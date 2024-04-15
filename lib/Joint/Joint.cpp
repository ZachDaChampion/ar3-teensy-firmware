#include "Joint.h"

Joint::Joint(JointConfig config)
  : config(config)
  , stepper(AccelStepper::DRIVER, config.step_pin, config.dir_pin)
  , limit_switch(config.lim_pin)
  , encoder(false)
{
  this->state.id = State::IDLE;
  this->is_calibrated = false;
  this->encoder_feedback_enabled = false;
  this->micros_timer = 0;
  this->print_timer = 0;

  this->motor_deg_per_step = 360.0 / ((float)config.motor_steps_per_rev * config.motor_reduction);

  // Setup the encoder depending on which type the joint uses.
  switch (config.encoder_config.type) {
    case EncoderConfig::OPTICAL: {
      const auto optical_config = config.encoder_config.optical;
      this->enc_deg_per_tick =
        360.0 / ((float)optical_config.ticks_per_rev * optical_config.reduction);
      this->enc_ticks_per_step =
        (float)optical_config.ticks_per_rev / (float)config.motor_steps_per_rev;
      this->encoder = Encoder(optical_config.pin_a, optical_config.pin_b);
    } break;

    case EncoderConfig::MAGNETIC: {
      const auto magnetic_config = config.encoder_config.magnetic;
      this->encoder_feedback_enabled = true;
      this->enc_deg_per_tick = 360.0 / 4096.0;
      this->enc_ticks_per_step = 4096.f / (float)config.motor_steps_per_rev;
      this->encoder = AS5600(magnetic_config.bus);
    } break;

    default:
      break;
  }

  this->stepper.setMinPulseWidth(5);  // VERY IMPORTANT, THIS TOOK HOURS TO FIGURE OUT
  this->stepper.setMaxSpeed(config.max_speed / motor_deg_per_step);
  this->stepper.setAcceleration(config.max_accel / motor_deg_per_step);
}

void Joint::init()
{
  pinMode(config.lim_pin, INPUT_PULLDOWN);

  switch (config.encoder_config.type) {
    case EncoderConfig::MAGNETIC: {
      const auto magnetic_config = config.encoder_config.magnetic;
      magnetic_config.bus->begin();
      std::get<AS5600>(encoder).setOffset(magnetic_config.offset);
      std::get<AS5600>(encoder).begin(magnetic_config.dir_pin);
      is_calibrated = true;
    } break;

    default:
      break;
  }
}

Joint::State* Joint::get_state()
{
  return &state;
}

float Joint::get_position()
{
  return stepper.currentPosition() * config.direction * motor_deg_per_step;
}

float Joint::get_speed()
{
  return stepper.speed() * motor_deg_per_step;
}

void Joint::move_to_auto(int32_t target)
{
  float target_f = target * 0.001f;
  state.id = State::MOVE_TO_AUTO;
  state.data.move_to_auto.target_steps = config.direction * target_f / motor_deg_per_step;

  // Limit the target position to the range of the joint.
  if (state.data.move_to_auto.target_steps < config.min_steps)
    state.data.move_to_auto.target_steps = config.min_steps;
  if (state.data.move_to_auto.target_steps > config.max_steps)
    state.data.move_to_auto.target_steps = config.max_steps;

  stepper.moveTo(state.data.move_to_auto.target_steps);
}

void Joint::move_to_speed(int32_t target, int32_t speed)
{
  float target_f = target * 0.001f;
  float speed_f = speed * 0.001f;
  state.id = State::MOVE_TO_SPEED;
  state.data.move_to_speed.target_steps = config.direction * target_f / motor_deg_per_step;
  state.data.move_to_speed.speed = speed_f / motor_deg_per_step;

  // Limit the target position to the range of the joint.
  if (state.data.move_to_speed.target_steps < config.min_steps)
    state.data.move_to_speed.target_steps = config.min_steps;
  if (state.data.move_to_speed.target_steps > config.max_steps)
    state.data.move_to_speed.target_steps = config.max_steps;

  // Limit the speed to between 0 and the maximum speed of the joint.
  if (state.data.move_to_speed.speed < 0) state.data.move_to_speed.speed = 0;
  if (state.data.move_to_speed.speed > config.max_speed / motor_deg_per_step)
    state.data.move_to_speed.speed = config.max_speed / motor_deg_per_step;

  stepper.moveTo(state.data.move_to_speed.target_steps);
  stepper.setSpeed(state.data.move_to_speed.speed);
}

void Joint::move_forever_speed(int32_t speed)
{
  float speed_f = speed * 0.001f;
  state.id = State::MOVE_FOREVER_SPEED;
  state.data.move_forever_speed.speed = config.direction * speed_f / motor_deg_per_step;

  // Limit the speed to between -max_speed and max_speed.
  if (state.data.move_forever_speed.speed < -config.max_speed)
    state.data.move_forever_speed.speed = -config.max_speed / motor_deg_per_step;
  if (state.data.move_forever_speed.speed > config.max_speed)
    state.data.move_forever_speed.speed = config.max_speed / motor_deg_per_step;

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
  if (config.encoder_config.type == EncoderConfig::MAGNETIC) return;
  state.id = State::CALIBRATING;
  state.data.calibrate.has_hit_limit_switch = false;
  stepper.setSpeed(config.calibration_speed / motor_deg_per_step);
}

bool Joint::get_is_calibrated()
{
  return is_calibrated;
}

void Joint::override_position(int32_t position)
{
  float position_f = position * 0.001f;
  state.id = State::IDLE;
  is_calibrated = true;
  stepper.setCurrentPosition(position_f / motor_deg_per_step);

  switch (config.encoder_config.type) {
    case EncoderConfig::OPTICAL: {
      std::get<Encoder>(encoder).write(position_f / enc_deg_per_tick);
    } break;
    case EncoderConfig::MAGNETIC: {
      std::get<AS5600>(encoder).setOffset(position_f);
    } break;
    default:
      break;
  }
}

bool Joint::position_within_range(int32_t position)
{
  float position_f = position * 0.001f;
  return (position_f >= config.min_steps * motor_deg_per_step) &&
         (position_f <= config.max_steps * motor_deg_per_step);
}

bool Joint::speed_within_range(int32_t speed)
{
  float speed_f = speed * 0.001f;
  return (speed_f >= -config.max_speed) && (speed_f <= config.max_speed);
}

String Joint::position_range_str() const
{
  return "[" + String(config.min_steps * motor_deg_per_step) + ", " +
         String(config.max_steps * motor_deg_per_step) + "]";
}

String Joint::speed_range_str() const
{
  return "[" + String(-config.max_speed) + ", " + String(config.max_speed) + "]";
}

void Joint::reset()
{
  state.id = State::IDLE;
  is_calibrated = false;
  encoder_feedback_enabled = false;
  stepper.setSpeed(0);
  stepper.runSpeed();
  stepper.setCurrentPosition(0);
  last_encoder_pos = 0;
  micros_timer = 0;

  switch (config.encoder_config.type) {
    case EncoderConfig::OPTICAL: {
      std::get<Encoder>(encoder).write(0);
    } break;
    case EncoderConfig::MAGNETIC: {
      std::get<AS5600>(encoder).setOffset(config.encoder_config.magnetic.offset);
      encoder_feedback_enabled = true;
    } break;
    default:
      break;
  }
}

void Joint::update()
{
  switch (state.id) {
    case State::IDLE:
      break;

    case State::STOPPING:
      if (stepper.speed() == 0) {
        state.id = State::IDLE;
        break;
      }
      stepper.run();
      break;

    case State::CALIBRATING: {
      if (state.data.calibrate.has_hit_limit_switch) {
        if (!stepper.isRunning()) {
          state.id = State::IDLE;
          is_calibrated = true;
          break;
        }
        stepper.run();
      } else {
        if (limit_switch.read() && limit_switch.read_interval(1, 100)) {
          stepper.setCurrentPosition(config.ref_steps);
          if (config.encoder_config.type == EncoderConfig::OPTICAL)
            std::get<Encoder>(encoder).write(config.ref_steps * enc_ticks_per_step);
          stepper.moveTo(config.goto_after_calibrate);
          state.data.calibrate.has_hit_limit_switch = true;
        }
        stepper.runSpeed();
      }

    } break;

    case State::MOVE_TO_AUTO:
      if (!stepper.isRunning()) {
        state.id = State::IDLE;
        break;
      }
      stepper.run();
      break;

    case State::MOVE_TO_SPEED:
      if (stepper.distanceToGo() == 0) {
        state.id = State::IDLE;
        stepper.setSpeed(0);
      }
      stepper.runSpeedToPosition();
      break;

    case State::MOVE_FOREVER_SPEED:
      if (stepper.currentPosition() <= config.min_steps ||
          stepper.currentPosition() >= config.max_steps) {
        state.id = State::IDLE;
        stepper.setSpeed(0);
      }
      stepper.runSpeed();
      break;
  }
}

void Joint::update_measured_position()
{
  if (!encoder_feedback_enabled) return;

  float measured_deg;
  switch (config.encoder_config.type) {
    case EncoderConfig::OPTICAL:
      measured_deg = std::get<Encoder>(encoder).read() * config.direction * enc_deg_per_tick;
    case EncoderConfig::MAGNETIC: {
      measured_deg = std::get<AS5600>(encoder).rawAngle() * enc_deg_per_tick *
                     config.encoder_config.magnetic.direction;
      while (measured_deg > 180.f) measured_deg -= 360.f;
      while (measured_deg < -180.f) measured_deg += 360.f;
    };
    default:
      return;
  }

  stepper.setCurrentPosition(measured_deg * config.direction / motor_deg_per_step);
}

void Joint::set_feedback_enabled(bool enabled)
{
  encoder_feedback_enabled = enabled;
}
