/**
 * @file joints-cobot1.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-10
 *
 * Joint configurations for COBOT 0.
 */

#include <Joint.h>

// clang-format off

static const int GRIPPER_SERVO_PIN = 13;

static Joint joints[] = {
  Joint({
    .id = 0,
    .name = "base",

    .min_steps = -74770,
    .max_steps = 46000,
    .ref_steps = 0,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 40.0,
    .enc_reduction = 40.0,

    .direction = -1,

    .max_speed = 80.0,
    .max_accel = 240.0,
    .calibration_speed = 10.0,

    .step_pin = 0,
    .dir_pin = 1,
    .enc_a_pin = 14,
    .enc_b_pin = 15,

    .speed_filter_strength = 5.0,

    .lim_pin = 26,
  }),
  
  Joint({
    .id = 1,
    .name = "shoulder",

    .min_steps = -24500,
    .max_steps = 32000,
    .ref_steps = 0,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 50.0,
    .enc_reduction = 50.0,

    .direction = 1,

    .max_speed = 60.0,
    .max_accel = 240.0,
    .calibration_speed = -5.0,

    .step_pin = 2,
    .dir_pin = 3,
    .enc_a_pin = 16,
    .enc_b_pin = 17,

    .speed_filter_strength = 5.0,

    .lim_pin = 27,
  }),
  
  Joint({
    .id = 2,
    .name = "elbow",

    .min_steps = -70000,
    .max_steps = 80560,
    .ref_steps = 0,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 50.0,
    .enc_reduction = 50.0,

    .direction = 1,

    .max_speed = 160.0,
    .max_accel = 220.0,
    .calibration_speed = 5.0,

    .step_pin = 4,
    .dir_pin = 5,
    .enc_a_pin = 18,
    .enc_b_pin = 19,

    .speed_filter_strength = 5.0,

    .lim_pin = 28,
  }),
  
  Joint({
    .id = 3,
    .name = "forearm roll",

    .min_steps = -60000,
    .max_steps = 70460,
    .ref_steps = 0,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 39.2,
    .enc_reduction = 39.2,

    .direction = -1,

    .max_speed = 240.0,
    .max_accel = 1200.0,
    .calibration_speed = 10.0,

    .step_pin = 6,
    .dir_pin = 7,
    .enc_a_pin = 20,
    .enc_b_pin = 21,

    .speed_filter_strength = 5.0,

    .lim_pin = 29,
  }),
  
  Joint({
    .id = 4,
    .name = "wrist pitch",

    .min_steps = -20000,
    .max_steps = 20000,
    .ref_steps = 0,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 800,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 9.1455,
    .enc_reduction = 9.1455,

    .direction = 1,

    .max_speed = 200.0,
    .max_accel = 600.0,
    .calibration_speed = -10.0,

    .step_pin = 8,
    .dir_pin = 9,
    .enc_a_pin = 22,
    .enc_b_pin = 23,

    .speed_filter_strength = 5.0,

    .lim_pin = 30,
  }),
  
  Joint({
    .id = 5,
    .name = "wrist roll",

    .min_steps = -30000,
    .max_steps = 32500,
    .ref_steps = 0,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 19.0,
    .enc_reduction = 19.0,

    .direction = 1,

    .max_speed = 1500.0,
    .max_accel = 8000.0,
    .calibration_speed = 10.0,

    .step_pin = 10,
    .dir_pin = 11,
    .enc_a_pin = 24,
    .enc_b_pin = 25,

    .speed_filter_strength = 5.0,

    .lim_pin = 31,
  })
};

// clang-format on