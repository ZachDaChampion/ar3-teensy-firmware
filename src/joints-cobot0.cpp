/**
 * @file joints-cobot0.cpp
 * @author Zach Champion (zachchampion79@gmail.com)
 *
 * @version 1.0
 * @date 2023-09-10
 *
 * Joint configurations for COBOT 0.
 */

#if COBOT_ID == 0

#include "config.h"

Gripper gripper({
  .pin = 13,
  .min_angle = 0,
  .max_angle = 180,
  .avg_speed = 450,
});

// clang-format off

Joint joints[] = {
  Joint({
    .id = 0,
    .name = "base",

    .min_steps = -7425,
    .max_steps = 6250,
    .ref_steps = -7425,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,

    .motor_reduction = 40.0,

    .direction = -1,

    .max_speed = 80.0,
    .max_accel = 240.0,
    .calibration_speed = -10.0,

    .step_pin = 0,
    .dir_pin = 1,

    .encoder_config = {
      .type = EncoderConfig::NONE,
    },

    .lim_pin = 26,
  }),
  
  Joint({
    .id = 1,
    .name = "shoulder",

    .min_steps = -2350,
    .max_steps = 4000,
    .ref_steps = -2450,
    
    .goto_after_calibrate = -1750,

    .motor_steps_per_rev = 400,

    .motor_reduction = 50.0,

    .direction = 1,

    .max_speed = 60.0,
    .max_accel = 240.0,
    .calibration_speed = -5.0,

    .step_pin = 2,
    .dir_pin = 3,

    .encoder_config = {
      .type = EncoderConfig::NONE,
    },

    .lim_pin = 27,
  }),
  
  Joint({
    .id = 2,
    .name = "elbow",

    .min_steps = -8000,
    .max_steps = 8100,
    .ref_steps = 8100,
    
    .goto_after_calibrate = 3500,

    .motor_steps_per_rev = 400,

    .motor_reduction = 50.0,

    .direction = 1,

    .max_speed = 160.0,
    .max_accel = 220.0,
    .calibration_speed = 5.0,

    .step_pin = 4,
    .dir_pin = 5,

    // .encoder_config = {
    //   .type = EncoderConfig::MAGNETIC,
    //   .magnetic = {
    //     .bus = &Wire,
    //     .direction = -1,
    //     .offset = -165.666,
    //     .dir_pin = 255,
    //   },
    // },

    .encoder_config = {
      .type = EncoderConfig::NONE,
    },

    .lim_pin = 28,
  }),
  
  Joint({
    .id = 3,
    .name = "forearm roll",

    .min_steps = -4250,
    .max_steps = 7046,
    .ref_steps = 7046,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,

    .motor_reduction = 39.2,

    .direction = -1,

    .max_speed = 240.0,
    .max_accel = 1200.0,
    .calibration_speed = 10.0,

    .step_pin = 6,
    .dir_pin = 7,

    .encoder_config = {
      .type = EncoderConfig::NONE,
    },

    .lim_pin = 29,
  }),
  
  Joint({
    .id = 4,
    .name = "wrist pitch",

    .min_steps = -1750,
    .max_steps = 2250,
    .ref_steps = -1750,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 800,

    .motor_reduction = 9.1455,

    .direction = 1,

    .max_speed = 200.0,
    .max_accel = 600.0,
    .calibration_speed = -10.0,

    .step_pin = 8,
    .dir_pin = 9,

    .encoder_config = {
      .type = EncoderConfig::MAGNETIC,
      .magnetic = {
        .bus = &Wire1,
        .direction = -1,
        .offset = -107.666,
        .dir_pin = 255,
      },
    },

    .lim_pin = 30,
  }),
  
  Joint({
    .id = 5,
    .name = "wrist roll",

    .min_steps = -3000,
    .max_steps = 3250,
    .ref_steps = 3250,
    
    .goto_after_calibrate = 0,

    .motor_steps_per_rev = 400,

    .motor_reduction = 19.0,

    .direction = 1,

    .max_speed = 1500.0,
    .max_accel = 8000.0,
    .calibration_speed = 10.0,

    .step_pin = 10,
    .dir_pin = 11,

    .encoder_config = {
      .type = EncoderConfig::NONE,
    },

    .lim_pin = 31,
  })
};

// clang-format on

#endif