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
#include <main_generated.h>
#include <Arduino.h>

template <size_t BUFFER_SIZE>
class Messenger
{
public:
  // Output buffer used to frame outgoing messages.
  uint8_t out_buffer[BUFFER_SIZE];

  // The flatbuffer builder used to build outgoing messages.
  flatbuffers::FlatBufferBuilder* builder;

  // The current log level.
  CobotMsgs::LogLevel log_level = CobotMsgs::LogLevel::LogLevel_INFO;

  /**
   * Construct a new Messenger object without a FlatBufferBuilder.
   */
  Messenger() : builder(nullptr) {}

  /**
   * Construct a new Messenger object with a FlatBufferBuilder.
   *
   * @param[in] builder The FlatBufferBuilder to use to build outgoing messages.
   */
  Messenger(flatbuffers::FlatBufferBuilder* builder) : builder(builder) {}

  /**
   * Writes a log message to Serial if the log level is high enough.
   *
   * @param[in] level The log level of the message.
   * @param[in] message The message to log.
   */
  void log(CobotMsgs::LogLevel level, const char* message)
  {
    if (level < this->log_level) return;

    this->builder->Clear();
    auto log_msg_str = this->builder->CreateString(message);
    auto log_msg = CobotMsgs::CreateLogMessage(*this->builder, level, log_msg_str);
    auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
      *this->builder, CobotMsgs::OutgoingMessagePayload_LogMessage, log_msg.Union());
    this->builder->Finish(outgoing_msg);

    int written = framing::frame_message(
      this->out_buffer, BUFFER_SIZE, this->builder->GetBufferPointer(), this->builder->GetSize());
    if (written > 0) Serial.write(this->out_buffer, written);
  }

  /**
   * Writes an ack response to serial.
   *
   * @param[in] msg_id The ID of the message that this is a response to.
   */
  void send_ack(uint32_t msg_id)
  {
    this->builder->Clear();
    auto ack = CobotMsgs::Response::CreateAck(*this->builder);
    auto response = CobotMsgs::Response::CreateResponse(
      *this->builder, msg_id, CobotMsgs::Response::ResponsePayload_Ack, ack.Union());
    auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
      *this->builder, CobotMsgs::OutgoingMessagePayload_Response, response.Union());
    this->builder->Finish(outgoing_msg);

    int written = framing::frame_message(
      this->out_buffer, BUFFER_SIZE, this->builder->GetBufferPointer(), this->builder->GetSize());
    if (written > 0) Serial.write(this->out_buffer, written);
  }

  /**
   * Writes a done response to serial.
   *
   * @param[in] msg_id The ID of the message that this is a response to.
   */
  void send_done(uint32_t msg_id)
  {
    this->builder->Clear();
    auto done = CobotMsgs::Response::CreateDone(*this->builder);
    auto response = CobotMsgs::Response::CreateResponse(
      *this->builder, msg_id, CobotMsgs::Response::ResponsePayload_Done, done.Union());
    auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
      *this->builder, CobotMsgs::OutgoingMessagePayload_Response, response.Union());
    this->builder->Finish(outgoing_msg);

    int written = framing::frame_message(
      this->out_buffer, BUFFER_SIZE, this->builder->GetBufferPointer(), this->builder->GetSize());
    if (written > 0) Serial.write(this->out_buffer, written);
  }

  /**
   * Writes an error response to serial.
   *
   * @param[in] msg_id The ID of the message that this is a response to.
   * @param[in] error_code The error code to send.
   * @param[in] error_msg The error message to send.
   */
  void send_error_response(uint32_t msg_id, CobotMsgs::ErrorCode error_code, const char* error_msg)
  {
    this->builder->Clear();
    auto error_msg_str = this->builder->CreateString(error_msg);
    auto error = CobotMsgs::Response::CreateError(*this->builder, error_code, error_msg_str);
    auto response = CobotMsgs::Response::CreateResponse(
      *this->builder, msg_id, CobotMsgs::Response::ResponsePayload_Error, error.Union());
    auto outgoing_msg = CobotMsgs::CreateOutgoingMessage(
      *this->builder, CobotMsgs::OutgoingMessagePayload_Response, response.Union());
    this->builder->Finish(outgoing_msg);

    int written = framing::frame_message(
      this->out_buffer, BUFFER_SIZE, this->builder->GetBufferPointer(), this->builder->GetSize());
    if (written > 0) Serial.write(this->out_buffer, written);
  }
};

#endif