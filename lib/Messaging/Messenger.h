/**
 * @file Messenger.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-01
 */

#ifndef AR3_TEENSY_FIRMWARE__MESSENGER_H
#define AR3_TEENSY_FIRMWARE__MESSENGER_H

#include "MessageReader.h"
#include "MessageWriter.h"
#include "proto/main.h"
#include <Arduino.h>

template <size_t READ_BUFFER_SIZE, size_t WRITE_BUFFER_SIZE>
class Messenger
{
public:
  MessageReader<READ_BUFFER_SIZE> reader;
  MessageWriter<WRITE_BUFFER_SIZE> writer;

  /**
   * Send a log message to the host.
   *
   * @tparam MSG_LEN The length of the message string (including null terminator)
   * @param[in] level The log level of the message
   * @param[in] msg The message string
   * @return  True if the message was successfully written to the buffer, false otherwise
   */
  template <size_t MSG_LEN>
  bool send_log(cobot_proto::LogLevel level, const char* msg)
  {
    writer.clear();

    cobot_proto::LogMessage<MSG_LEN> log_msg;
    log_msg.set_level(level);
    log_msg.mutable_message() = msg;

    cobot_proto::CobotMessage<0, 0, 0, 0, 0, MSG_LEN> cobot_msg;
    cobot_msg.set_log(log_msg);

    if (cobot_msg.serialized_size() < writer.get_available_size()) {
      send_size_error_log();
      return false;
    }

    if (cobot_msg.serialize(writer) != EmbeddedProto::Error::NO_ERRORS) {
      // TODO: handle this somehow
      return false;
    }

    Serial.write(writer.get_buffer(), writer.get_full_buffer_len());
    return true;
  }

  /**
   * Log an error that the message was too large to serialize. This will write a log message to the
   * write buffer. This will clear the write buffer before writing.
   */
  void send_size_error_log()
  {
    writer.clear();

    cobot_proto::LogMessage<32> log_msg;
    log_msg.set_level(cobot_proto::LogLevel::ERROR);
    log_msg.mutable_message() = "Message too large to serialize";

    cobot_proto::CobotMessage<0, 0, 0, 0, 0, 32> msg;
    msg.set_log(log_msg);

    msg.serialize(writer);
    Serial.write(writer.get_buffer(), writer.get_full_buffer_len());
  }
};

#endif