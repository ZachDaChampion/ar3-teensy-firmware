#include "Joint.h"

void Joint::init(JointConfig config)
{
  this->state.id = State::StateID::IDLE;
  this->is_calibrated = false;
  this->last_update_time = 0;
  this->config = config;

  this->enc_deg_per_tick = 360.0 / (config.enc_ticks_per_rev * config.enc_reduction);
  this->motor_deg_per_step = 360.0 / (config.motor_steps_per_rev * config.motor_reduction);

  this->stepper = AccelStepper(AccelStepper::DRIVER, config.step_pin, config.dir_pin);
  this->stepper.setMaxSpeed(config.max_speed);
  this->stepper.setAcceleration(config.max_accel);
  this->encoder = Encoder(config.enc_a_pin, config.enc_b_pin);
  this->limit_switch = LimitSwitch(config.lim_pin, config.lim_debounce_time);
}

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
  if (!is_calibrated) throw "Joint not calibrated";  // TODO: better error handling
  state.id = State::StateID::MOVE_TO_AUTO;
  state.data.move_to_auto.target_steps = target / motor_deg_per_step;
  stepper.moveTo(state.data.move_to_auto.target_steps);
}

void Joint::move_to_speed(float target, float speed)
{
  if (!is_calibrated) throw "Joint not calibrated";  // TODO: better error handling
  state.id = State::StateID::MOVE_TO_SPEED;
  state.data.move_to_speed.target_steps = target / motor_deg_per_step;
  state.data.move_to_speed.speed = speed / motor_deg_per_step;
  stepper.moveTo(state.data.move_to_speed.target_steps);
  stepper.setSpeed(state.data.move_to_speed.speed);
}

void Joint::move_forever_speed(float speed)
{
  if (!is_calibrated) throw "Joint not calibrated";  // TODO: better error handling
  state.id = State::StateID::MOVE_FOREVER_SPEED;
  state.data.move_forever_speed.speed = speed / motor_deg_per_step;
  stepper.setSpeed(state.data.move_forever_speed.speed);
}

void Joint::stop(bool smooth)
{
  if (smooth && is_calibrated) {
    state.id = State::StateID::STOPPING;
    stepper.stop();
  } else {
    state.id = State::StateID::IDLE;
    stepper.setSpeed(0);
  }
}

void Joint::calibrate()
{
  state.id = State::StateID::CALIBRATING;
  stepper.setSpeed(config.calibration_speed / motor_deg_per_step);
}

void Joint::update()
{
  switch (state.id) {
    case State::StateID::IDLE:
      break;

    case State::StateID::STOPPING:
      if (stepper.distanceToGo() == 0) {
        state.id = State::StateID::IDLE;
        stepper.setSpeed(0);
      }
      stepper.run();
      break;

    case State::StateID::CALIBRATING:
      if (limit_switch.read()) {
        stepper.setCurrentPosition(config.ref_steps);
        is_calibrated = true;
        state.id = State::StateID::IDLE;
        stepper.setSpeed(0);
      }
      stepper.runSpeed();
      break;

    case State::StateID::MOVE_TO_AUTO:
      if (stepper.distanceToGo() == 0) {
        state.id = State::StateID::IDLE;
        stepper.setSpeed(0);
      }
      stepper.run();
      break;

    case State::StateID::MOVE_TO_SPEED:
      if (stepper.distanceToGo() == 0) {
        state.id = State::StateID::IDLE;
        stepper.setSpeed(0);
      }
      stepper.run();
      break;
  }
}
