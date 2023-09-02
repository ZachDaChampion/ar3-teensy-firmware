/**
 * @file main.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-01
 */

#include <Arduino.h>
#include <Joint.h>
#include <MsgPack.h>
#include <messaging.h>
#include <framing.h>

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define JOINT_COUNT SIZE(joints)

/**
 * A state of the cobot. This is comprised of a state ID and a message ID. The message ID is used to
 * send responses to the message that initiated the state. If the state is IDLE, the message ID is
 * ignored.
 */
struct CobotState {
  // The ID of the state.
  enum {
    IDLE,                // The cobot is not moving
    STOPPING,            // The cobot is stopping
    CALIBRATING,         // The cobot is calibrating
    MOVE_TO_AUTO,        // The cobot is moving to a position with an automatically calculated speed
    MOVE_TO_SPEED,       // The cobot is moving to a position with a specified speed
    MOVE_FOREVER_SPEED,  // The cobot is moving indefinitely at a specified speed
  } id;

  // The ID of the message that initiated the state.
  uint32_t msg_id;
};

//                                                                                                //
// ==================================== Joint configuration ===================================== //
//                                                                                                //

static Joint joints[] = { Joint({
  .id = 0,
  .name = "base",

  .min_steps = 0,  // TODO
  .max_steps = 0,  // TODO
  .ref_steps = 0,  // TODO

  .motor_steps_per_rev = 400,
  .enc_ticks_per_rev = 2048,

  .motor_reduction = 7.0,
  .enc_reduction = 7.0,

  .direction = 1,

  .max_speed = 5.0,
  .max_accel = 10.0,
  .calibration_speed = 5.0,

  .step_pin = 0,
  .dir_pin = 1,
  .enc_a_pin = 14,
  .enc_b_pin = 15,

  .speed_filter_strength = 5.0,

  .lim_pin = 26,
  .lim_debounce_time = 50,
}) };

//                                                                                                //
// ======================================== Global data ========================================= //
//                                                                                                //

// The current state of the cobot.
static CobotState state = { .id = CobotState::IDLE, .msg_id = 0 };
bool initialized = false;

// Message pack objects.
MsgPack::Packer packer;
MsgPack::Unpacker unpacker;

// Serial buffers.
static const size_t SERIAL_BUFFER_SIZE = 258;  // 255 bytes + 3 bytes for the header
static uint8_t serial_buffer_in[SERIAL_BUFFER_SIZE];
static uint8_t serial_buffer_out[SERIAL_BUFFER_SIZE];
static size_t serial_buffer_in_len = 0;
static size_t serial_buffer_out_len = 0;

bool message_in_progress = false;

//                                                                                                //
// ================================= Arduino control functions ================================== //
//                                                                                                //

void setup()
{
  // Start serial communication.
  Serial.begin(115200);

  // Initialize the joints.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].init();
  }
}

void loop()
{
  // Update all joints.
  for (auto joint : joints) {
    joint.update();
  }

  // Read from the serial port until the buffer is full or there are no more bytes to read.
  if (!Serial.available()) return;
  while (serial_buffer_in_len < SERIAL_BUFFER_SIZE) {
    int x = Serial.read();
    if (x == -1) break;
    if (message_in_progress || x == START_BYTE) {
      message_in_progress = true;
      serial_buffer_in[serial_buffer_in_len++] = x;
    }
  }

  // Try parsing a message.
  int msg_len = check_message(serial_buffer_in, serial_buffer_in_len);
  if (msg_len == 0) return;  // Message is incomplete

  // If the message is invalid, send an error log message and clear the buffer.
  if (msg_len == -1) {
    
  }

  // Parse the message as a request.
  cobot_proto::Request<6, 6, 6> request;
  request.deserialize(messenger.reader);
}
