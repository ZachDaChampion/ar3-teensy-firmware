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
#include <Encoder.h>
#include <LimitSwitch.h>

struct JointConfig {
  uint8_t id;        // ID of the joint (0-5)
  const char* name;  // Name of the joint

  long min_steps;  // Most negative position of the joint (in steps)
  long max_steps;  // Most positive position of the joint (in steps)
  long ref_steps;  // Position of the joint when it touches the limit switch (in steps)

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

  uint8_t lim_pin;             // Limit switch pin
  uint16_t lim_debounce_time;  // Debounce time for the limit switch
};

/**
 * The Joint class handles all interactions with a Joint. It controls the stepper motor and keeps
 * the motor and encoder in sync.
 */
class Joint
{
public:
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
        long target_steps;  // The target position of the joint (in steps)
      } move_to_auto;

      struct {
        long target_steps;  // The target position of the joint (in steps)
        float speed;        // The speed of the joint (in steps per second)
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
  State get_state();

  /**
   * Get the current position of the joint.
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
  void move_to_auto(float target);

  /**
   * Begin moving the joint to a position with a specified speed.
   *
   * @param[in] target The target position of the joint (in degrees).
   * @param[in] speed The speed of the joint (in degrees per second) (positive).
   */
  void move_to_speed(float target, float speed);

  /**
   * Begin moving the joint indefinitely at a specified speed.
   *
   * @param[in] speed The speed of the joint (in degrees per second).
   */
  void move_forever_speed(float speed);

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
   * Override the current position of the joint. This will mark the joint as calibrated.
   * 
   * @param[in] position The new position of the joint (in degrees).
   */
  void override_position(float position);

  /**
   * Update the joint. This should be called as frequently as possible.
   */
  void update();

private:
  AccelStepper stepper;
  Encoder encoder;
  LimitSwitch limit_switch;

  float enc_deg_per_tick;
  float motor_deg_per_step;

  State state;
  JointConfig config;
  bool is_calibrated;
  float measured_speed;
  int32_t last_encoder_pos;
  elapsedMicros micros_timer;
};

#endif