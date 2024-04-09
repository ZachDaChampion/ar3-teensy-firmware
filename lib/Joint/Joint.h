/**
 * @file Joint.h
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-08-28
 */

#ifndef AR3_TEENSY_FIRMWARE__JOINT_HPP
#define AR3_TEENSY_FIRMWARE__JOINT_HPP

#include <AccelStepper.h>
#include <Encoder.h>
#include <LimitSwitch.h>
#include <stdint.h>

struct JointConfig {
  uint8_t id;        // ID of the joint (0-5)
  const char* name;  // Name of the joint

  int32_t min_steps;  // Most negative position of the joint (in steps)
  int32_t max_steps;  // Most positive position of the joint (in steps)
  int32_t ref_steps;  // Position of the joint when it touches the limit switch (in steps)

  int32_t goto_after_calibrate;  // Position of the joint to go to after calibration (in steps).
                                 // This is included in the joint's calibration procedure.

  int motor_steps_per_rev;  // Number of steps per revolution of the stepper motor
  int enc_ticks_per_rev;    // Number of ticks per revolution of the encoder

  float motor_reduction;  // Gear reduction from the motor to the joint
  float enc_reduction;    // Gear reduction from the encoder to the joint

  int8_t direction;  // 1 if the joint is not reversed, -1 if it is reversed

  float max_speed;  // Maximum speed of the joint (in degrees per second)
  float max_accel;  // Maximum acceleration of the joint (in degrees per second per second)

  float calibration_speed;  // Speed of the joint during calibration (in degrees per second). Sign
                            // determines the direction of calibration. `direction` is ignored
                            // during calibration.

  uint8_t step_pin;  // Step pin of the motor controller
  uint8_t dir_pin;   // Direction pin of the motor controller

  uint8_t enc_a_pin;  // Encoder A pin
  uint8_t enc_b_pin;  // Encoder B pin

  float speed_filter_strength;  // Strength of the speed filter (percent of new speed per second)

  uint8_t lim_pin;  // Limit switch pin
};

/**
 * The Joint class handles all interactions with a Joint. It controls the stepper motor and keeps
 * the motor and encoder in sync.
 */
class Joint
{
public:
  JointConfig config;

  /**
   * A state that the joint can be in.
   */
  struct State {
    // The ID of the state.
    enum {
      IDLE,           // The joint is not moving
      STOPPING,       // The joint is stopping
      CALIBRATING,    // The joint is calibrating
      MOVE_TO_AUTO,   // The joint is moving to a position with an automatically calculated speed
      MOVE_TO_SPEED,  // The joint is moving to a position with a specified speed
      MOVE_FOREVER_SPEED,  // The joint is moving indefinitely at a specified speed
    } id;

    // Data dependent on the state.
    union {
      struct {
        bool has_hit_limit_switch;  // Whether or not the joint has hit the limit switch
      } calibrate;

      struct {
        int32_t target_steps;  // The target position of the joint (in steps)
      } move_to_auto;

      struct {
        int32_t target_steps;  // The target position of the joint (in steps)
        float speed;           // The speed of the joint (in steps per second)
      } move_to_speed;

      struct {
        float speed;  // The speed of the joint (in steps per second)
      } move_forever_speed;
    } data;
  };

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
   * Get the current state of the joint.
   *
   * @return The current state of the joint.
   */
  State* get_state();

  /**
   * Get the current position of the joint. This will use the encoder if feedback is enabled,
   * otherwise it will use the stepper motor.
   *
   * @return The current position of the joint (in degrees).
   */
  float get_position();

  /**
   * Get the current speed of the joint.
   *
   * @return The current speed of the joint (in degrees per second).
   */
  float get_speed();

  /**
   * Begin moving the joint to a position with an automatically calculated speed.
   *
   * @param[in] target The target position of the joint (in degrees).
   */
  void move_to_auto(int32_t target);

  /**
   * Begin moving the joint to a position with a specified speed.
   *
   * @param[in] target The target position of the joint (in degrees * 10^3).
   * @param[in] speed The speed of the joint (in degrees * 10^3 per second) (positive).
   */
  void move_to_speed(int32_t target, int32_t speed);

  /**
   * Begin moving the joint indefinitely at a specified speed.
   *
   * @param[in] speed The speed of the joint (in degrees * 10^3 per second).
   */
  void move_forever_speed(int32_t speed);

  /**
   * Stop the joint.
   *
   * @param[in] smooth Whether or not to decelerate the joint smoothly.
   */
  void stop(bool smooth = true);

  /**
   * Calibrate the joint.
   */
  void calibrate();

  /**
   * Get whether or not the joint is calibrated.
   *
   * @return Whether or not the joint is calibrated.
   */
  bool get_is_calibrated();

  /**
   * Override the current position of the joint. This will mark the joint as calibrated.
   *
   * @param[in] position The new position of the joint (in degrees * 10^3).
   */
  void override_position(int32_t position);

  /**
   * Determine whether or not a position is within the range of the joint.
   *
   * @param[in] position The position to check (in degrees * 10^3).
   * @return Whether or not the position is within the range of the joint.
   */
  bool position_within_range(int32_t position);

  /**
   * Determine whether or not a speed is within the range of the joint.
   *
   * @param[in] speed The speed to check (in degrees * 10^3 per second).
   * @return Whether or not the speed is within the range of the joint.
   */
  bool speed_within_range(int32_t speed);

  /**
   * Get a string representation of this joint's position range.
   *
   * @return A string representation of this joint's position range.
   */
  String position_range_str() const;

  /**
   * Get a string representation of this joint's speed range.
   *
   * @return A string representation of this joint's speed range.
   */
  String speed_range_str() const;

  /**
   * Reset the joint. This will stop the joint immediateyl and mark it as uncalibrated.
   */
  void reset();

  /**
   * Update the joint. This should be called as frequently as possible.
   */
  void update();

  /**
   * Uses the encoder value to remove any error in the stepper position.
   */
  void fix_stepper_position();

  /**
   * Enable or disable encoder feedback.
   *
   * @param[in] enabled Whether or not to enable encoder feedback.
   */
  void set_feedback_enabled(bool enabled);

private:
  AccelStepper stepper;
  Encoder encoder;
  LimitSwitch<8> limit_switch;

  float enc_deg_per_tick;
  float motor_deg_per_step;
  float enc_ticks_per_step;

  State state;
  bool is_calibrated;
  bool encoder_feedback_enabled;
  float measured_speed;
  int32_t last_encoder_pos;
  elapsedMicros micros_timer;
  elapsedMillis print_timer;
};

#endif