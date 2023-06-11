/**
 * \file LimitSwitch.cpp
 * \author Zach Champion (zachchampion79@gmail.com)
 *
 * \version 1.1
 * \date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "LimitSwitch.hpp"

#include <Arduino.h>

LimitSwitch::LimitSwitch(uint8_t pin, uint16_t debounce_time)
{
  this->pin_ = pin;
  this->debounce_time_ = debounce_time;
  this->state_ = 0;
  this->last_update_time_ = -1;
}

uint8_t LimitSwitch::read()
{
  uint32_t now = millis();
  if (now - this->last_update_time_ > this->debounce_time_) {
    uint8_t new_state = digitalRead(this->pin_);
    if (new_state != this->state_) {
      this->state_ = new_state;
      this->last_update_time_ = now;
    }
  }
  return this->state_;
}