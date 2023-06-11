/**
 * \file LimitSwitch.cpp
 * \author Zach Champion (zachchampion79@gmail.com)
 *
 * \version 1.0
 * \date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "LimitSwitch.hpp"

#include <Arduino.h>

LimitSwitch::LimitSwitch(uint8_t pin, uint16_t debounce_time)
{
  this->pin = pin;
  this->debounce_time = debounce_time;
  this->state = 0;
  this->last_update_time = -1;
}

uint8_t LimitSwitch::read()
{
  uint32_t now = millis();
  if (now - this->last_update_time > this->debounce_time) {
    this->state = digitalRead(this->pin);
    this->last_update_time = now;
  }
  return this->state;
}