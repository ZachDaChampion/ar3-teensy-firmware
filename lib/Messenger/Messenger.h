/**
 * @file Messenger.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-06
 */

#ifndef AR3_TEENSY_FIRMWARE__MESSENGER_H
#define AR3_TEENSY_FIRMWARE__MESSENGER_H

#include <framing.h>
#include <Arduino.h>
#include <serialize.h>

/**
 * Error codes for the error response.
 */
enum class ErrorCode {
  OTHER = 0,
  MALFORMED_REQUEST = 1,
  OUT_OF_RANGE = 2,
  INVALID_JOINT = 3,
  NOT_INITIALIZED = 4,
  NOT_CALIBRATED = 5,
  CANCELLED = 6,
  INVALID_FIRMWARE_VERSION = 7,
};

/**
 * The log level of a log message.
 */
enum class LogLevel {
  DEBUG = 0,  // The lowest log level. Used for debugging. Should not be used in production.
  INFO = 1,   // Used for general information.
  WARN = 2,   // Used for warnings.
  ERROR = 3,  // Used for errors.
  NONE = 4    // Used to disable logging.
};

/**
 * The type of an outgoing message.
 */
enum class OutgoingMessage {
  Log = 0,
  Response = 1,
};

/**
 * The type of a response message.
 */
enum class Response {
  Ack = 0,
  Done = 1,
  Error = 2,
  Joints = 3,
};

/**
 * The type of a request message.
 */
enum class Request {
  Init = 0,
  Calibrate = 1,
  Override = 2,
  GetJoints = 3,
  MoveTo = 4,
  MoveSpeed = 5,
  FollowTrajectory = 6,
  Stop = 7,
  GoHome = 8,
  Reset = 9,
  SetLogLevel = 10,
  SetFeedback = 11,
};

#define MESSAGE_SIZE (BUFFER_SIZE - 3)

/**
 * Data structure for a single joint's response.
 */
struct JointsResponse {
  int32_t angle;  // in degrees * 10^-3
  int32_t speed;  // in degrees * 10^-3 / second
};

template <size_t BUFFER_SIZE>
class Messenger
{
public:
  // Output buffer used to frame outgoing messages.
  uint8_t* out_buffer;

  // Output buffer of the message itself. This is inside the out_buffer.
  uint8_t* out_message = this->out_buffer + 3;

  // The current log level.
  LogLevel log_level = LogLevel::INFO;

  /**
   * Construct a new Messenger object.
   *
   * @param out_buffer The output buffer to use for framing outgoing messages.
   * @param log_level The log level to use.
   */
  Messenger(uint8_t* out_buffer, LogLevel log_level = LogLevel::INFO)
    : out_buffer(out_buffer), log_level(log_level)
  {
  }

  /**
   * Writes a log message to Serial if the log level is high enough.
   *
   * @param[in] level The log level of the message.
   * @param[in] message The message to log.
   */
  void log(LogLevel level, const char* message)
  {
    if (level < this->log_level) return;

    // Calculate the length of the message.
    int message_len = strlen(message);
    if (message_len < 0) return;
    uint8_t full_message_len = message_len + 1 + 2;  // +1 for log, +2 for level and string length.
    if (full_message_len + 3u > BUFFER_SIZE) return;

    // Create the message.
    this->out_message[0] = static_cast<uint8_t>(OutgoingMessage::Log);
    this->out_message[1] = static_cast<uint8_t>(level);
    this->out_message[2] = static_cast<uint8_t>(message_len);
    memcpy(this->out_message + 3, message, message_len);

    // Frame the message.
    int written = framing::frame_message_inline(this->out_buffer, BUFFER_SIZE, full_message_len);
    if (written > 0) Serial.write(this->out_buffer, written);
  }

  /**
   * Writes an ack response to serial.
   *
   * @param[in] msg_id The ID of the message that this is a response to.
   */
  void send_ack(uint32_t msg_id)
  {
    // 3 bytes for framing, 1 for response, 1 for response type, 4 for msg_id.
    static_assert(BUFFER_SIZE >= 3 + 1 + 1 + 4, "Buffer is too small to send ack response");

    this->out_message[0] = static_cast<uint8_t>(OutgoingMessage::Response);
    this->out_message[1] = static_cast<uint8_t>(Response::Ack);
    serialize_uint32(this->out_message + 2, MESSAGE_SIZE, msg_id);
    int written = framing::frame_message_inline(this->out_buffer, BUFFER_SIZE, 6);
    if (written > 0) Serial.write(this->out_buffer, written);
  }

  /**
   * Writes a done response to serial.
   *
   * @param[in] msg_id The ID of the message that this is a response to.
   */
  void send_done(uint32_t msg_id)
  {
    // 3 bytes for framing, 1 for response, 1 for response type, 4 for msg_id.
    static_assert(BUFFER_SIZE >= 3 + 1 + 1 + 4, "Buffer is too small to send done response");

    this->out_message[0] = static_cast<uint8_t>(OutgoingMessage::Response);
    this->out_message[1] = static_cast<uint8_t>(Response::Done);
    serialize_uint32(this->out_message + 2, MESSAGE_SIZE, msg_id);
    int written = framing::frame_message_inline(this->out_buffer, BUFFER_SIZE, 6);
    if (written > 0) Serial.write(this->out_buffer, written);
  }

  /**
   * Writes an error response to serial.
   *
   * @param[in] msg_id The ID of the message that this is a response to.
   * @param[in] error_code The error code to send.
   * @param[in] error_msg The error message to send.
   */
  void send_error_response(uint32_t msg_id, ErrorCode error_code, const char* error_msg)
  {
    int error_msg_len = strlen(error_msg);
    if (error_msg_len < 0) return;
    if (msg_id == 0) return;

    // +1 for response, +1 for response type, +4 for msg_id, +2 for error code and error message
    // length.
    uint8_t full_message_len = error_msg_len + 1 + 1 + 4 + 2;
    if (full_message_len + 3u > BUFFER_SIZE) return;

    this->out_message[0] = static_cast<uint8_t>(OutgoingMessage::Response);
    this->out_message[1] = static_cast<uint8_t>(Response::Error);
    serialize_uint32(this->out_message + 2, MESSAGE_SIZE, msg_id);
    this->out_message[6] = static_cast<uint8_t>(error_code);
    this->out_message[7] = static_cast<uint8_t>(error_msg_len);
    memcpy(this->out_message + 8, error_msg, error_msg_len);
    int written = framing::frame_message_inline(this->out_buffer, BUFFER_SIZE, full_message_len);
    if (written > 0) Serial.write(this->out_buffer, written);
  }

  /**
   * Writes a joints response to serial.
   *
   * @param[in] msg_id The ID of the message that this is a response to.
   * @param[in] joints The joints to send.
   * @param[in] num_joints The number of joints to send.
   */
  void send_joints_response(uint32_t msg_id, JointsResponse* joints, uint8_t num_joints)
  {
    // +1 for response, +1 for response type, +4 for msg_id, +1 for num_joints, +8 for each joint.
    uint8_t full_message_len = 1 + 1 + 4 + 1 + 8 * num_joints;
    if (full_message_len + 3u > BUFFER_SIZE) return;

    this->out_message[0] = static_cast<uint8_t>(OutgoingMessage::Response);
    this->out_message[1] = static_cast<uint8_t>(Response::Joints);
    serialize_uint32(this->out_message + 2, MESSAGE_SIZE, msg_id);
    this->out_message[6] = num_joints;
    for (int i = 0; i < num_joints; i++) {
      serialize_int32(this->out_message + 7 + 8 * i, MESSAGE_SIZE, joints[i].angle);
      serialize_int32(this->out_message + 11 + 8 * i, MESSAGE_SIZE, joints[i].speed);
    }
    int written = framing::frame_message_inline(this->out_buffer, BUFFER_SIZE, full_message_len);
    if (written > 0) Serial.write(this->out_buffer, written);
  }
};

#endif