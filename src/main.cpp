#include <AccelStepper.h>
#include <Arduino.h>
#include <Encoder.h>

#include <LimitSwitch.hpp>
#include <ar3_error.h>

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define JOINT_COUNT SIZE(joints)

struct JointConfig {
  int min_steps;               // Most negative position of the joint (in steps)
  int max_steps;               // Most positive position of the joint (in steps)
  int ref_steps;               // Position of the joint when it touches the limit switch (in steps)
  int steps_per_rev;           // Number of steps per revolution of the stepper motor

  float max_speed;             // Maximum speed of the joint (in steps per second)
  float max_accel;             // Maximum acceleration of the joint (in steps per second per second)

  uint8_t step_pin;            // Step pin of the motor controller
  uint8_t dir_pin;             // Direction pin of the motor controller

  uint8_t enc_a_pin;           // Encoder A pin
  uint8_t enc_b_pin;           // Encoder B pin

  uint8_t lim_pin;             // Limit switch pin
  uint16_t lim_debounce_time;  // Debounce time for the limit switch

  uint8_t reversed;            // Whether the joint is reversed
};

enum joint_state_t {
  JOINT_STATE_OFF,
  JOINT_STATE_HOLD,
  JOINT_STATE_MOVE_SPEED,
  JOINT_STATE_MOVE_AUTO,
};

struct JointState {
  int steps;            // Current position of the joint (in steps)
  float speed;          // Current speed of the joint (in steps per second)

  joint_state_t state;  // Current state of the joint
};

// ============================ ROBOT CONFIGURATION ============================

static const char* FIRMWARE_VERSION = "1.0.0";

static const JointConfig joints[] = {

  {
      // Joint 0
      .min_steps = 0,
      .max_steps = 0,
      .ref_steps = 0,
      .steps_per_rev = 0,
      .step_pin = 0,
      .dir_pin = 0,
      .enc_a_pin = 0,
      .enc_b_pin = 0,
      .lim_pin = 0,
      .reversed = 0,
  },
};

// ========================== END ROBOT CONFIGURATION ==========================

static AccelStepper* steppers[JOINT_COUNT];
static Encoder* encoders[JOINT_COUNT];
static LimitSwitch* limit_switches[JOINT_COUNT];
static JointState* joint_states[JOINT_COUNT];

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
    joint_states[i] = new JointState{
      .steps = 0,
      .speed = 0,
      .state = JOINT_STATE_OFF,
    };
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
    switch (joint_states[i]->state) {
      case JOINT_STATE_MOVE_AUTO:
        steppers[i]->run();
        break;
      case JOINT_STATE_MOVE_SPEED:
        steppers[i]->runSpeed();
        break;
      default:
        break;
    }
  }
}

/**
 * Send a message to the serial port. This function adds the '$', the checksum, and the newline.
 *
 * \param[in] from Buffer to send.
 */
void send_msg(char* from)
{
  Serial.print("$");
  Serial.print(from);
  Serial.print("\n");
}

/**
 * Write an error message to a buffer.
 *
 * \param[out] dest The buffer to write to
 * \param[in] size The size of the buffer
 * \param[in] code The error code
 * \param[in] msg The error message
 */
int write_err(char* dest, size_t size, uint8_t code, const char* msg)
{
  return snprintf(obuf, size, "ERR;%d;%s;", code, msg);
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

bool verify_checksum(char* msg, char* checksum)
{
  // TODO
  return true;
}