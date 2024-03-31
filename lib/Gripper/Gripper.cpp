#include "Gripper.h"

using namespace std;

Gripper::Gripper(GripperConfig config)
  : config(config), last_pos_(config.min_angle), set_pos_(config.min_angle), move_speed_(0)
{
  this->pos_interpolation_timer = 0;
}

void Gripper::init()
{
  servo_.attach(config.pin);
  servo_.write(set_pos_);
}

int Gripper::get_position_estimate()
{
  const int error = set_pos_ - last_pos_;
  if (error == 0) return set_pos_;

  const float travelled = move_speed_ * pos_interpolation_timer * 0.001;
  const int travelled_int = static_cast<int>(travelled);
  if (abs(travelled_int) >= abs(error)) {
    last_pos_ = set_pos_;
    move_speed_ = 0;
    return set_pos_;
  }

  return last_pos_ + travelled_int;
}

void Gripper::move_to(int dest)
{
  if (dest < config.min_angle) dest = config.min_angle;
  if (dest > config.max_angle) dest = config.max_angle;

  last_pos_ = get_position_estimate();
  set_pos_ = dest;
  move_speed_ = (dest > last_pos_) ? config.avg_speed : -config.avg_speed;
  pos_interpolation_timer = 0;
  servo_.write(dest);
}

bool Gripper::position_within_range(int angle) const
{
  return angle >= config.min_angle - 1 && angle <= config.max_angle + 1;
}

String Gripper::position_range_str() const
{
  return "[" + String(config.min_angle) + ", " + String(config.max_angle) + "]";
}
