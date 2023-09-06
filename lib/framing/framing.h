/**
 * @file framing.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-08-28
 */

#ifndef AR3_TEENSY_FIRMWARE__FRAMING_H
#define AR3_TEENSY_FIRMWARE__FRAMING_H

#include <stdint.h>

#define START_BYTE 0x24

namespace framing
{

/**
 * Frame a message to be sent over the serial port. This will add the start byte, length, and
 * checksum.
 *
 * @param[out] dest The destination buffer to write the framed message to.
 * @param[in] dest_len The length of the destination buffer.
 * @param[in] src The source buffer containing the message to frame.
 * @param[in] src_len The length of the source buffer.
 * @return The length of the framed message, or -1 if the message is too long to fit in the buffer.
 */
int frame_message(uint8_t* dest, size_t dest_len, const uint8_t* src, size_t src_len);

/**
 * Check if a framed message is complete and valid. This will check the start byte, length, and
 * checksum.
 *
 * @param[in] buffer The buffer containing the framed message.
 * @param[in] buffer_len The length of the buffer.
 * @return -1 if the message is invalid, 0 if the message is incomplete, or the length of the
 *         message if it is valid.
 */
int check_message(const uint8_t* buffer, size_t buffer_len);

/**
 * Removes the first frame from the buffer. This will shift the buffer to remove the first frame.
 *
 * @param[in] buffer The buffer to remove the frame from.
 * @param[in] buffer_len The length of the buffer.
 * @return The length of the buffer after removing the frame.
 */
int remove_frame(uint8_t* buffer, size_t buffer_len);

/**
 * Attempts to remove bad data from the buffer. This will shift the buffer until a start byte is
 * found that is not in the first position. If no start byte is found, the buffer will be cleared.
 *
 * @param[out] buffer The buffer to remove bad data from.
 * @param[in] buffer_len The length of the buffer.
 * @return The length of the buffer after removing bad data.
 */
int remove_bad_frame(uint8_t* buffer, size_t buffer_len);

}  // namespace framing
#endif