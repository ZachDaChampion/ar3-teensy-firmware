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

/**
 * Create an empty message frame. This will add placeholder values for the length and CRC,
 * which must be filled in later.
 *
 * @param[out] dest The destination buffer to write the framed message to.
 * @param[in] dest_len The length of the destination buffer.
 * @return Number of bytes written to the buffer, or -1 if the buffer is too small.
 */
int framed_template(uint8_t* dest, uint8_t dest_len);

/**
 * Fill in the length and CRC of a framed message. The message must already have been written into
 * the frame.
 *
 * @param[out] dest The destination buffer to write the framed message to.
 * @param[in] dest_len The length of the destination buffer.
 * @param[in] msg_len The length of the message.
 * @return The length of the framed message, or -1 if the message is too long to fit in the buffer.
 */
int framed_finalize(uint8_t* dest, uint8_t dest_len, uint8_t msg_len);

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
int frame_message(uint8_t* dest, uint8_t dest_len, const uint8_t* src, uint8_t src_len);

/**
 * Check if a framed message is complete and valid. This will check the start byte, length, and
 * checksum.
 *
 * @param[in] buffer The buffer containing the framed message.
 * @param[in] buffer_len The length of the buffer.
 * @return -1 if the message is invalid, 0 if the message is incomplete, or the length of the
 *         message if it is valid.
 */
int check_message(const uint8_t* buffer, uint8_t buffer_len);
#endif