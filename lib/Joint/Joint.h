/**
 * @file Joint.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-08-28
 */

#ifndef AR3_TEENSY_FIRMWARE__JOINT_HPP
#define AR3_TEENSY_FIRMWARE__JOINT_HPP

#include <stdint.h>
#include <AccelStepper.h>
#include <LimitSwitch.h>

struct JointConfig {
  uint8_t id;        // ID of the joint (0-5)
  const char* name;  // Name of the joint

  int motor_steps_per_rev;  // Number of steps per revolution of the stepper motor

  float motor_reduction;  // Gear reduction from the motor to the joint

  float max_speed;  // Maximum speed of the joint (in degrees per second)
  float max_accel;  // Maximum acceleration of the joint (in degrees per second per second)

  float calibration_speed;  // Speed of the joint during calibration (in degrees per second). Sign
                            // determines the direction of calibration. `direction` is ignored
                            // during calibration.

  uint8_t step_pin;  // Step pin of the motor controller
  uint8_t dir_pin;   // Direction pin of the motor controller

  uint8_t lim_pin;  // Limit switch pin
};

/**
 * The Joint class handles all interactions with a Joint. It controls the stepper motor and keeps
 * the motor and encoder in sync.
 */
class Joint
{
public:
  /**
   * Construct a new Joint object.
   *
   * @param[in] config The configuration for the joint.
   */
  Joint(JointConfig config);

  /**
   * Initialize the joint. This should be called in `setup()` and must be called before any other
   * methods are called.
   */
  void init();

  /**
   * Get the current position of the joint.
   *
   * @return The current position of the joint (in steps).
   */
  long get_steps();

  /**
   * Begin moving the joint to a position with an automatically calculated speed.
   *
   * @param[in] target The target position of the joint (in steps).
   */
  void move_to_auto(long target);

  /**
   * Begin moving the joint to a position with a specified speed.
   *
   * @param[in] target The target position of the joint (in steps).
   * @param[in] speed The speed of the joint (in steps per second) (positive).
   */
  void move_to_speed(long target, float speed);

  /**
   * Stop the joint.
   *
   * @param[in] smooth Whether or not to decelerate the joint smoothly.
   */
  void stop(bool smooth = true);

  /**
   * Move the joint to the limit switch.
   *
   * @param[in] reverse Whether or not to move in the reverse direction.
   */
  void move_to_limit_switch(bool reverse = false);

  /**
   * Override the current position of the joint. This will mark the joint as calibrated.
   *
   * @param[in] position The new position of the joint (in steps).
   */
  void override_position(long position);

  /**
   * Get the joint config.
   *
   * @return The joint config.
   */
  const JointConfig& get_config() const;

  /**
   * Check if the limit switch is pressed.
   *
   * @return Whether or not the limit switch is pressed.
   */
  bool limit_switch_pressed();

private:
  AccelStepper stepper;
  LimitSwitch<8> limit_switch;
  float motor_deg_per_step;

  JointConfig config;
};

#endif