#ifndef AR3_TEENSY_FIRMWARE__CONFIG_HPP
#define AR3_TEjsonNSY_FIRMWARE__CONFIG_HPP

#include <Gripper.h>
#include <Joint.h>

const size_t JOINT_COUNT = 6;

extern Gripper gripper;
extern Joint joints[JOINT_COUNT];

#endif