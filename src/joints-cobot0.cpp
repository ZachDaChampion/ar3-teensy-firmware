/**
 * @file joints-cobot0.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-10
 *
 * Joint configurations for COBOT 0.
 */

#include <Joint.h>

static const uint8_t CALIBRATION_ORDER[] = {5, 4, 3, 2, 1, 0};

static Joint joints[] = {
  Joint({
    .id = 0,
    .name = "base",

    .min_steps = -7477,
    .max_steps = 4600,
    .ref_steps = -7477,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 40.0,
    .enc_reduction = 40.0,

    .direction = -1,

    .max_speed = 20.0,
    .max_accel = 10.0,
    .calibration_speed = -10.0,

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

    .min_steps = -2397,
    .max_steps = 2120,
    .ref_steps = -2397,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 50.0,
    .enc_reduction = 50.0,

    .direction = -1,

    .max_speed = 20.0,
    .max_accel = 10.0,
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

    .min_steps = -6000,
    .max_steps = 7506,
    .ref_steps = 7506,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 50.0,
    .enc_reduction = 50.0,

    .direction = 1,

    .max_speed = 20.0,
    .max_accel = 10.0,
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

    .min_steps = -6000,
    .max_steps = 7046,
    .ref_steps = 7046,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 39.2,
    .enc_reduction = 39.2,

    .direction = 1,

    .max_speed = 60.0,
    .max_accel = 25.0,
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
    .name = "forearm roll",

    .min_steps = -1958,
    .max_steps = 1958,
    .ref_steps = -1958,

    .motor_steps_per_rev = 800,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 9.1455,
    .enc_reduction = 9.1455,

    .direction = -1,

    .max_speed = 40.0,
    .max_accel = 40.0,
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
    .name = "forearm pitch",

    .min_steps = -3000,
    .max_steps = 3250,
    .ref_steps = 3250,

    .motor_steps_per_rev = 400,
    .enc_ticks_per_rev = 2048,

    .motor_reduction = 19.0,
    .enc_reduction = 19.0,

    .direction = 1,

    .max_speed = 40.0,
    .max_accel = 120.0,
    .calibration_speed = 10.0,

    .step_pin = 10,
    .dir_pin = 11,
    .enc_a_pin = 24,
    .enc_b_pin = 25,

    .speed_filter_strength = 5.0,

    .lim_pin = 31,
  })
};
