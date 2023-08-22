#include <AccelStepper.h>
#include <Arduino.h>
#include <Encoder.h>

#include <LimitSwitch.hpp>
#include <ar3_error.h>
#include <checksum.hpp>

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define JOINT_COUNT SIZE(joints)

#define SKIP_BYTE 0x7FFF
#define MSG_START 0x24
#define MSG_ERR 0x00
#define MSG_ACK 0x01
#define MSG_DONE 0x02
#define MSG_INIT 0x03
#define MSG_CAL 0x04
#define MSG_SET 0x05
#define MSG_GET 0x06
#define MSG_MOV 0x07
#define MSG_STP 0x08
#define MSG_RST 0x09
#define MSG_HOM 0x0A
#define MSG_POS 0x0B

// Message lengths (in bytes) indexed by message type. -1 indicates a variable length message.
static const size_t msg_len[] = {
  [MSG_ERR] = (size_t)-1, [MSG_ACK] = 3,  [MSG_DONE] = 3, [MSG_INIT] = 5,
  [MSG_CAL] = 3,          [MSG_SET] = 17, [MSG_GET] = 3,  [MSG_MOV] = 45,
  [MSG_STP] = 4,          [MSG_RST] = 3,  [MSG_HOM] = 3,  [MSG_POS] = 17,
};

struct JointConfig {
  const char* name;            // Name of the joint

  long min_steps;              // Most negative position of the joint (in steps)
  long max_steps;              // Most positive position of the joint (in steps)
  long ref_steps;              // Position of the joint when it touches the limit switch (in steps)
  int steps_per_rev;           // Number of steps per revolution of the stepper motor

  float max_speed;             // Maximum speed of the joint (in steps per second)
  float max_accel;             // Maximum acceleration of the joint (in steps per second per second)

  float calibration_speed;     // Speed of the joint during calibration (in steps per second). Sign
                               // determines the direction of calibration. `direction` is ignored
                               // during calibration.

  uint8_t step_pin;            // Step pin of the motor controller
  uint8_t dir_pin;             // Direction pin of the motor controller

  uint8_t enc_a_pin;           // Encoder A pin
  uint8_t enc_b_pin;           // Encoder B pin

  uint8_t lim_pin;             // Limit switch pin
  uint16_t lim_debounce_time;  // Debounce time for the limit switch

  int8_t direction;            // 1 if the joint is not reversed, -1 if it is reversed
};

enum JointState {
  JOINT_STATE_OFF,            // Joint is off
  JOINT_STATE_HOLD,           // Joint is holding position
  JOINT_STATE_STOPPING,       // Joint is in the process of stopping
  JOINT_STATE_MOVE_SPEED,     // Joint is moving at a constant speed
  JOINT_STATE_MOVE_TO_SPEED,  // Joint is moving to a position at a constant speed
  JOINT_STATE_MOVE_AUTO,      // Joint is moving to a position at an automatically calculated speed
};

enum ActiveCommand {
  ACTIVE_COMMAND_NONE,  // No command is currently active
  ACTIVE_COMMAND_MOVE,  // The robot is currently moving to a position
  ACTIVE_COMMAND_STOP,  // The robot is currently stopping
};

struct RobotState {
  bool firmware_matched = false;  // Whether the firmware version matches the expected version
  bool calibrated = false;        // Whether the robot has been calibrated
  ActiveCommand active_command = ACTIVE_COMMAND_NONE;  // The currently active command
};

//                                                                                                //
// ==================================== Robot configuration ===================================== //
//                                                                                                //

static const uint16_t firmware_version[] = { 1, 0 };  // [major, minor]

static const JointConfig joints[] = {

  {
      // Joint 0
      .name = "j0",
      .min_steps = 0,
      .max_steps = 0,
      .ref_steps = 0,
      .steps_per_rev = 0,
      .step_pin = 0,
      .dir_pin = 0,
      .enc_a_pin = 0,
      .enc_b_pin = 0,
      .lim_pin = 0,
      .direction = 1,
  },
};

//                                                                                                //
// ======================================== Global data ========================================= //
//                                                                                                //

static AccelStepper* steppers[JOINT_COUNT];
static Encoder* encoders[JOINT_COUNT];
static LimitSwitch* limit_switches[JOINT_COUNT];

// State of the robot
static RobotState robot_state;
static JointState joint_states[JOINT_COUNT];

// Serial buffer used for receiving commands
static uint8_t ibuf[1024];
static uint8_t ibuf_idx = 0;

// Serial buffer used for sending responses
static uint8_t obuf[1024];

// Forward declarations
void run_steppers();
bool all_joints_stopped();
void send_msg(uint8_t* from, size_t size);
int write_err(uint8_t* dest, size_t size, uint8_t code, char* msg);
int write_err(uint8_t* dest, size_t size, uint8_t code, const char* msg);
int parse_serial(uint8_t* dest, size_t dest_size, uint8_t* src, size_t src_size);
int cmd_init(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);
int cmd_cal(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);
int cmd_set(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);
int cmd_get(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);
int cmd_mov(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);
int cmd_stp(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);
int cmd_rst(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);
int cmd_hom(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size);

//                                                                                                //
// ================================= Arduino control functions ================================== //
//                                                                                                //

void setup()
{
  // Initialize steppers, encoders, and limit switches
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    steppers[i] = new AccelStepper(AccelStepper::DRIVER, joints[i].step_pin, joints[i].dir_pin);
    steppers[i]->setMaxSpeed(joints[i].max_speed);
    steppers[i]->setAcceleration(joints[i].max_accel);
    encoders[i] = new Encoder(joints[i].enc_a_pin, joints[i].enc_b_pin);
    limit_switches[i] = new LimitSwitch(joints[i].lim_pin);
    joint_states[i] = JOINT_STATE_OFF;
  }
}

void loop()
{
  run_steppers();

  // Check if the active command is complete and send a `DONE` message if it is
  switch (robot_state.active_command) {
    case ACTIVE_COMMAND_MOVE:
    case ACTIVE_COMMAND_STOP:
      if (all_joints_stopped()) {
        robot_state.active_command = ACTIVE_COMMAND_NONE;
        obuf[0] = MSG_DONE;
        send_msg(obuf, 1);
        Serial.flush();
      }
      break;
    default:
      break;
  }

  // Read a character from the serial port
  if (Serial.available()) {
    uint8_t c = Serial.read();

    // If we are currently receiving a command, or this is the start of a new command,
    // then add the character to the buffer
    if (ibuf_idx > 0 || c == MSG_START) {
      ibuf[ibuf_idx++] = c;
    }

    // If we have less than three bytes, the message is not complete. Wait for more bytes.
    if (ibuf_idx < 3) {
      return;
    }

    // If the message type is invalid, send an error and reset the buffer.
    uint8_t msg_type = ibuf[1];
    if (msg_type > SIZE(msg_len)) {
      size_t len = write_err(obuf, SIZE(obuf), AR3_ERR_INVALID_COMMAND, "Invalid message type");
      send_msg(obuf, len);
      ibuf_idx = 0;
      return;
    }

    // If the message is complete, then process it. We can use the `msg_len` array to look up the
    // expected length because we do not receive any messages of variable length.
    size_t full_msg_len = msg_len[msg_type];
    if (ibuf_idx == full_msg_len) {
      int len = parse_serial(obuf, SIZE(obuf), ibuf, full_msg_len);
      if (len < 0) send_msg(obuf, len);  // Ignore message if it couldn't fit in the buffer
      ibuf_idx = 0;
      return;
    }

    // If the buffer is full, send an error and reset the buffer
    if (ibuf_idx >= SIZE(ibuf)) {
      size_t len = write_err(obuf, SIZE(obuf), AR3_ERR_BUFFER_OVERFLOW, "Command buffer overflow");
      send_msg(obuf, len);
      ibuf_idx = 0;
      return;
    }
  }
}

//                                                                                                //
// ===================================== Utility functions ====================================== //
//                                                                                                //

/**
 * Run the stepper motors. This function should be called frequently.
 */
void run_steppers()
{
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    switch (joint_states[i]) {
      case JOINT_STATE_STOPPING:
        if (steppers[i]->isRunning()) {
          steppers[i]->run();
        } else {
          joint_states[i] = JOINT_STATE_HOLD;
        }
        break;

      case JOINT_STATE_MOVE_AUTO:
        steppers[i]->run();
        break;

      case JOINT_STATE_MOVE_SPEED:
        steppers[i]->runSpeed();
        break;

      case JOINT_STATE_MOVE_TO_SPEED:
        steppers[i]->runSpeedToPosition();
        break;

      default:
        break;
    }
  }
}

/**
 * Check if all the stepper motors have stopped.
 *
 * @return True if all the stepper motors have stopped, false otherwise.
 */
bool all_joints_stopped()
{
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    if (steppers[i]->isRunning()) return false;
  }
  return true;
}

/**
 * Stop all stepper motors. Bt default, this function takes into account maximum acceleration and
 * deceleration values, so the motors may not stop immediately. Set the `immediate` parameter to
 * `true` to stop the motors immediately.
 *
 * @param[in] immediate Whether to stop the motors immediately or not.
 */
void stop_all(bool immediate = false)
{
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    if (immediate) {
      steppers[i]->setSpeed(0);
      steppers[i]->runSpeed();
      joint_states[i] = JOINT_STATE_HOLD;
    } else {
      steppers[i]->stop();
      joint_states[i] = JOINT_STATE_STOPPING;
    }
    robot_state.active_command = ACTIVE_COMMAND_STOP;
  }
}

/**
 * Send a message to the serial port. This function adds the start byte and checksum.
 *
 * @param[in] from Buffer to send.
 * @param[in] size Size of the buffer.
 */
void send_msg(uint8_t* from, size_t size)
{
  uint8_t checksum = crc8ccitt(from, size);
  Serial.write(MSG_START);
  Serial.write(from, size);
  Serial.write(checksum);
}

/**
 * Write an error message to a buffer. Returns the number of bytes written to the buffer, or -1 if
 * the buffer is too small. This function does not add the start byte or checksum.
 *
 * @param[out] dest The buffer to write to
 * @param[in] size The size of the buffer
 * @param[in] code The error code
 * @param[in] msg The error message
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int write_err(uint8_t* dest, size_t size, uint8_t code, char* msg)
{
  size_t msg_len = strlen(msg);

  if (size < 4 + msg_len) {
    return -1;
  }

  dest[0] = MSG_ERR;
  dest[1] = code;
  dest[2] = msg_len;
  memcpy(dest + 3, msg, msg_len);

  return 3 + msg_len;
}

/**
 * Write an error message to a buffer. Returns the number of bytes written to the buffer, or -1 if
 * the buffer is too small. This function does not add the start byte or checksum.
 *
 * @param[out] dest The buffer to write to
 * @param[in] size The size of the buffer
 * @param[in] code The error code
 * @param[in] msg The error message
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int write_err(uint8_t* dest, size_t size, uint8_t code, const char* msg)
{
  size_t msg_len = strlen(msg);

  if (size < 4 + msg_len) {
    return -1;
  }

  dest[0] = MSG_ERR;
  dest[1] = code;
  dest[2] = msg_len;
  memcpy(dest + 3, msg, msg_len);

  return 3 + msg_len;
}

//                                                                                                //
// ====================================== Serial interface ====================================== //
//                                                                                                //

/**
 * Parse an input from the serial port.
 *
 * @param[out] dest Destination to write the response to
 * @param[in] dest_size Size of the destination buffer
 * @param[in] src Source buffer
 * @param[in] src_size Size of the source buffer
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int parse_serial(uint8_t* dest, size_t dest_size, uint8_t* src, size_t src_size)
{
  if (src[0] != MSG_START) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_COMMAND, "Command must start with '$'");
  }

  // Verify checksum
  uint8_t checksum = crc8ccitt(src + 1, src_size - 2);
  if (checksum != src[src_size - 1]) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_CHECKSUM, "Invalid checksum");
  }

  // Run the command
  switch (src[1]) {
    case MSG_INIT:
      return cmd_init(dest, dest_size, src + 2, src_size - 3);
    case MSG_CAL:
      return cmd_cal(dest, dest_size, src + 2, src_size - 3);
    case MSG_SET:
      return cmd_set(dest, dest_size, src + 2, src_size - 3);
    case MSG_GET:
      return cmd_get(dest, dest_size, src + 2, src_size - 3);
    case MSG_MOV:
      return cmd_mov(dest, dest_size, src + 2, src_size - 3);
    case MSG_STP:
      return cmd_stp(dest, dest_size, src + 2, src_size - 3);
    case MSG_RST:
      return cmd_rst(dest, dest_size, src + 2, src_size - 3);
    case MSG_HOM:
      return cmd_hom(dest, dest_size, src + 2, src_size - 3);
    default:
      return write_err(dest, dest_size, AR3_ERR_INVALID_COMMAND, "Invalid command");
  }
}

/**
 * Handle the INIT command. Initialize the robot and ensure firmware is correct.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args Command payload
 * @param[in] args_size Size of the command payload
 *  @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_init(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  if (args_size != 2)
    return write_err(dest, dest_size, AR3_ERR_MALFORMED_ARG, "Invalid payload size");

  // Verify firmware version
  uint8_t firmware_major = args[0];
  uint8_t firmware_minor = args[1];
  if (firmware_major != firmware_version[0] || firmware_minor != firmware_version[1]) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_FIRMWARE, "Invalid firmware version");
  }

  robot_state.firmware_matched = true;
  dest[0] = MSG_ACK;
  return 1;
}

/**
 * Handle the CAL command. Calibrate the robot.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args  Command arguments
 * @param[in] args_size Size of the command arguments
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_cal(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  if (!robot_state.firmware_matched) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_FIRMWARE, "Robot has not been initialized");
  }
  if (args_size != 0) {
    return write_err(dest, dest_size, AR3_ERR_MALFORMED_ARG, "CAL command does not take arguments");
  }

  // Send acknowledgement
  dest[0] = MSG_ACK;
  send_msg(dest, 1);
  Serial.flush();

  uint16_t hit_limit_switches = 0;  // Bitfield of which joints have hit their limit switches.
  uint8_t calibrated_count = 0;     // Number of joints that have been calibrated.

  // Start moving all joints towards their limit switches.
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    steppers[i]->setSpeed(joints[i].calibration_speed);
    joint_states[i] = JOINT_STATE_MOVE_SPEED;
  }

  // Loop until all joints have been calibrated. Each joint will move until it hits its limit
  // switch, then will move to its home position. The `hit_limit_switches` bitfield is used to
  // track which joints have hit their limit switches.
  //
  // It is very important that `run_steppers` is called continuously while the robot is calibrating.
  // If it is not called, the robot will not move.
  while (calibrated_count < JOINT_COUNT) {
    run_steppers();

    for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
      // If the joint has just hit its limit switch, set current position to the reference position
      // and move to the home position.
      uint8_t limit = limit_switches[i]->read();
      if (limit && !(hit_limit_switches & (1 << i))) {
        steppers[i]->setCurrentPosition(joints[i].ref_steps);
        steppers[i]->moveTo(0);
        steppers[i]->setSpeed(joints[i].calibration_speed);
        joint_states[i] = JOINT_STATE_MOVE_TO_SPEED;
        hit_limit_switches |= (1 << i);
        continue;
      }

      // If the joint has come to a stop at the home position, set the state to HOLD and increment
      // the calibrated count.
      if (!steppers[i]->isRunning()) {
        joint_states[i] = JOINT_STATE_HOLD;
        ++calibrated_count;
        continue;
      }
    }
  }

  robot_state.calibrated = true;
  dest[0] = MSG_DONE;
  return 1;
}

/**
 * Handle the SET command. Set the current position of one or more joints.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args Command arguments
 * @param[in] args_size Size of the command arguments
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_set(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  if (!robot_state.firmware_matched) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_FIRMWARE, "Robot has not been initialized");
  }
  if (!robot_state.calibrated) {
    return write_err(dest, dest_size, AR3_ERR_NOT_CALIBRATED, "Robot is not calibrated");
  }
  if (args_size != JOINT_COUNT * 2) {
    return write_err(dest, dest_size, AR3_ERR_MALFORMED_ARG, "Invalid payload size");
  }

  // Parse arguments
  uint16_t new_positions[JOINT_COUNT];
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    uint16_t new_position = args[i * 2] | (args[i * 2 + 1] << 8);

    // If the new position is not being skipped, and it is out of bounds, return an error.
    if (new_position != SKIP_BYTE &&
        (new_position > joints[i].max_steps || new_position < joints[i].min_steps)) {
      char msg[29];
      snprintf(msg, SIZE(msg), "Position %d out of bounds", new_position);
      return write_err(dest, dest_size, AR3_ERR_OOB, msg);
    }

    new_positions[i] = new_position;
  }

  // Set the new position for each joint
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    if (new_positions[i] != SKIP_BYTE) steppers[i]->setCurrentPosition(new_positions[i]);
  }

  dest[0] = MSG_ACK;
  return 1;
}

/**
 * Handles the GET command. Get the current positions of the joints.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args Command arguments
 * @param[in] args_size Size of the command arguments
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_get(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  if (!robot_state.firmware_matched) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_FIRMWARE, "Robot has not been initialized");
  }
  if (!robot_state.calibrated) {
    return write_err(dest, dest_size, AR3_ERR_NOT_CALIBRATED, "Robot is not calibrated");
  }
  if (args_size != 0) {
    return write_err(dest, dest_size, AR3_ERR_MALFORMED_ARG, "GET command does not take arguments");
  }

  // Read the current position of each joint and write it to the output buffer
  dest[0] = MSG_POS;
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    uint16_t position = steppers[i]->currentPosition();
    dest[i * 2 + 1] = position & 0xFF;
    dest[i * 2 + 2] = (position >> 8) & 0xFF;
  }

  return 1 + JOINT_COUNT * 2;
}

/**
 * Handle the MOV command. Move one or more joints to a position.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args  Command arguments
 * @param[in] args_size Size of the command arguments
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_mov(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  if (!robot_state.firmware_matched) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_FIRMWARE, "Robot has not been initialized");
  }
  if (!robot_state.calibrated) {
    return write_err(dest, dest_size, AR3_ERR_NOT_CALIBRATED, "Robot is not calibrated");
  }
  if (args_size != JOINT_COUNT * 6) {
    return write_err(dest, dest_size, AR3_ERR_MALFORMED_ARG, "Invalid payload size");
  }

  // Parse arguments
  uint16_t positions[JOINT_COUNT];
  float speeds[JOINT_COUNT];
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    uint16_t position = args[i * 6] | (args[i * 6 + 1] << 8);
    float speed = *((float*)(args + i * 6 + 2));  // Floats don't care about endianness

    // If the position is not being skipped, and it is out of bounds, return an error.
    if (position != SKIP_BYTE &&
        (position > joints[i].max_steps || position < joints[i].min_steps)) {
      char msg[29];
      snprintf(msg, SIZE(msg), "Position %d out of bounds", position);
      return write_err(dest, dest_size, AR3_ERR_OOB, msg);
    }

    // Clamp the speed to the maximum speed
    if (speed < 0) speed = 0;
    if (speed > joints[i].max_speed) speed = joints[i].max_speed;

    positions[i] = position;
    speeds[i] = speed;
  }

  // Start moving each joint
  for (uint8_t i = 0; args != NULL; ++i) {
    if (positions[i] == SKIP_BYTE) continue;

    steppers[i]->moveTo(positions[i]);
    if (speeds[i] == 0) {
      joint_states[i] = JOINT_STATE_MOVE_AUTO;
    } else {
      steppers[i]->setSpeed(speeds[i]);
      joint_states[i] = JOINT_STATE_MOVE_TO_SPEED;
    }
  }

  robot_state.active_command = ACTIVE_COMMAND_MOVE;
  dest[0] = MSG_ACK;
  return 1;
}

/**
 * Handle the STP command. Stops all joints.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args  Command arguments
 * @param[in] args_size Size of the command arguments
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_stp(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  if (!robot_state.firmware_matched) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_FIRMWARE, "Robot has not been initialized");
  }

  // Because stopping is so important, we accept the command even if the arguments are invalid.
  bool smooth = args_size > 0 && args[0] == 1;
  stop_all(!smooth);

  robot_state.active_command = ACTIVE_COMMAND_STOP;
  dest[0] = MSG_ACK;
  return 1;
}

/**
 * Handle the RST command. Resets the robot, but does not move joints.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args  Command arguments
 * @param[in] args_size Size of the command arguments
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_rst(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  stop_all(false);
  robot_state.active_command = ACTIVE_COMMAND_STOP;
  robot_state.calibrated = false;
  robot_state.firmware_matched = false;

  dest[0] = MSG_ACK;
  return 1;
}

/**
 * Handle the HOM command. Moves all joints to their home position.
 *
 * @param[out] dest Output buffer to write to
 * @param[in] dest_size Size of the output buffer
 * @param[in] args  Command arguments
 * @param[in] args_size Size of the command arguments
 * @return The number of bytes written to the buffer, or -1 if the buffer is too small
 */
int cmd_hom(uint8_t* dest, size_t dest_size, uint8_t* args, size_t args_size)
{
  if (!robot_state.firmware_matched) {
    return write_err(dest, dest_size, AR3_ERR_INVALID_FIRMWARE, "Robot has not been initialized");
  }
  if (!robot_state.calibrated) {
    return write_err(dest, dest_size, AR3_ERR_NOT_CALIBRATED, "Robot is not calibrated");
  }
  if (args_size != 0) {
    return write_err(dest, dest_size, AR3_ERR_MALFORMED_ARG, "Invalid payload size");
  }

  // Start moving each joint
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    steppers[i]->moveTo(0);
    joint_states[i] = JOINT_STATE_MOVE_AUTO;
  }

  robot_state.active_command = ACTIVE_COMMAND_MOVE;
  dest[0] = MSG_ACK;
  return 1;
}