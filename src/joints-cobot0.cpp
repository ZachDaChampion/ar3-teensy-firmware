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

static Joint joints[] = { Joint({
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
}) };
