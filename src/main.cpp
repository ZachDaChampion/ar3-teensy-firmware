/**
 * @file main.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 * 
 * @version 1.0
 * @date 2023-09-01
 */

#include <Arduino.h>
#include <Joint.h>
#include <framing.hpp>
#include <proto/main.h>
#include <MessageWriter.h>

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define JOINT_COUNT SIZE(joint_configs)

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
// ==================================== Robot configuration ===================================== //
//                                                                                                //

static const JointConfig joint_configs[] = { {
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
} };

//                                                                                                //
// ======================================== Global data ========================================= //
//                                                                                                //

// The current state of the cobot.
static CobotState state = { .id = CobotState::IDLE, .msg_id = 0 };
bool initialized = false;

// The joints of the cobot.
static Joint joints[JOINT_COUNT];

// Serial buffers. Size is 258 because the maximum supported payload length is 255, plus 3 bytes
// for the header.
static uint8_t serial_in_buffer[258];
static uint8_t serial_out_buffer[258];
static size_t serial_in_buffer_len = 0;
static size_t serial_out_buffer_len = 0;
OutputWriter serial_out_writer(serial_out_buffer, &serial_out_buffer_len, SIZE(serial_out_buffer));

//                                                                                                //
// ================================= Arduino control functions ================================== //
//                                                                                                //

void setup()
{
  // Start serial communication.
  Serial.begin(115200);

  // Initialize the joints.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].init(joint_configs[i]);
  }
}

void loop()
{
  // Update all joints.
  for (auto joint : joints) {
    joint.update();
  }

  // Read from serial until the buffer is full or there is no more data to read.
  if (!Serial.available()) return;
  while (serial_in_buffer_len < SIZE(serial_in_buffer)) {
    int x = Serial.read();
    if (x == -1) break;
    serial_in_buffer[serial_in_buffer_len++] = x;
  }

  // Try parsing a message.
  int msg_len = check_message(serial_in_buffer, serial_in_buffer_len);
  if (msg_len == 0) return;  // Message is incomplete

  // If the message is invalid, send an error log message and shift the buffer.
  if (msg_len == -1) {
    static const unsigned long MSG_LEN = 25;
    auto log_msg = cobot::LogMessage<MSG_LEN>();
    log_msg.set_level(cobot::LogLevel::ERROR);
    log_msg.mutable_message() = "Invalid message received";

    auto msg = cobot::CobotMessage<0, 0, 0, 0, 0, MSG_LEN>();
    msg.set_log(log_msg);
    uint32_t serialized_size = msg.serialized_size();
    int w = framed_template(serial_out_buffer, SIZE(serial_out_buffer));
    serial_out_buffer_len = w;

    // If the error message doesn't fit in the buffer,
    if (msg.serialize(serial_out_writer) != EmbeddedProto::Error::NO_ERRORS) {
      exit(1);
    }
  }
}
