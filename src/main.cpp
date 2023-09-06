/**
 * @file main.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-01
 */

#include <Arduino.h>
#include <Joint.h>
#include <main_generated.h>
#include <framing.h>
#include "message-helper.h"

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
// ====================================== Firmware version ====================================== //
//                                                                                                //

#define FW_VERSION 2
#define FW_VERSION_STR "2"

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

// Flatbuffers builder.
static flatbuffers::FlatBufferBuilder builder(1024);

// Serial buffers.
static const size_t SERIAL_BUFFER_SIZE = 258;  // 255 bytes + 3 bytes for the header
static uint8_t serial_buffer_in[SERIAL_BUFFER_SIZE];
static uint8_t serial_buffer_out[SERIAL_BUFFER_SIZE];
static size_t serial_buffer_in_len = 0;
static size_t serial_buffer_out_len = 0;

bool message_in_progress = false;

//                                                                                                //
// ====================================== Request handlers ====================================== //
//                                                                                                //

/**
 * Handles an init request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return  The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *          small.
 */
int handle_init(uint32_t request_id, const CobotMsgs::Request::Init* data)
{
  if (data->expected_fw_version() == FW_VERSION) {
    initialized = true;
    return msg_helper::write_ack(serial_buffer_out, SERIAL_BUFFER_SIZE, builder, request_id);
  } else {
    return msg_helper::write_error_response(
      serial_buffer_out, SERIAL_BUFFER_SIZE, builder, request_id,
      CobotMsgs::ErrorCode_INVALID_FIRMWARE_VERSION,
      "COBOT is running firmware version " FW_VERSION_STR ".");
  }
}

/**
 * Handles a calibrate request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return  The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *          small.
 */
int handle_calibrate(uint32_t request_id, const CobotMsgs::Request::Calibrate* data)
{
  if (!initialized) {
    return msg_helper::write_error_response(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                                            request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  uint8_t joints_bf = data->joints_bitfield();

  // Verify that no joints are set that don't exist.
  if (joints_bf >> JOINT_COUNT) {
    return msg_helper::write_error_response(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                                            request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                            "The joints bitfield contains bits that don't "
                                            "correspond to any joints.");
  }

  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop();
    if (joints_bf & (1 << i)) {
      joints[i].calibrate();
    }
  }

  state.id = CobotState::CALIBRATING;
  state.msg_id = request_id;
  return msg_helper::write_ack(serial_buffer_out, SERIAL_BUFFER_SIZE, builder, request_id);
}

/**
 * Handles an override request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
int handle_override(uint32_t request_id, const CobotMsgs::Request::Override* data)
{
  if (!initialized) {
    return msg_helper::write_error_response(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                                            request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  auto entries = data->entries();
  auto entry_count = entries->size();

  // Stop all joints and override the position of any joints that are specified. Count the number of
  // joints we override so that we can verify that all joints were found.
  uint8_t found = 0;
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop();
    for (size_t j = 0; j < entry_count; ++j) {
      auto entry = entries->Get(j);
      if (entry->joint_id() == i) {
        joints[i].override_position(entry->angle());
        ++found;
        break;
      }
    }
  }

  if (found != entry_count) {
    return msg_helper::write_error_response(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                                            request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                            "Some joints were not found.");
  }
  return msg_helper::write_ack(serial_buffer_out, SERIAL_BUFFER_SIZE, builder, request_id);
}

/**
 * Handles a get joints request.
 *
 * @param[in] request_id The ID of the request.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
int handle_get_joints(uint32_t request_id)
{
  if (!initialized) {
    return msg_helper::write_error_response(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                                            request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }

  // Create an array of joint entries. This must be done in a manually allocated buffer because
  // JointsEntry does not have a default constructor.
  uint8_t joint_entries_buf[JOINT_COUNT * sizeof(CobotMsgs::Response::JointsEntry)];
  auto joint_entries = reinterpret_cast<CobotMsgs::Response::JointsEntry*>(joint_entries_buf);

  // Populate the joint entries.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    auto joint_entry = &joint_entries[i];
    *joint_entry = CobotMsgs::Response::JointsEntry(i, joints[i].get_position());
  }

  // Create the outgoing message.
  builder.Clear();
  auto joint_entries_vec = builder.CreateVectorOfStructs(joint_entries, JOINT_COUNT);
  auto joints_resp = CobotMsgs::Response::CreateJoints(builder, joint_entries_vec);
  auto response = CobotMsgs::Response::CreateResponse(
    builder, request_id, CobotMsgs::Response::ResponsePayload_Joints, joints_resp.Union());
  auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
    builder, CobotMsgs::OutgoingMessagePayload_Response, response.Union());
  builder.Finish(outgoing_msg);

  return framing::frame_message(serial_buffer_out, SERIAL_BUFFER_SIZE, builder.GetBufferPointer(),
                                builder.GetSize());
}

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
  int msg_len = framing::check_message(serial_buffer_in, serial_buffer_in_len);
  if (msg_len == 0) return;  // Message is incomplete

  // If the message is invalid, send an error log message and  discard it.
  if (msg_len == -1) {
    int written = msg_helper::write_log(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                                        CobotMsgs::LogLevel_ERROR, "Invalid message received.");

    // Only send the message if it fits in the buffer. Otherwise, ignore it.
    // TODO: Handle this better.
    if (written > 0) {
      serial_buffer_out_len += written;
      Serial.write(serial_buffer_out, serial_buffer_out_len);
      Serial.flush();
    }
    serial_buffer_out_len = 0;

    serial_buffer_in_len = framing::remove_bad_frame(serial_buffer_in, serial_buffer_in_len);
    return;
  }

  // Remove the message from the input buffer.
  serial_buffer_in_len = framing::remove_frame(serial_buffer_in, serial_buffer_in_len);

  // Parse the message as a request.
  flatbuffers::FlatBufferBuilder builder(1024);
  auto incoming_msg = flatbuffers::GetRoot<CobotMsgs::IncomingMessage>(serial_buffer_in);
  auto request = incoming_msg->payload();
  auto request_type = request->payload_type();
  auto request_id = request->message_id();

  // Handle the request and get the number of bytes written to the serial buffer.
  int written;
  switch (request_type) {
    case CobotMsgs::Request::RequestPayload_Init:
      written = handle_init(request_id, request->payload_as_Init());
      break;
    case CobotMsgs::Request::RequestPayload_Calibrate:
      written = handle_calibrate(request_id, request->payload_as_Calibrate());
      break;
    case CobotMsgs::Request::RequestPayload_Override:
      written = handle_override(request_id, request->payload_as_Override());
      break;
    case CobotMsgs::Request::RequestPayload_GetJoints:
      written = handle_get_joints(request_id);
      break;

    default:
      written = msg_helper::write_error_response(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                                                 request_id, CobotMsgs::ErrorCode_MALFORMED_REQUEST,
                                                 "Unknown request type.");
      break;
  }

  // Send the response if it fits in the buffer. Otherwise, log an error.
  if (written > 0) {
    serial_buffer_out_len += written;
    Serial.write(serial_buffer_out, serial_buffer_out_len);
    Serial.flush();
  } else {
    int written =
      msg_helper::write_log(serial_buffer_out, SERIAL_BUFFER_SIZE, builder,
                            CobotMsgs::LogLevel_ERROR, "Serial buffer too small to send response.");
    if (written > 0) {
      serial_buffer_out_len += written;
      Serial.write(serial_buffer_out, serial_buffer_out_len);
      Serial.flush();
    }
  }
  serial_buffer_out_len = 0;
}
