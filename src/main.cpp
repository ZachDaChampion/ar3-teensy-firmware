#include <AccelStepper.h>
#include <Arduino.h>
#include <Encoder.h>

#include <LimitSwitch.hpp>
#include <ar3_error.h>
#include <checksum.hpp>

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define JOINT_COUNT SIZE(joints)

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
  JOINT_STATE_MOVE_SPEED,     // Joint is moving at a constant speed
  JOINT_STATE_MOVE_TO_SPEED,  // Joint is moving to a position at a constant speed
  JOINT_STATE_MOVE_AUTO,      // Joint is moving to a position at an automatically calculated speed
};

struct RobotState {
  bool firmware_matched = false;  // Whether the firmware version matches the expected version
  bool calibrated = false;        // Whether the robot has been calibrated
};

// ============================ ROBOT CONFIGURATION ============================

static const char* firmware_version = "1.0.0";

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

// ========================== END ROBOT CONFIGURATION ==========================

static AccelStepper* steppers[JOINT_COUNT];
static Encoder* encoders[JOINT_COUNT];
static LimitSwitch* limit_switches[JOINT_COUNT];

// State of the robot
static RobotState robot_state;
static JointState joint_states[JOINT_COUNT];

// Serial buffer used for receiving commands
static char ibuf[1024];
static uint8_t ibuf_idx = 0;

// Serial buffer used for sending responses
static char obuf[1024];

void setup()
{
  // Ensure i/o buffers are null-terminated (for safety)
  ibuf[SIZE(ibuf) - 1] = '\0';
  obuf[SIZE(obuf) - 1] = '\0';

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
  // Read a character from the serial port
  if (Serial.available()) {
    char c = Serial.read();

    // If the character is a newline, then we have received a complete command
    if (c == '\n') {
      ibuf[ibuf_idx] = '\0';
      parse_serial(obuf, SIZE(obuf), ibuf);
      send_msg(obuf);
      ibuf_idx = 0;
      goto update_hw;
    }

    // If the character is whitespace, then ignore it
    if (c == ' ' || c == '\t' || c == '\r') {
      goto update_hw;
    }

    // If the buffer is full, send an error and reset the buffer
    if (ibuf_idx >= SIZE(ibuf)) {
      write_err(obuf, SIZE(obuf), AR3_ERR_BUFFER_OVERFLOW, "Command buffer overflow");
      send_msg(obuf);
      ibuf_idx = 0;
      goto update_hw;
    }

    // If we are currently receiving a command, or this is the start of a new command,
    // then add the character to the buffer
    if (ibuf_idx > 0 || c == '$') {
      ibuf[ibuf_idx++] = c;
      goto update_hw;
    }
  }

update_hw:
  run_steppers();
}

/**
 * Run the stepper motors. This function should be called frequently.
 */
void run_steppers()
{
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    switch (joint_states[i]) {
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
 * Send a message to the serial port. This function adds the '$', the '*', the checksum, and the
 * newline.
 *
 * \param[in] from Buffer to send.
 */
void send_msg(char* from)
{
  uint8_t checksum = calc_checksum(from);
  Serial.printf("$%s*%02X\n", from, checksum);
}

/**
 * Write an error message to a buffer.
 *
 * \param[out] dest The buffer to write to
 * \param[in] size The size of the buffer
 * \param[in] code The error code
 * \param[in] msg The error message
 */
int write_err(char* dest, size_t size, uint8_t code, char* msg)
{
  return snprintf(obuf, size, "ERR;%d;%s;", code, msg);
}

/**
 * Implementation of strtok_r from the standard library. It is not available on the Teensy.
 * See <https://linux.die.net/man/3/strtok_r> for more information.
 *
 * \param[in] str The string to tokenize
 * \param[in] delim The delimiter to use
 * \param[out] save_ptr The save pointer
 * \return The next token
 */
char* strtok_r(char* str, const char* delim, char** save_ptr)
{
  if (str == NULL) str = *save_ptr;
  if (*str == '\0') return NULL;

  char* end = strpbrk(str, delim);
  if (end == NULL) {
    *save_ptr = str + strlen(str);
    return str;
  }

  *end = '\0';
  *save_ptr = end + 1;
  return str;
}

/**
 * Parse an input from the serial port.
 *
 * \param[out] dest Destination to write the response to
 * \param[in] size Size of the destination buffer
 * \param[in] from Input buffer to parse
 */
void parse_serial(char* dest, size_t size, char* from)
{
  // Check if beginning of message is valid
  if (from[0] != '$') {
    write_err(dest, size, AR3_ERR_INVALID_COMMAND, "Command must start with '$'");
    return;
  }

  // Separate message and checksum
  char* msg = strtok(from, "*");
  char* checksum = strtok(NULL, "*");
  if (msg == NULL || checksum == NULL) {
    write_err(dest, size, AR3_ERR_INVALID_COMMAND, "Invalid command");
    return;
  }
  if (!verify_checksum(msg, checksum)) {
    write_err(dest, size, AR3_ERR_INVALID_CHECKSUM, "Invalid checksum");
    return;
  }

  // Parse the command
  char* cmd = strtok(msg, ";");
  if (cmd == NULL) {
    write_err(dest, size, AR3_ERR_INVALID_COMMAND, "Invalid command");
    return;
  }
  char* args = strtok(NULL, ";");

  // Run the command
  if (strcmp(cmd, "INIT") == 0)
    cmd_init(dest, size, args);
  else if (strcmp(cmd, "CAL") == 0)
    cmd_cal(dest, size, args);
  else if (strcmp(cmd, "SET") == 0)
    cmd_set(dest, size, args);
  else if (strcmp(cmd, "MV") == 0)
    cmd_mv(dest, size, args);
  else if (strcmp(cmd, "MVR") == 0)
    cmd_mvr(dest, size, args);
  else if (strcmp(cmd, "STP") == 0)
    cmd_stp(dest, size, args);
  else if (strcmp(cmd, "GET") == 0)
    cmd_get(dest, size, args);
  else if (strcmp(cmd, "RST") == 0)
    cmd_rst(dest, size, args);
  else if (strcmp(cmd, "HOME") == 0)
    cmd_home(dest, size, args);
  else
    write_err(dest, size, AR3_ERR_INVALID_COMMAND, "Invalid command");
}

struct ParsedArg {
  char* label;
  char* vals[4];
  uint8_t count;
};

/**
 * Parse a single argument into a label and an array of values.
 *
 * \param[in] arg The argument to parse
 * \param[in] default_label The default label to use if none is specified
 * \return The parsed argument
 */
ParsedArg parse_arg(char* arg, char* default_label)
{
  // Parse label
  ParsedArg ret;
  char* save_ptr;
  char* delim = strchr(arg, ':');
  if (delim == NULL) {
    ret.label = default_label;
    delim = arg;
  } else {
    *delim = '\0';
    ret.label = arg;
    delim++;
  }

  // Parse values
  while (ret.count < SIZE(ret.vals)) {
    char* val = strtok_r(delim, ",", &save_ptr);
    if (val == NULL) break;
    ret.vals[ret.count++] = val;
    delim = NULL;
  }

  return ret;
}

/**
 * Handle the INIT command. Initialize the robot and ensure firmware is correct.
 *
 * \param[out] dest Output buffer to write to
 * \param[in] size Size of the output buffer
 * \param[in] args  Command arguments
 */
void cmd_init(char* dest, size_t size, char* args)
{
  ParsedArg arg = parse_arg(args, "v");
  if (strcmp(arg.label, "v")) {
    char msg[32];
    snprintf(msg, SIZE(msg), "Invalid argument '%s'", arg.label);
    write_err(dest, size, AR3_ERR_INVALID_ARG, msg);
    return;
  }
  if (arg.count != 1) {
    write_err(dest, size, AR3_ERR_MALFORMED_ARG, "Invalid number of arguments");
    return;
  }

  // Check firmware version
  if (strcmp(arg.vals[0], firmware_version) != 0) {
    char msg[64];
    snprintf(msg, SIZE(msg), "Running firmware %s, expected %s", firmware_version, arg.vals[0]);
    write_err(dest, size, AR3_ERR_INVALID_FIRMWARE, msg);
    return;
  }

  // Initialize the robot
  robot_state.firmware_matched = true;
  snprintf(dest, size, "OK;");
}

/**
 * Handle the CAL command. Calibrate the robot.
 *
 * \param[out] dest Output buffer to write to
 * \param[in] size Size of the output buffer
 * \param[in] args  Command arguments
 */
void cmd_cal(char* dest, size_t size, char* args)
{
  if (args != NULL) {
    write_err(dest, size, AR3_ERR_INVALID_ARG, "CAL does not take arguments");
    return;
  }

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
  snprintf(dest, size, "OK;");
}