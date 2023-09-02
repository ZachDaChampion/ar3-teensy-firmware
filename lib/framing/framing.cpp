/**
 * @file framing.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 * 
 * @version 1.0
 * @date 2023-08-28
 */

#include "framing.h"
#include "messaging.h"
#include <checksum.hpp>
#include <cstring>

int framed_template(uint8_t* dest, uint8_t dest_len)
{
  if (dest_len < 3) return -1;
  dest[0] = START_BYTE;
  dest[1] = 0;
  dest[2] = 0;
  return 3;
}

int framed_finalize(uint8_t* dest, int dest_len, uint8_t msg_len)
{
  if (dest_len < msg_len + 3) return -1;
  dest[1] = msg_len;
  dest[2] = crc8ccitt(dest + 3, msg_len);
  return msg_len + 3;
}

int frame_message(uint8_t* dest, uint8_t dest_len, const uint8_t* src, uint8_t src_len)
{
  int frame_len = framed_template(dest, dest_len);
  if (frame_len == -1) return -1;

  memcpy(dest + frame_len, src, src_len);
  return framed_finalize(dest, dest_len, src_len);
}

int check_message(const uint8_t* buffer, uint8_t buffer_len)
{
  if (buffer_len < 3) return 0;
  if (buffer[0] != START_BYTE) return -1;

  uint8_t msg_len = buffer[1];
  if (buffer_len < msg_len + 3) return 0;

  uint8_t crc = crc8ccitt(buffer + 3, msg_len);
  if (crc != buffer[2]) return -1;

  return msg_len + 3;
}