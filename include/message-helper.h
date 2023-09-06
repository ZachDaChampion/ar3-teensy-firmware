/**
 * @file message-helper.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-05
 */

#ifndef AR3_TEENSY_FIRMWARE__MESSAGE_HELPER_H
#define AR3_TEENSY_FIRMWARE__MESSAGE_HELPER_H

#include <stdint.h>
#include <main_generated.h>

namespace msg_helper
{

/**
 * Writes a log message to the given destination buffer. This will be a fully framed message, ready
 * to be sent over the serial port. It will return the number of bytes written to the destination,
 * or -1 if the destination buffer was too small.
 *
 * NOTE: This function will clear the FlatBufferBuilder before building the message.
 *
 * @param[out] dest The destination buffer to write to.
 * @param[in] dest_size The size of the destination buffer.
 * @param[in] builder The FlatBufferBuilder to use to build the message.
 * @param[in] level The log level of the message.
 * @param[in] message The message to log.
 * @return The number of bytes written to the destination buffer, or -1 if the destination buffer
 *         was too small.
 */
int write_log(uint8_t* dest, size_t dest_size, flatbuffers::FlatBufferBuilder& builder,
              CobotMsgs::LogLevel level, const char* message);

/**
 * Writes an ack response to the given destination buffer. This will be a fully framed message,
 * ready to be sent over the serial port. It will return the number of bytes written to the
 * destination, or -1 if the destination buffer was too small.
 *
 * NOTE: This function will clear the FlatBufferBuilder before building the message.
 *
 * @param[out] dest The destination buffer to write to.
 * @param[in] dest_size The size of the destination buffer.
 * @param[in] builder The FlatBufferBuilder to use to build the message.
 * @param[in] msg_id The ID of the message that this is a response to.
 * @return The number of bytes written to the destination buffer, or -1 if the destination buffer
 *         was too small.
 */
int write_ack(uint8_t* dest, size_t dest_size, flatbuffers::FlatBufferBuilder& builder,
              uint32_t msg_id);

/**
 * Writes a done response to the given destination buffer. This will be a fully framed message,
 * ready to be sent over the serial port. It will return the number of bytes written to the
 * destination, or -1 if the destination buffer was too small.
 *
 * NOTE: This function will clear the FlatBufferBuilder before building the message.
 *
 * @param[out] dest The destination buffer to write to.
 * @param[in] dest_size The size of the destination buffer.
 * @param[in] builder The FlatBufferBuilder to use to build the message.
 * @param[in] msg_id The ID of the message that this is a response to.
 * @return The number of bytes written to the destination buffer, or -1 if the destination buffer
 *        was too small.
 */
int write_done(uint8_t* dest, size_t dest_size, flatbuffers::FlatBufferBuilder& builder,
               uint32_t msg_id);

/**
 * Writes an error response to the given destination buffer. This will be a fully framed message,
 * ready to be sent over the serial port. It will return the number of bytes written to the
 * destination, or -1 if the destination buffer was too small.
 *
 * NOTE: This function will clear the FlatBufferBuilder before building the message.
 *
 * @param[out] dest The destination buffer to write to.
 * @param[in] dest_size The size of the destination buffer.
 * @param[in] builder The FlatBufferBuilder to use to build the message.
 * @param[in] msg_id The ID of the message that this is a response to.
 * @param[in] error_code The error code to send.
 * @param[in] error_msg The error message to send.
 * @return The number of bytes written to the destination buffer, or -1 if the destination buffer
 *         was too small.
 */
int write_error_response(uint8_t* dest, size_t dest_size, flatbuffers::FlatBufferBuilder& builder,
                         uint32_t msg_id, CobotMsgs::ErrorCode error_code, const char* error_msg);

};  // namespace msg_helper

#endif