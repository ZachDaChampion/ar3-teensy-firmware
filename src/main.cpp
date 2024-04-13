#include <Arduino.h>
#include <AccelStepper.h>
#include <LimitSwitch.h>
#include <AS5600.h>

#include <functional>
#include <array>

#if COBOT_ID == 0
#include "joints-cobot0.cpp"
#endif

#if COBOT_ID == 1
#include "joints-cobot1.cpp"
#endif

using namespace std;

int selected_joint = -1;

AS5600 encoders[2];

//                                                                                                //
// ===================================== Command functions ====================================== //
//                                                                                                //

void print_status()
{
  if (selected_joint == -1) {
    Serial.println("No joint selected");
    return;
  }

  auto& joint = joints[selected_joint];
  auto& config = joint.get_config();

  uint16_t enc_vals[2];
  for (size_t i = 0; i < 2; ++i) enc_vals[i] = encoders[i].rawAngle();

  Serial.printf("Encoders:\n");
  Serial.printf("  Wire:  %d (%f)\n", enc_vals[0], enc_vals[0] * AS5600_RAW_TO_DEGREES);
  Serial.printf("  Wire1: %d (%f)\n", enc_vals[1], enc_vals[1] * AS5600_RAW_TO_DEGREES);
  Serial.printf("Selected joint: %d (%s)\n", selected_joint, config.name);
  Serial.printf("  Steps: %ld\n", joint.get_steps());
  Serial.printf("  Limit switch: %s\n", joint.limit_switch_pressed() ? "pressed" : "not pressed");
  Serial.printf("  Config:\n");
  Serial.printf("    Step pin: %d\n", config.step_pin);
  Serial.printf("    Dir pin:  %d\n", config.dir_pin);
  Serial.printf("    Lim pin:  %d\n", config.lim_pin);
  Serial.printf("    Steps per revolution: %d\n", config.motor_steps_per_rev);
  Serial.printf("    Motor reduction: %f\n", config.motor_reduction);
  Serial.printf("    Max speed: %f deg/sec\n", config.max_speed);
  Serial.printf("    Max acceleration: %f deg/sec^2\n", config.max_accel);
}

struct Command {
  const char* name;
  const char abbreviation;
  const char* description;
  std::function<void(const char*)> function;
};

Command commands[] = {
  Command{
    .name = "joint",
    .abbreviation = 'j',
    .description = "Select a joint",
    .function =
      [](const char* arg) {
        int joint = atoi(arg);
        if (joint < 0 || joint > 5) {
          Serial.println("Invalid joint ID");
          return;
        }
        selected_joint = joint;
        print_status();
      },
  },
  Command{
    .name = "status",
    .abbreviation = 's',
    .description = "Print the status of the selected joint",
    .function = [](const char* arg) { print_status(); },
  },
  Command{
    .name = "move_to",
    .abbreviation = 'm',
    .description = "Move the selected joint to a position",
    .function =
      [](const char* arg) {
        if (selected_joint == -1) {
          Serial.println("No joint selected");
          return;
        }
        long target = atol(arg);
        joints[selected_joint].move_to_auto(target);
      },
  },
  Command{
    .name = "move_to_speed",
    .abbreviation = 'v',
    .description = "Move the selected joint to a position at a specified speed",
    .function =
      [](const char* arg) {
        if (selected_joint == -1) {
          Serial.println("No joint selected");
          return;
        }
        char* arg1 = strtok(NULL, " ");
        char* arg2 = strtok(NULL, " ");
        long target = atol(arg1);
        float speed = atof(arg2);
        joints[selected_joint].move_to_speed(target, speed);
      },
  },
  Command{
    .name = "limit_switch",
    .abbreviation = 'l',
    .description = "Move the selected joint to the limit switch",
    .function =
      [](const char* arg) {
        if (selected_joint == -1) {
          Serial.println("No joint selected");
          return;
        }
        joints[selected_joint].move_to_limit_switch(arg && arg[0] == 'r');
      },
  },
  Command{
    .name = "override",
    .abbreviation = 'o',
    .description = "Override the current position of the joint",
    .function =
      [](const char* arg) {
        if (selected_joint == -1) {
          Serial.println("No joint selected");
          return;
        }
        long position = atol(arg);
        joints[selected_joint].override_position(position);
      },
  },
};

//                                                                                                //
// ================================= Arduino control functions ================================== //
//                                                                                                //

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(UINT32_MAX);

  for (auto& joint : joints) {
    joint.init();
  }

  encoders[0] = AS5600(&Wire);
  encoders[1] = AS5600(&Wire1);
  encoders[0].begin();
  encoders[1].begin();
}

void loop()
{
  Serial.print("\n: ");
  String input = Serial.readStringUntil('\n');

  if (input.length() == 0) return;

  if (input == "help" || input == "h") {
    Serial.println("Commands:");
    for (const auto& command : commands) {
      Serial.printf("  %c: %s - %s\n", command.abbreviation, command.name, command.description);
    }
    return;
  }

  char* command = strtok((char*)input.c_str(), " ");
  for (const auto& cmd : commands) {
    if (strcmp(command, cmd.name) == 0 || command[0] == cmd.abbreviation) {
      char* arg = strtok(NULL, " ");
      cmd.function(arg);
      return;
    }
  }
}
