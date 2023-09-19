/**
 * @file main.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-01
 *
 * This is the main entrypoint for the COBOT firmware. All of the main functionality is contained
 * here. If the firmware is ever significantly updated, especially if the binary protocol changes,
 * you MUST increment the `FW_VERSION` and `FW_VERSION_STR` macros. They should always be equal.
 *
 * Joint characteristics should be configured in the "Joint configuration" section. Don't mess with
 * these unless you know what you're doing.
 */

#include <Arduino.h>
#include <Joint.h>
#include <framing.h>
#include <Messenger.h>
#include <serialize.h>

#if DEBUGGING
#include "TeensyDebug.h"
#pragma GCC optimize("O0")
#endif

#if COBOT_ID == 0
#include "joints-cobot0.cpp"
#endif

#if COBOT_ID == 1
#include "joints-cobot1.cpp"
#endif

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

  // State-specific data.
  union {
    // CALIBRATING
    struct {
      // Bitfield of joints left to calibrate.
      uint8_t joint_bitfield;
    } calibrating;
  };
};

//                                                                                                //
// ======================================= Configuration ======================================== //
//                                                                                                //

// The firmware version. This must be incremented whenever the firmware is updated, especially if
// the binary protocol changes.
#define FW_VERSION 2
#define FW_VERSION_STR "2"

// The order in which joints are calibrated.
static const uint8_t CALIBRATION_ORDER[] = { 5, 4, 3, 1, 2, 0 };

//                                                                                                //
// ======================================== Global data ========================================= //
//                                                                                                //

// The current state of the cobot.
static CobotState state = { .id = CobotState::IDLE, .msg_id = 0 };
bool initialized = false;
bool message_in_progress = false;

// Serial buffers.
static const size_t SERIAL_BUFFER_SIZE = 1024;
static uint8_t serial_buffer_in[SERIAL_BUFFER_SIZE];
static uint8_t serial_buffer_out[SERIAL_BUFFER_SIZE];
static size_t serial_buffer_in_len = 0;

// The messenger.
Messenger<SERIAL_BUFFER_SIZE> messenger(serial_buffer_out, LogLevel::INFO);

//                                                                                                //
// ====================================== Request handlers ====================================== //
//                                                                                                //

/**
 * Handles an Init request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @param[in] data_len The length of the data buffer.
 * @return  The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *          small.
 */
void handle_init(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (data_len != sizeof(uint32_t)) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is too short.");
  }

  uint32_t expected_fw_version;
  deserialize_uint32(&expected_fw_version, data);

  if (expected_fw_version == FW_VERSION) {
    initialized = true;
    return messenger.send_ack(request_id);
  } else {
    return messenger.send_error_response(request_id, ErrorCode::INVALID_FIRMWARE_VERSION,
                                         "COBOT is running firmware version " FW_VERSION_STR ".");
  }
}

/**
 * Handles a Calibrate request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @param[in] data_len The length of the data buffer.
 * @return  The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *          small.
 */
void handle_calibrate(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }
  if (data_len != 1) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is too short.");
  }

  uint8_t joints_bf = data[0];

  // Verify that no joints are set that don't exist.
  if (joints_bf >> JOINT_COUNT) {
    return messenger.send_error_response(request_id, ErrorCode::INVALID_JOINT,
                                         "The joints bitfield contains bits that don't "
                                         "correspond to any joints.");
  }

  // In order to safely calibrate a joint, all previous joints in the calibration order must already
  // be calibrated. Here, we verify that all necessary joints are calibrated before starting this
  // calibration.
  //
  // To do this, we iterate over the CALIBRATION_ORDER backwards. Once we encounter the first joint
  // that we intend to calibrate, all subsequent joints should either already be calibrated or in
  // joints_bf.
  bool found_first = false;
  for (int i = SIZE(CALIBRATION_ORDER) - 1; i >= 0; --i) {
    auto index = CALIBRATION_ORDER[i];
    bool to_calibrate = joints_bf & (1 << index);
    bool already_calibrated = joints[index].get_is_calibrated();

    if (found_first && !(to_calibrate || already_calibrated)) {
      return messenger.send_error_response(state.msg_id, ErrorCode::NOT_CALIBRATED,
                                           "Joints cannot be safely calibrated.");
    }
    if (to_calibrate) found_first = true;
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, ErrorCode::CANCELLED, "Interrupted by calibration");
  }

  // Stop all joints.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
  }

  // Set the calibrating bitfield so that the update loop knows which joints to calibrate.
  state.calibrating.joint_bitfield = joints_bf;

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
 * @param[in] data_len The length of the data buffer.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_override(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }
  if (data_len % 5 != 0) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is not a multiple of 5 bytes.");
  }
  uint8_t entry_count = data_len / 5;
  if (entry_count > JOINT_COUNT) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is too long.");
  }

  // Create a map from joint index to entry index. Any joint that does not have an entry will be
  // mapped to -1. This will also count the number of entries that were found so that we can verify
  // that all joints were found.
  uint8_t found = 0;
  int8_t map[JOINT_COUNT];
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    map[i] = -1;
    for (size_t j = 0; j < entry_count; ++j) {
      const uint8_t* entry = data + (j * 5);
      if (entry[0] == i) {
        ++found;
        map[i] = j;
        break;
      }
    }
  }

  // Verify that all specified joints were found.
  if (found < entry_count) {
    return messenger.send_error_response(request_id, ErrorCode::INVALID_JOINT,
                                         "Some joints were not found.");
  }

  // Ensure that all override angles are within the joint limits.
  for (size_t i = 0; i < entry_count; ++i) {
    const uint8_t* entry = data + (map[i] * 5);
    int32_t angle;
    deserialize_int32(&angle, entry + 1);
    if (!joints[i].position_within_range(angle)) {
      return messenger.send_error_response(request_id, ErrorCode::OUT_OF_RANGE,
                                           "Some joints are out of range.");
    }
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, ErrorCode::CANCELLED, "Interrupted by override");
  }

  // Stop all joints.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
  }

  // Override the positions of all specified joints.
  for (size_t i = 0; i < entry_count; ++i) {
    const uint8_t* entry = data + (map[i] * 5);
    int32_t angle;
    deserialize_int32(&angle, entry + 1);
    joints[i].override_position(angle);
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
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }

  // Create an array of joint entries.
  JointsResponse joints_resp[JOINT_COUNT];
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints_resp[i].angle = static_cast<int32_t>(joints[i].get_position() * 1000);
    joints_resp[i].speed = static_cast<int32_t>(joints[i].get_speed() * 1000);
  }
  messenger.send_joints_response(request_id, joints_resp, JOINT_COUNT);
}

/**
 * Handles a MoveTo request.
 *
 * @param[in] request_id The ID of the request.
 * @param[in] data The request data.
 * @param[in] data_len The length of the data buffer.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_move_to(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }
  if (data_len % 9 != 0) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is not a multiple of 9 bytes.");
  }
  uint8_t entry_count = data_len / 9;
  if (entry_count > JOINT_COUNT) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is too long.");
  }

  // Create a map from joint index to entry index. Any joint that does not have an entry will be
  // mapped to -1. This will also count the number of entries that were found so that we can verify
  // that all joints were found.
  uint8_t found = 0;
  int8_t map[JOINT_COUNT];
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    map[i] = -1;
    for (size_t j = 0; j < entry_count; ++j) {
      uint8_t joint_id = data[j * 9];
      if (joint_id == i) {
        ++found;
        map[i] = j;
        break;
      }
    }
  }

  // Verify that all specified joints were found.
  if (found < entry_count) {
    return messenger.send_error_response(request_id, ErrorCode::INVALID_JOINT,
                                         "Some joints were not found.");
  }

  // Ensure that all new positions are within the joint and speed limits. Speeds must be
  // non-negative to be valid.
  for (size_t i = 0; i < entry_count; ++i) {
    if (map[i] == -1) continue;
    const uint8_t* entry = data + (map[i] * 9);

    int32_t angle;
    deserialize_int32(&angle, entry + 1);
    int32_t speed;
    deserialize_int32(&speed, entry + 5);

    if (!joints[i].position_within_range(angle)) {
      return messenger.send_error_response(request_id, ErrorCode::OUT_OF_RANGE,
                                           "Some joint positions are out of range.");
    }
    if (speed < 0) {
      return messenger.send_error_response(request_id, ErrorCode::OUT_OF_RANGE,
                                           "Some joint speeds are negative.");
    }
    if (!joints[i].speed_within_range(speed)) {
      return messenger.send_error_response(request_id, ErrorCode::OUT_OF_RANGE,
                                           "Some joint speeds are out of range.");
    }
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, ErrorCode::CANCELLED, "Interrupted by move");
  }

  // Stop all joints immediately.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
  }

  // Move all specified joints to their target positions.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    if (map[i] != -1) {
      const uint8_t* entry = data + (map[i] * 9);

      int32_t angle;
      deserialize_int32(&angle, entry + 1);
      int32_t speed;
      deserialize_int32(&speed, entry + 5);

      if (speed == 0) {
        joints[i].move_to_auto(angle);
      } else
        joints[i].move_to_speed(angle, speed);
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
 * @param[in] data_len The length of the data buffer.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_move_speed(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }
  if (data_len % 5 != 0) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is not a multiple of 5 bytes.");
  }
  uint8_t entry_count = data_len / 5;
  if (entry_count > JOINT_COUNT) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is too long.");
  }

  // Create a map from joint index to entry index. Any joint that does not have an entry will be
  // mapped to -1. This will also count the number of entries that were found so that we can verify
  // that all joints were found.
  uint8_t found = 0;
  int8_t map[JOINT_COUNT];
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    map[i] = -1;
    for (size_t j = 0; j < entry_count; ++j) {
      const uint8_t* entry = data + (j * 5);
      uint8_t joint_id = entry[0];
      if (joint_id == i) {
        ++found;
        map[i] = j;
        break;
      }
    }
  }

  // Verify that all specified joints were found.
  if (found < entry_count) {
    return messenger.send_error_response(request_id, ErrorCode::INVALID_JOINT,
                                         "Some joints were not found.");
  }

  // Ensure that all speeds are within the joint limits. Speeds may be negative to indicate
  // backwards motion.
  for (size_t i = 0; i < entry_count; ++i) {
    if (map[i] == -1) continue;
    const uint8_t* entry = data + (map[i] * 5);

    int32_t speed;
    deserialize_int32(&speed, entry + 1);

    if (!joints[i].speed_within_range(speed)) {
      return messenger.send_error_response(request_id, ErrorCode::OUT_OF_RANGE,
                                           "Some joint speeds are out of range.");
    }
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, ErrorCode::CANCELLED, "Interrupted by move");
  }

  // Stop all joints immediately.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].stop(false);
  }

  // Move all specified joints at their target speeds.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    if (map[i] != -1) {
      if (map[i] == -1) continue;
      const uint8_t* entry = data + (map[i] * 5);

      int32_t speed;
      deserialize_int32(&speed, entry + 1);

      joints[i].move_forever_speed(speed);
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
 * @param[in] data_len The length of the data buffer.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_stop(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }
  if (data_len != 2) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is too short.");
  }

  uint8_t immediate = data[0];
  uint8_t joints_bf = data[1];

  // Verify that no joints are set that don't exist.
  if (joints_bf >> JOINT_COUNT) {
    return messenger.send_error_response(request_id, ErrorCode::INVALID_JOINT,
                                         "The joints bitfield contains bits that don't "
                                         "correspond to any joints.");
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, ErrorCode::CANCELLED, "Interrupted by stop");
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
 * @param[in] data_len The length of the data buffer.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_go_home(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }
  if (data_len != 1) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is not 1 byte.");
  }

  uint8_t joints_bf = data[0];

  // Verify that no joints are set that don't exist.
  if (joints_bf >> JOINT_COUNT) {
    return messenger.send_error_response(request_id, ErrorCode::INVALID_JOINT,
                                         "The joints bitfield contains bits that don't "
                                         "correspond to any joints.");
  }

  // If we are interrupting an active process, respond to it with an error.
  if (state.id != CobotState::IDLE) {
    messenger.send_error_response(state.msg_id, ErrorCode::CANCELLED, "Interrupted by go home");
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
    messenger.send_error_response(state.msg_id, ErrorCode::CANCELLED, "Interrupted by reset");
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
 * @param[in] data_len The length of the data buffer.
 * @return The number of bytes written to the serial buffer, or -1 if the serial buffer was too
 *         small.
 */
void handle_set_log_level(uint32_t request_id, const uint8_t* data, uint8_t data_len)
{
  if (!initialized) {
    return messenger.send_error_response(request_id, ErrorCode::NOT_INITIALIZED, "");
  }
  if (data_len != 1) {
    return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                         "The request data is not 1 byte.");
  }

  uint8_t new_log_level = data[0];
  switch (new_log_level) {
    case static_cast<uint8_t>(LogLevel::DEBUG):
    case static_cast<uint8_t>(LogLevel::INFO):
    case static_cast<uint8_t>(LogLevel::WARN):
    case static_cast<uint8_t>(LogLevel::ERROR):
      messenger.log_level = static_cast<const LogLevel>(new_log_level);
      return messenger.send_ack(request_id);
    default:
      return messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
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

#if DEBUGGING
  // Start debug serial communication.
  debug.begin(SerialUSB1);
#endif

  // Initialize the joints.
  for (size_t i = 0; i < JOINT_COUNT; ++i) {
    joints[i].init();
  }
}

void loop()
{
  // Update all joints.
  for (auto& joint : joints) {
    joint.update();
  }

  // Update the state of the cobot.
  switch (state.id) {
    // In the IDLE state, do nothing.
    case CobotState::IDLE:
      break;

    // In the CALIBRATING state, check if a joint is still calibrating. If not, start calibrating
    // the next joint. If all joints are calibrated, send a done response and transition to the IDLE
    // state.
    case CobotState::CALIBRATING: {
      // Check if any joints are actively calibrating.
      bool all_stopped = true;
      for (auto& joint : joints) {
        if (joint.get_state()->id == Joint::State::CALIBRATING) {
          all_stopped = false;
          break;
        }
      }

      // If all joints are calibrated, send a done response and transition to the IDLE state.
      if (state.calibrating.joint_bitfield == 0) {
        messenger.send_done(state.msg_id);
        state.id = CobotState::IDLE;
        state.msg_id = 0;
      }

      // If all joints are stopped but there are still joints left to calibrate, start calibrating
      // the next joint in the calibration order.
      else if (all_stopped) {
        for (auto index : CALIBRATION_ORDER) {
          if (state.calibrating.joint_bitfield & (1 << index)) {
            joints[index].calibrate();
            state.calibrating.joint_bitfield &= ~(1 << index);
            break;
          }
        }
      }
    } break;

    // In the STOPPING, MOVE_TO, and MOVE_SPEED states, check if all joints are idle.
    // If so, send a done response and transition to the IDLE state.
    case CobotState::STOPPING:
    case CobotState::MOVE_TO:
    case CobotState::MOVE_SPEED: {
      bool all_stopped = true;
      for (auto& joint : joints) {
        if (joint.get_state()->id != Joint::State::IDLE) {
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
    messenger.log(LogLevel::ERROR, "Invalid message received.");
    serial_buffer_in_len = framing::remove_bad_frame(serial_buffer_in, serial_buffer_in_len);
    return;
  }

  // Parse the message as a request.
  if (msg_len < 5) {
    messenger.log(LogLevel::ERROR, "Message is too short to be a request.");
    serial_buffer_in_len = framing::remove_bad_frame(serial_buffer_in, serial_buffer_in_len);
    return;
  }
  uint8_t msg_payload_len = msg_len - 5;
  const uint8_t* msg = serial_buffer_in + (serial_buffer_in_len - msg_len);
  uint8_t request_type = msg[0];
  int32_t request_id;
  deserialize_int32(&request_id, msg + 1);

  // Handle the request.
  switch (request_type) {
    case static_cast<uint8_t>(Request::Init):
      handle_init(request_id, msg + 5, msg_payload_len);
      break;
    case static_cast<uint8_t>(Request::Calibrate):
      handle_calibrate(request_id, msg + 5, msg_payload_len);
      break;
    case static_cast<uint8_t>(Request::Override):
      handle_override(request_id, msg + 5, msg_payload_len);
      break;
    case static_cast<uint8_t>(Request::GetJoints):
      handle_get_joints(request_id);
      break;
    case static_cast<uint8_t>(Request::MoveTo):
      handle_move_to(request_id, msg + 5, msg_payload_len);
      break;
    case static_cast<uint8_t>(Request::MoveSpeed):
      handle_move_speed(request_id, msg + 5, msg_payload_len);
      break;
    case static_cast<uint8_t>(Request::Stop):
      handle_stop(request_id, msg + 5, msg_payload_len);
      break;
    case static_cast<uint8_t>(Request::GoHome):
      handle_go_home(request_id, msg + 5, msg_payload_len);
      break;
    case static_cast<uint8_t>(Request::Reset):
      handle_reset(request_id);
      break;
    case static_cast<uint8_t>(Request::SetLogLevel):
      handle_set_log_level(request_id, msg + 5, msg_payload_len);
      break;

    default:
      messenger.send_error_response(request_id, ErrorCode::MALFORMED_REQUEST,
                                    "Unknown request type.");
      break;
  }

  // Remove the message from the input buffer.
  serial_buffer_in_len = framing::remove_frame(serial_buffer_in, serial_buffer_in_len);
}
