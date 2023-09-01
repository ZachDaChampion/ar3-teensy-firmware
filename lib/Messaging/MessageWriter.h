/**
 * @file MessageWriter.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-08-31
 */

#ifndef AR3_TEENSY_FIRMWARE__MESSEAGEWRITER_H
#define AR3_TEENSY_FIRMWARE__MESSEAGEWRITER_H

#define START_BYTE 0x24

#include <stddef.h>
#include <checksum.hpp>
#include <WriteBufferInterface.h>

template <size_t BUFFER_SIZE>
class MessageWriter : public EmbeddedProto::WriteBufferInterface
{
public:
  /**
   * Construct a new MessageWriter object. This will initialize a buffer of the specified size.
   */
  MessageWriter()
  {
    this->buffer[0] = START_BYTE;
    this->buffer[1] = 0;
    this->buffer[2] = 0;
    this->buffer_len = 3;
  }

  /**
   * Destroy the Message Writer object.
   */
  ~MessageWriter() {}

  /**
   * Get a reference to the full buffer.
   *
   * @return A reference to the full buffer.
   */
  const uint8_t* get_buffer() const { return this->buffer; }

  /**
   * Get the length of all bytes in the buffer, including the header.
   *
   * @return The length of all bytes in the buffer.
   */
  uint32_t get_full_buffer_len() const { return this->buffer_len; }

  /**
   * Get a reference to the message in the buffer, not including the header.
   *
   * @return A reference to the message in the buffer.
   */
  const uint8_t* get_message() const { return &this->buffer[3]; }

  /**
   * Clear the buffer.
   */
  void clear() override
  {
    this->buffer[0] = START_BYTE;
    this->buffer[1] = 0;
    this->buffer[2] = 0;
  }

  /**
   * Get the amount of space remaining in the buffer.
   *
   * @return The amount of space remaining in the buffer.
   */
  uint32_t get_available_size() const override { return BUFFER_SIZE - this->buffer[1]; }

  /**
   * Get the maximum size of the buffer, not including the header.
   *
   * @return The maximum size of the buffer.
   */
  uint32_t get_max_size() const override { return BUFFER_SIZE - 3; }

  /**
   * Get the current size of the buffer.
   *
   * @return The current size of the buffer.
   */
  uint32_t get_size() const override { return this->buffer[1]; }

  /**
   * Push an array of bytes into the buffer.
   *
   * @param[in] bytes Pointer to the array of bytes to push.
   * @param[in] length The length of the array of bytes.
   * @return True if the bytes were successfully pushed, false otherwise.
   */
  bool push(const uint8_t* bytes, const uint32_t length)
  {
    if (length < BUFFER_SIZE - this->buffer_len) return false;
    memcpy(&buffer[this->buffer_len], bytes, length);
    this->buffer[1] += length;
    this->buffer[2] = calc_crc();
    return true;
  }

  /**
   * Push a single byte into the buffer.
   *
   * @param[in] byte The byte to push.
   * @return True if the byte was successfully pushed, false otherwise.
   */
  bool push(const uint8_t byte) override
  {
    if (BUFFER_SIZE - this->buffer_len < 1) return false;
    this->buffer[this->buffer_len] = byte;
    this->buffer[1] += 1;
    this->buffer[2] = calc_crc();
    return true;
  }

private:
  uint8_t calc_crc() const { return crc8ccitt(&buffer[3], buffer[1]); }

  uint8_t buffer[BUFFER_SIZE];
  size_t buffer_len;
};

#endif