/**
 * @file Gripper.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2024-03-30
 */

#ifndef AR3_TEENSY_FIRMWARE__GRIPPER_HPP
#define AR3_TEENSY_FIRMWARE__GRIPPER_HPP

#include <PWMServo.h>
#include <elapsedMillis.h>

struct GripperConfig {
  int pin;           // The pin that the gripper's servo is attached to
  int min_angle;     // The minimum angle (degrees) that the servo is allowed to go to.
  int max_angle;     // The maximum angle (degrees) that the server is allowed to go to.
  double avg_speed;  // The average speed of the gripper servo (deg/sec).
};

class Gripper
{
public:
  GripperConfig config;

  /**
   * Construct a new Gripper object.
   *
   * @param[in] config The configuration for the gripper.
   */
  Gripper(GripperConfig config);

  /**
   * Initialize the gripper.This should be called in `setup()` and must be called before any other
   * methods are called.
   */
  void init();

  /**
   * Calculate the estimated position of the gripper based on its last command and average speed.
   *
   * @return The estimated position of the gripper.
   */
  int get_position_estimate();

  /**
   * Begin moving the gripper to the desired angle.
   *
   * @param[in] dest The desired angle to move to (degrees).
   */
  void move_to(int dest);

  /**
   * Return whether or not the given angle is within the gripper's range.
   * 
   * @param[in] angle The angle to check.
   * @return True if within range, false otherwise.
   */
  bool position_within_range(int angle) const;

private:
  PWMServo servo_;

  int last_pos_;
  int set_pos_;
  float move_speed_;
  elapsedMillis pos_interpolation_timer;
};

#endif