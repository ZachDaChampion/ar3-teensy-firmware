/**
 * @file framing.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-08-28
 */

#include "framing.h"
#include <checksum.hpp>
#include <cstring>

namespace framing
{

int frame_message(uint8_t* dest, size_t dest_len, const uint8_t* src, uint8_t src_len)
{
  if (dest_len < src_len + 3) return -1;
  dest[0] = START_BYTE;
  dest[1] = src_len;
  dest[2] = crc8ccitt(src, src_len);
  memcpy(dest + 3, src, src_len);
  return src_len + 3;
}

int check_message(const uint8_t* buffer, size_t buffer_len)
{
  if (buffer_len < 3) return 0;
  if (buffer[0] != START_BYTE) return -1;

  uint8_t msg_len = buffer[1];
  if (buffer_len < msg_len + 3u) return 0;

  uint8_t crc = crc8ccitt(buffer + 3, msg_len);
  if (crc != buffer[2]) return -1;

  return msg_len + 3;
}

int remove_frame(uint8_t* buffer, size_t buffer_len)
{
  if (buffer_len < 3) return 0;
  uint8_t msg_len = buffer[1];
  if (buffer_len < msg_len + 3) return 0;
  memmove(buffer, buffer + msg_len + 3, buffer_len - msg_len - 3);
  return buffer_len - msg_len - 3;
}

int remove_bad_frame(uint8_t* buffer, size_t buffer_len)
{
  for (size_t i = 1; i < buffer_len; ++i) {
    if (buffer[i] == START_BYTE) {
      memmove(buffer, buffer + i, buffer_len - i);
      return buffer_len - i;
    }
  }

  return 0;
}

}  // namespace framing