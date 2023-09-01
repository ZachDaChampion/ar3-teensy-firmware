#include "Joint.h"

Joint::Joint(JointConfig config)
  : config(config)
  , stepper(AccelStepper::DRIVER, config.step_pin, config.dir_pin)
  , encoder(config.enc_a_pin, config.enc_b_pin)
  , limit_switch(config.lim_pin, config.lim_debounce_time)
{
  this->state.id = State::IDLE;
  this->is_calibrated = false;
  this->micros_timer = 0;

  this->enc_deg_per_tick = 360.0 / (config.enc_ticks_per_rev * config.enc_reduction);
  this->motor_deg_per_step = 360.0 / (config.motor_steps_per_rev * config.motor_reduction);

  this->stepper.setMaxSpeed(config.max_speed);
  this->stepper.setAcceleration(config.max_accel);
}

void Joint::init() {}

float Joint::get_position()
{
  return encoder.read() * enc_deg_per_tick;
}

float Joint::get_speed()
{
  return measured_speed;
}

void Joint::move_to_auto(float target)
{
  state.id = State::MOVE_TO_AUTO;
  state.data.move_to_auto.target_steps = target / motor_deg_per_step;
  stepper.moveTo(state.data.move_to_auto.target_steps);
}

void Joint::move_to_speed(float target, float speed)
{
  state.id = State::MOVE_TO_SPEED;
  state.data.move_to_speed.target_steps = target / motor_deg_per_step;
  state.data.move_to_speed.speed = speed / motor_deg_per_step;
  stepper.moveTo(state.data.move_to_speed.target_steps);
  stepper.setSpeed(state.data.move_to_speed.speed);
}

void Joint::move_forever_speed(float speed)
{
  state.id = State::MOVE_FOREVER_SPEED;
  state.data.move_forever_speed.speed = speed / motor_deg_per_step;
  stepper.setSpeed(state.data.move_forever_speed.speed);
}

void Joint::stop(bool smooth)
{
  if (smooth && is_calibrated) {
    state.id = State::STOPPING;
    stepper.stop();
  } else {
    state.id = State::IDLE;
    stepper.setSpeed(0);
  }
}

void Joint::calibrate()
{
  state.id = State::CALIBRATING;
  stepper.setSpeed(config.calibration_speed / motor_deg_per_step);
}

void Joint::update()
{
  switch (state.id) {
    case State::IDLE:
      break;

    case State::STOPPING:
      if (stepper.distanceToGo() == 0) {
        state.id = State::IDLE;
        stepper.setSpeed(0);
      }
      stepper.run();
      break;

    case State::CALIBRATING:
      if (limit_switch.read()) {
        stepper.setCurrentPosition(config.ref_steps);
        is_calibrated = true;
        state.id = State::IDLE;
        stepper.setSpeed(0);
      }
      break;

    case State::MOVE_TO_AUTO:
      if (stepper.distanceToGo() == 0) {
        state.id = State::IDLE;
        stepper.setSpeed(0);
      }
      stepper.run();
      break;

    case State::MOVE_TO_SPEED:
      if (stepper.distanceToGo() == 0) {
        state.id = State::IDLE;
        stepper.setSpeed(0);
      }
      stepper.run();
      break;

    case State::MOVE_FOREVER_SPEED:
      stepper.runSpeed();
      break;
  }

  /*
   * Calculate the speed of the joint. This uses a moving mean filter, scaled by the time since the
   * last update. This way, the filter is independent of the update rate.
   */

  int32_t encoder_pos = encoder.read();
  float dt = micros_timer / 1000000.0;
  micros_timer = 0;

  float unfiltered_speed = (encoder_pos - last_encoder_pos) * enc_deg_per_tick / dt;
  float scaled_filter_strength = config.speed_filter_strength * dt;

  if (scaled_filter_strength >= 1) {
    measured_speed = unfiltered_speed;
  } else {
    measured_speed =
      measured_speed * (1 - scaled_filter_strength) + unfiltered_speed * scaled_filter_strength;
  }
  last_encoder_pos = encoder_pos;
}
