/**
 * @file joints-cobot1.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-10
 *
 * Joint configurations for COBOT 1.
 */

#include <Joint.h>

// clang-format off

static const int GRIPPER_SERVO_PIN = 23;

static Joint joints[] = {
  Joint({
    .id = 0,
    .name = "base",

    .motor_steps_per_rev = 400,

    .motor_reduction = 40.0,

    .max_speed = 80.0,
    .max_accel = 240.0,
    .calibration_speed = -10.0,

    .step_pin = 0,
    .dir_pin = 1,

    .lim_pin = 26,
  }),
  
  Joint({
    .id = 1,
    .name = "shoulder",

    .motor_steps_per_rev = 400,

    .motor_reduction = 50.0,

    .max_speed = 60.0,
    .max_accel = 240.0,
    .calibration_speed = 5.0,

    .step_pin = 2,
    .dir_pin = 3,

    .lim_pin = 27,
  }),
  
  Joint({
    .id = 2,
    .name = "elbow",

    .motor_steps_per_rev = 400,

    .motor_reduction = 50.0,

    .max_speed = 160.0,
    .max_accel = 220.0,
    .calibration_speed = -5.0,

    .step_pin = 4,
    .dir_pin = 5,

    .lim_pin = 28,
  }),
  
  Joint({
    .id = 3,
    .name = "forearm roll",

    .motor_steps_per_rev = 400,

    .motor_reduction = 39.2,

    .max_speed = 240.0,
    .max_accel = 1200.0,
    .calibration_speed = -10.0,

    .step_pin = 6,
    .dir_pin = 7,

    .lim_pin = 29,
  }),
  
  Joint({
    .id = 4,
    .name = "wrist pitch",

    .motor_steps_per_rev = 800,

    .motor_reduction = 9.1455,

    .max_speed = 200.0,
    .max_accel = 600.0,
    .calibration_speed = -10.0,

    .step_pin = 8,
    .dir_pin = 9,

    .lim_pin = 30,
  }),
  
  Joint({
    .id = 5,
    .name = "wrist roll",

    .motor_steps_per_rev = 400,

    .motor_reduction = 19.0,

    .max_speed = 1500.0,
    .max_accel = 8000.0,
    .calibration_speed = -10.0,

    .step_pin = 10,
    .dir_pin = 11,

    .lim_pin = 31,
  })
};

// clang-format on