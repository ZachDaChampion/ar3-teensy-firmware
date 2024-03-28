/**
 * @file LimitSwitch.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.1
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef AR3_TEENSY_FIRMWARE__LIMIT_SWITCH_HPP
#define AR3_TEENSY_FIRMWARE__LIMIT_SWITCH_HPP

#include <Arduino.h>

/**
 * A simple class for reading a filtered limit switch.
 */
template <size_t FILTER_BUFFER_SIZE>
class LimitSwitch
{
public:
  /**
   * Construct a new Limit Switch object.
   *
   * @param[in] pin The pin_ the limit switch is connected to.
   */
  LimitSwitch(uint8_t pin)
  {
    this->pin_ = pin;
    this->filter_buffer_index_ = 0;
    this->active_count_ = 0;

    for (size_t i = 0; i < FILTER_BUFFER_SIZE; ++i) {
      this->filter_buffer_[i] = 0;
    }
  }
  /**
   * Read a filtered value from the limit switch. This will only return `1` if all of the last
   * `FILTER_BUFFER_SIZE` reads were `1`.
   *
   * @return `1` if the limit switch is pressed, `0` otherwise.
   */
  uint8_t read()
  {
    if (this->filter_buffer_[this->filter_buffer_index_]) --this->active_count_;
    uint8_t val = digitalRead(this->pin_);
    if (val) ++this->active_count_;
    this->filter_buffer_[this->filter_buffer_index_] = val;

    this->filter_buffer_index_ = (this->filter_buffer_index_ + 1) % FILTER_BUFFER_SIZE;
    return this->active_count_ == FILTER_BUFFER_SIZE;
  }

  /**
   * Read the value of the limit switch at regular intervals and return `1` if the limit switch is
   * pressed for the entire duration of the interval. This function will block for the duration of
   * the interval, or until the limit switch is released (whichever comes first).
   *
   * @param[in] interval The interval to read the limit switch at.
   * @param[in] samples The number of samples to take.
   * @return `1` if the limit switch was pressed for the entire duration of the interval, `0`
   * otherwise.
   */
  uint8_t read_interval(uint32_t interval, uint32_t samples)
  {
    for (uint32_t i = 0; i < samples; ++i) {
      if (!this->read()) return 0;
      delay(interval);
    }
    return 1;
  }

private:
  uint8_t pin_;
  uint8_t filter_buffer_[FILTER_BUFFER_SIZE];
  size_t active_count_;
  size_t filter_buffer_index_;
};

#endif  // AR3_TEENSY_FIRMWARE__LIMIT_SWITCH_HPP