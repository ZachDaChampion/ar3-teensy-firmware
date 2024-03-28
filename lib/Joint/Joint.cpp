#include "Joint.h"
#include <Arduino.h>

Joint::Joint(JointConfig config)
  : config(config)
  , stepper(AccelStepper::DRIVER, config.step_pin, config.dir_pin)
  , limit_switch(config.lim_pin)
{
  this->motor_deg_per_step = 360.0 / ((float)config.motor_steps_per_rev * config.motor_reduction);

  this->stepper.setMinPulseWidth(5);  // VERY IMPORTANT, THIS TOOK HOURS TO FIGURE OUT
  this->stepper.setMaxSpeed(config.max_speed / motor_deg_per_step);
  this->stepper.setAcceleration(config.max_accel / motor_deg_per_step);
}

void Joint::init()
{
  pinMode(config.lim_pin, INPUT_PULLDOWN);
}

long Joint::get_steps()
{
  return stepper.currentPosition();
}

void Joint::move_to_auto(long target)
{
  stepper.moveTo(target);
  stepper.runToPosition();
}

void Joint::move_to_speed(long target, float speed)
{
  stepper.moveTo(target);
  stepper.setSpeed(speed);
  stepper.runSpeedToPosition();
}

void Joint::stop(bool smooth)
{
  if (smooth) {
    stepper.stop();
    stepper.runToPosition();
  } else {
    stepper.setSpeed(0);
    stepper.runSpeed();
  }
}

void Joint::move_to_limit_switch(bool reverse)
{
  int dir = reverse ? -1 : 1;
  stepper.setSpeed(dir * config.calibration_speed / motor_deg_per_step);
  while (1) {
    if (limit_switch.read() && limit_switch.read_interval(1, 100)) break;
    stepper.runSpeed();
  }
  this->stop(false);
}

void Joint::override_position(long position)
{
  stepper.setCurrentPosition(position);
}

const JointConfig& Joint::get_config() const
{
  return config;
}

bool Joint::limit_switch_pressed()
{
  // Flush the filter buffer
  for (int i = 0; i < 8; ++i) {
    limit_switch.read();
    delay(1);
  }

  return limit_switch.read() == 1;
}