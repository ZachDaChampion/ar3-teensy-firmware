/**
 * @file Messenger.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-01
 */

#include "Messenger.h"
#include <checksum.hpp>

#define START_BYTE 0x24

Messenger::Messenger() {}

int Messenger::write_log_message(uint8_t* dest, uint8_t dest_len, LogLevel level,
                                 const char* message)
{
  packer.clear();
  packer.serialize(level, message);
  size_t msg_len = packer.size();
  if (msg_len + 3 > dest_len) return -1;

  dest[0] = START_BYTE;
  dest[1] = packer.size();
  dest[2] = crc8ccitt(packer.data(), msg_len);
  memcpy(dest + 3, packer.data(), msg_len);

  return msg_len + 3;
}
