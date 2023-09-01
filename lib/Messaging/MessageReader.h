/**
 * @file MessageReader.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-01
 */

#ifndef AR3_TEENSY_FIRMWARE__MESSAGEREADER_H
#define AR3_TEENSY_FIRMWARE__MESSAGEREADER_H

#define START_BYTE 0x24

#include <stddef.h>
#include <checksum.hpp>
#include <ReadBufferInterface.h>
#include <Arduino.h>

template <size_t BUFFER_SIZE>
class MessageReader : public EmbeddedProto::ReadBufferInterface
{
public:
  /**
   * Construct a new Message Reader object.
   */
  MessageReader() {}

  /**
   * Destroy the Message Reader object.
   */
  ~MessageReader() {}

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
   * Read bytes from the serial port into the buffer. This will read until the buffer is full or
   * there are no more bytes to read.
   */
  void read_from_serial()
  {
    if (!Serial.available()) return;
    while (this->buffer_len < BUFFER_SIZE) {
      int x = Serial.read();
      if (x == -1) break;
      if (message_in_progress || x == START_BYTE) {
        message_in_progress = true;
        this->buffer[this->buffer_len++] = x;
      }
    }
  }

  /**
   * Get a reference to the message in the buffer, not including the header.
   *
   * @return A reference to the message in the buffer, or nullptr if there is no message.
   */
  const uint8_t* get_message() const
  {
    if (this->buffer_len > 3) {
      return &this->buffer[3];
    } else {
      return nullptr;
    }
  }

  /**
   * Check if the message is complete and valid. This will check the start byte, length, and
   * checksum.
   *
   * @return -1 if the message is invalid, 0 if the message is incomplete, or the length of the
   *         message if it is valid.
   */
  int check_message()
  {
    if (this->buffer_len < 4) return 0;  // Check if header is complete and some message exists
    if (this->buffer[0] != START_BYTE) return -1;          // Check start byte
    if (this->buffer[1] + 3u < this->buffer_len) return 0;  // Check if message is complete
    if (this->buffer[2] != calc_crc()) return -1;          // Verify checksum

    return this->buffer[1];
  }

  /**
   * Clear the buffer.
   */
  void clear()
  {
    this->buffer_len = 0;
    this->cursor = 0;
  }

  /**
   * Advance the internal read index by one.
   */
  bool advance() override
  {
    if (this->cursor >= this->buffer_len) return false;
    this->cursor++;
    return true;
  }

  /**
   * Advance the internal read index by n.
   *
   * @param n The number of bytes to advance the read index by.
   */
  bool advance(const uint32_t n) override
  {
    if (this->cursor + n < this->buffer_len) {
      this->cursor += n;
      return true;
    } else {
      this->cursor = this->buffer_len;
      return false;
    }
  }

  /**
   * Get the maximum size of the message, not including the header.
   *
   * @return The maximum size of the message, not including the header.
   */
  uint32_t get_max_size() const override { return BUFFER_SIZE - 3; }

  /**
   * Get the total number of bytes remaining in the message, not including the header.
   *
   * @return The total number of bytes remaining in the message, not including the header.
   */
  uint32_t get_size() const override { return this->buffer_len - 3 - this->cursor; }

  /**
   * Obtain the value of the oldest byte in the buffer. Does not advance the read index.
   *
   * @param[out] value The value of the oldest byte in the buffer.
   * @return false if the buffer is empty, true otherwise.
   */
  bool peek(uint8_t& value) const override
  {
    if (this->cursor < this->buffer_len) {
      value = this->buffer[this->cursor];
      return true;
    } else {
      return false;
    }
  }

  /**
   * Obtain the value of the oldest byte in the buffer. Advances the read index.
   *
   * @param[out] value The value of the oldest byte in the buffer.
   * @return false if the buffer is empty, true otherwise.
   */
  bool pop(uint8_t& value) override
  {
    if (this->cursor < this->buffer_len) {
      value = this->buffer[this->cursor++];
      return true;
    } else {
      return false;
    }
  }

private:
  uint8_t calc_crc() const { return crc8ccitt(&buffer[3], buffer[1]); }

  uint8_t buffer[BUFFER_SIZE];
  uint32_t buffer_len = 0;
  uint32_t cursor = 0;
  bool message_in_progress = false;
};

#endif