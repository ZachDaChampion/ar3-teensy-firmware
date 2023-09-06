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
#include <Messenger.h>

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
    IDLE,         // The cobot is not moving
    STOPPING,     // The cobot is stopping
    CALIBRATING,  // The cobot is calibrating
    MOVE_TO,      // The cobot is moving to a specified position
    MOVE_SPEED,   // The cobot is moving indefinitely at a specified speed
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
bool message_in_progress = false;

// Flatbuffers builder.
static flatbuffers::FlatBufferBuilder builder(1024);

// Serial buffers.
static const size_t SERIAL_BUFFER_SIZE = 1024;
static uint8_t serial_buffer_in[SERIAL_BUFFER_SIZE];
static uint8_t serial_buffer_out[SERIAL_BUFFER_SIZE];
static size_t serial_buffer_in_len = 0;

// The messenger.
Messenger<SERIAL_BUFFER_SIZE> messenger(&builder);

//                                                                                                //
// ====================================== Request handlers ====================================== //
//                                                                                                //

/**
 * Handles an Init request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return  The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *          small.
 */
void handle_init(uint32_t request_id, const CobotMsgs::Request::Init* data)
{
  if (data->expected_fw_version() == FW_VERSION) {
    initialized = true;
    return messenger.send_ack(request_id);
  } else {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_INVALID_FIRMWARE_VERSION,
                                         "COBOT is running firmware version " FW_VERSION_STR ".");
  }
}

/**
 * Handles a Calibrate request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return  The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *          small.
 */
void handle_calibrate(uint32_t request_id, const CobotMsgs::Request::Calibrate* data)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  uint8_t joints_bf = data->joints_bitfield();

  // Verify that no joints are set that don't exist.
  if (joints_bf >> JOINT_COUNT) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                         "The joints bitfield contains bits that don't "
                                         "correspond to any joints.");
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, CobotMsgs::ErrorCode_CANCELLED,
                                  "Interrupted by calibration");
  }

  // Stop all joints and calibrate the specified joints.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
    if (joints_bf & (1 << i)) {
      joints[i].calibrate();
    }
  }

  // Set the state to CALIBRATING and respond to the request with an ACK.
  state.id = CobotState::CALIBRATING;
  state.msg_id = request_id;
  messenger.send_ack(request_id);
}

/**
 * Handles an Override request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_override(uint32_t request_id, const CobotMsgs::Request::Override* data)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  auto entries = data->entries();
  auto entry_count = entries->size();

  // Create a map from joint index to entry index. Any joint that does not have an entry will be
  // mapped to -1. This will also count the number of entries that were found so that we can verify
  // that all joints were found.
  uint8_t found = 0;
  int8_t map[JOINT_COUNT];
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    map[i] = -1;
    for (size_t j = 0; j < entry_count; ++j) {
      auto entry = entries->Get(j);
      if (entry->joint_id() == i) {
        ++found;
        map[i] = j;
        break;
      }
    }
  }

  // Verify that all specified joints were found.
  if (found < entry_count) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                         "Some joints were not found.");
  }

  // Ensure that all override angles are within the joint limits.
  for (size_t i = 0; i < entry_count; ++i) {
    auto entry = entries->Get(map[i]);
    if (!joints[i].position_within_range(entry->angle())) {
      return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_OUT_OF_RANGE,
                                           "Some joints are out of range.");
    }
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, CobotMsgs::ErrorCode_CANCELLED,
                                  "Interrupted by override");
  }

  // Stop all joints.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
  }

  // Override the positions of all specified joints.
  for (size_t i = 0; i < entry_count; ++i) {
    auto entry = entries->Get(map[i]);
    joints[i].override_position(entry->angle());
  }

  // Set the state to IDLE and respond to the request with an ACK.
  state.id = CobotState::IDLE;
  state.msg_id = request_id;
  messenger.send_ack(request_id);
}

/**
 * Handles a GetJoints request.
 *
 * @param[in] request_id The ID of the request.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_get_joints(uint32_t request_id)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
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

  // Send the outgoing message.
  int written = framing::frame_message(serial_buffer_out, SERIAL_BUFFER_SIZE,
                                       builder.GetBufferPointer(), builder.GetSize());
  if (written > 0) Serial.write(serial_buffer_out, written);
}

/**
 * Handles a MoveTo request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_move_to(uint32_t request_id, const CobotMsgs::Request::MoveTo* data)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  auto entries = data->entries();

  // Create a map from joint index to entry index. Any joint that does not have an entry will be
  // mapped to -1. This will also count the number of entries that were found so that we can verify
  // that all joints were found.
  uint8_t found = 0;
  int8_t map[JOINT_COUNT];
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    map[i] = -1;
    for (size_t j = 0; j < entries->size(); ++j) {
      auto entry = entries->Get(j);
      if (entry->joint_id() == i) {
        ++found;
        map[i] = j;
        break;
      }
    }
  }

  // Verify that all specified joints were found.
  if (found < entries->size()) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                         "Some joints were not found.");
  }

  // Ensure that all new positions are within the joint and speed limits. Speeds must be
  // non-negative to be valid.
  for (size_t i = 0; i < entries->size(); ++i) {
    if (map[i] == -1) continue;
    auto entry = entries->Get(map[i]);
    if (!joints[i].position_within_range(entry->angle())) {
      return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_OUT_OF_RANGE,
                                           "Some joint positions are out of range.");
    }
    if (entry->speed() < 0) {
      return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_OUT_OF_RANGE,
                                           "Some joint speeds are negative.");
    }
    if (!joints[i].speed_within_range(entry->speed())) {
      return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_OUT_OF_RANGE,
                                           "Some joint speeds are out of range.");
    }
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, CobotMsgs::ErrorCode_CANCELLED,
                                  "Interrupted by move");
  }

  // Stop all joints immediately.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
  }

  // Move all specified joints to their target positions.
  for (size_t i = 0; i < entries->size(); ++i) {
    if (map[i] != -1) {
      auto entry = entries->Get(map[i]);
      if (entry->speed() == 0)
        joints[i].move_to_auto(entry->angle());
      else
        joints[i].move_to_speed(entry->angle(), entry->speed());
    } else {
      joints[i].stop(false);
    }
  }

  // Set the state to MOVE_TO and respond to the request with an ACK.
  state.id = CobotState::MOVE_TO;
  state.msg_id = request_id;
  messenger.send_ack(request_id);
}

/**
 * Handles a MoveSpeed request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_move_speed(uint32_t request_id, const CobotMsgs::Request::MoveSpeed* data)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  auto entries = data->entries();

  // Create a map from joint index to entry index. Any joint that does not have an entry will be
  // mapped to -1. This will also count the number of entries that were found so that we can verify
  // that all joints were found.
  uint8_t found = 0;
  int8_t map[JOINT_COUNT];
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    map[i] = -1;
    for (size_t j = 0; j < entries->size(); ++j) {
      auto entry = entries->Get(j);
      if (entry->joint_id() == i) {
        ++found;
        map[i] = j;
        break;
      }
    }
  }

  // Verify that all specified joints were found.
  if (found < entries->size()) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                         "Some joints were not found.");
  }

  // Ensure that all speeds are within the joint limits. Speeds may be negative to indicate
  // backwards motion.
  for (size_t i = 0; i < entries->size(); ++i) {
    if (map[i] == -1) continue;
    auto entry = entries->Get(map[i]);
    if (!joints[i].speed_within_range(entry->speed())) {
      return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_OUT_OF_RANGE,
                                           "Some joint speeds are out of range.");
    }
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, CobotMsgs::ErrorCode_CANCELLED,
                                  "Interrupted by move");
  }

  // Stop all joints immediately.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
  }

  // Move all specified joints at their target speeds.
  for (size_t i = 0; i < entries->size(); ++i) {
    if (map[i] != -1) {
      auto entry = entries->Get(map[i]);
      joints[i].move_forever_speed(entry->speed());
    } else {
      joints[i].stop(false);
    }
  }

  // Set the state to MOVE_SPEED and respond to the request with an ACK.
  state.id = CobotState::MOVE_SPEED;
  state.msg_id = request_id;
  messenger.send_ack(request_id);
}

/**
 * Handles a Stop request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_stop(uint32_t request_id, const CobotMsgs::Request::Stop* data)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  auto immediate = data->immediate();
  auto joints_bf = data->joints_bitfield();

  // Verify that no joints are set that don't exist.
  if (joints_bf >> JOINT_COUNT) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                         "The joints bitfield contains bits that don't "
                                         "correspond to any joints.");
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, CobotMsgs::ErrorCode_CANCELLED,
                                  "Interrupted by stop");
  }

  // Stop all specified joints. This will stop them smoothly only if immediate is false AND the
  // joints are calibrated.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    if (joints_bf & (1 << i)) {
      joints[i].stop(joints[i].get_is_calibrated() && !immediate);
    }
  }

  // Set the state to STOPPING and respond to the request with an ACK.
  state.id = CobotState::STOPPING;
  state.msg_id = request_id;
  messenger.send_ack(request_id);
}

/**
 * Handles a GoHome request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_go_home(uint32_t request_id, const CobotMsgs::Request::GoHome* data)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_NOT_INITIALIZED, "");
  }
  auto joints_bf = data->joints_bitfield();

  // Verify that no joints are set that don't exist.
  if (joints_bf >> JOINT_COUNT) {
    return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_INVALID_JOINT,
                                         "The joints bitfield contains bits that don't "
                                         "correspond to any joints.");
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, CobotMsgs::ErrorCode_CANCELLED,
                                  "Interrupted by go home");
  }

  // Stop all joints and move the specified joints to their home positions.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
    if (joints_bf & (1 << i)) {
      joints[i].move_to_auto(0);
    }
  }

  state.id = CobotState::MOVE_TO;
  state.msg_id = request_id;
  return messenger.send_ack(request_id);
}

/**
 * Handles a Reset request.
 *
 * @param[in] request_id The ID of the request.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_reset(uint32_t request_id)
{
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, CobotMsgs::ErrorCode_CANCELLED,
                                  "Interrupted by reset");
  }

  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].reset();
  }
  state.id = CobotState::IDLE;
  state.msg_id = 0;
  return messenger.send_ack(request_id);
}

/**
 * Handles a SetLogLevel request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_set_log_level(uint32_t request_id, const CobotMsgs::Request::SetLogLevel* data)
{
  auto new_log_level = data->log_level();
  switch (new_log_level) {
    case CobotMsgs::LogLevel_DEBUG:
    case CobotMsgs::LogLevel_INFO:
    case CobotMsgs::LogLevel_WARN:
    case CobotMsgs::LogLevel_ERROR:
      messenger.log_level = new_log_level;
      return messenger.send_ack(request_id);
    default:
      return messenger.send_error_response(request_id, CobotMsgs::ErrorCode_MALFORMED_REQUEST,
                                           "Invalid log level.");
  }
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

  // Update the state of the cobot.
  switch (state.id) {
    // In the IDLE state, do nothing.
    case CobotState::IDLE:
      break;

    // In the STOPPING, CALIBRATING, MOVE_TO, and MOVE_SPEED states, check if all joints are idle.
    // If so, send a done response and transition to the IDLE state.
    case CobotState::STOPPING:
    case CobotState::CALIBRATING:
    case CobotState::MOVE_TO:
    case CobotState::MOVE_SPEED: {
      bool all_stopped = true;
      for (auto joint : joints) {
        if (joint.get_state().id != Joint::State::IDLE) {
          all_stopped = false;
          break;
        }
      }
      if (all_stopped) {
        messenger.send_done(state.msg_id);
        state.id = CobotState::IDLE;
        state.msg_id = 0;
      }
      break;
    }
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
    messenger.log(CobotMsgs::LogLevel_ERROR, "Invalid message received.");
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

  // Handle the request.
  switch (request_type) {
    case CobotMsgs::Request::RequestPayload_Init:
      handle_init(request_id, request->payload_as_Init());
      break;
    case CobotMsgs::Request::RequestPayload_Calibrate:
      handle_calibrate(request_id, request->payload_as_Calibrate());
      break;
    case CobotMsgs::Request::RequestPayload_Override:
      handle_override(request_id, request->payload_as_Override());
      break;
    case CobotMsgs::Request::RequestPayload_GetJoints:
      handle_get_joints(request_id);
      break;
    case CobotMsgs::Request::RequestPayload_MoveTo:
      handle_move_to(request_id, request->payload_as_MoveTo());
      break;
    case CobotMsgs::Request::RequestPayload_MoveSpeed:
      handle_move_speed(request_id, request->payload_as_MoveSpeed());
      break;
    case CobotMsgs::Request::RequestPayload_Stop:
      handle_stop(request_id, request->payload_as_Stop());
      break;
    case CobotMsgs::Request::RequestPayload_GoHome:
      handle_go_home(request_id, request->payload_as_GoHome());
      break;
    case CobotMsgs::Request::RequestPayload_Reset:
      handle_reset(request_id);
      break;
    case CobotMsgs::Request::RequestPayload_SetLogLevel:
      handle_set_log_level(request_id, request->payload_as_SetLogLevel());
      break;

    default:
      messenger.send_error_response(request_id, CobotMsgs::ErrorCode_MALFORMED_REQUEST,
                                    "Unknown request type.");
      break;
  }
}
