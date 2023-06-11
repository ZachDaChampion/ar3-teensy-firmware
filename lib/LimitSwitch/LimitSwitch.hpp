#ifndef AR3_TEENSY_FIRMWARE__LIMIT_SWITCH_HPP
#define AR3_TEENSY_FIRMWARE__LIMIT_SWITCH_HPP

#include <stdint.h>

/**
 * A simple class for reading a debounced limit switch.
 */
class LimitSwitch
{
public:
  /**
   * Construct a new Limit Switch object.
   *
   * \param[in] pin The pin the limit switch is connected to.
   * \param[in] debounce_time The debounce time in milliseconds.
   */
  LimitSwitch(uint8_t pin, uint16_t debounce_time = 50);

  /**
   * Read a debounced value from the limit switch.
   *
   * \return `1` if the limit switch is pressed, `0` otherwise.
   */
  uint8_t read();

private:
  uint8_t pin;
  uint8_t state;
  uint16_t debounce_time;
  uint32_t last_update_time;
};

#endif  // AR3_TEENSY_FIRMWARE__LIMIT_SWITCH_HPP