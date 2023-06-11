#include <AccelStepper.h>
#include <Arduino.h>
#include <Encoder.h>

#include <LimitSwitch.hpp>
#include <ar3_error.h>

#define JOINT_COUNT (sizeof(joints) / sizeof(JointConfig))

/**
 * Configuration for a joint. This includes stepper, encoder, and limit switch information.
 */
struct JointConfig {
  int min_steps;               // Most negative position of the joint (in steps)
  int max_steps;               // Most positive position of the joint (in steps)
  int ref_steps;               // Position of the joint when it touches the limit switch (in steps)
  int steps_per_rev;           // Number of steps per revolution of the stepper motor

  float max_speed;             // Maximum speed of the joint (in steps per second)
  float max_accel;             // Maximum acceleration of the joint (in steps per second per second)

  uint8_t step_pin;            // Step pin of the motor controller
  uint8_t dir_pin;             // Direction pin of the motor controller

  uint8_t enc_a_pin;           // Encoder A pin
  uint8_t enc_b_pin;           // Encoder B pin

  uint8_t lim_pin;             // Limit switch pin
  uint16_t lim_debounce_time;  // Debounce time for the limit switch

  uint8_t reversed;            // Whether the joint is reversed
};

// ============================ ROBOT CONFIGURATION ============================

static const char* FIRMWARE_VERSION = "1.0.0";

static const JointConfig joints[] = {

  {
      // Joint 0
      .min_steps = 0,
      .max_steps = 0,
      .ref_steps = 0,
      .steps_per_rev = 0,
      .step_pin = 0,
      .dir_pin = 0,
      .enc_a_pin = 0,
      .enc_b_pin = 0,
      .lim_pin = 0,
      .reversed = 0,
  },
};

// ========================== END ROBOT CONFIGURATION ==========================

static AccelStepper* steppers[JOINT_COUNT];
static Encoder* encoders[JOINT_COUNT];
static LimitSwitch* limit_switches[JOINT_COUNT];

// Serial buffer used for receiving commands
static char ibuf[256];
static uint8_t ibuf_idx = 0;

// Serial buffer used for sending responses
static char obuf[256];
static uint8_t obuf_idx = 0;

void setup()
{
  // Initialize steppers, encoders, and limit switches
  for (uint8_t i = 0; i < JOINT_COUNT; ++i) {
    steppers[i] = new AccelStepper(AccelStepper::DRIVER, joints[i].step_pin, joints[i].dir_pin);
    steppers[i]->setMaxSpeed(joints[i].max_speed);
    steppers[i]->setAcceleration(joints[i].max_accel);
    encoders[i] = new Encoder(joints[i].enc_a_pin, joints[i].enc_b_pin);
    limit_switches[i] = new LimitSwitch(joints[i].lim_pin);
  }
}

void loop() {}
