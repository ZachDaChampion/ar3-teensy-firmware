/**
 * @file Messenger.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-01
 */

#ifndef AR3_TEENSY_FIRMWARE__MESSENGER_H
#define AR3_TEENSY_FIRMWARE__MESSENGER_H

#include <stdint.h>
#include <MsgPack.h>

namespace messaging
{

  static const uint8_t START_BYTE = 0x24;
  static const uint8_t

class Messenger
{
public:
  enum LogLevel { LOG_DEBUG = 0, LOG_INFO = 1, LOG_WARN = 2, LOG_ERROR = 3 };

  Messenger();

  /**
   * Write a log message to the given buffer.
   *
   * @param[out] dest The buffer to write to.
   * @param[in] dest_len The length of the buffer.
   * @param[in] level The log level of the message.
   * @param[in] message The message to write.
   * @return The number of bytes written to the buffer, or -1 if the buffer is too small.
   */
  int write_log_message(uint8_t* dest, uint8_t dest_len, LogLevel level, const char* message);

private:
  MsgPack::Unpacker unpacker;
  MsgPack::Packer packer;
};

}  // namespace messaging

#endif