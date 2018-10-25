#include "main.h"

#ifndef CONFIG
#define CONFIG

/**
* Configurations that autonomous.cpp and opcontrol use.
**/

/**
* Port Configuration: Ports that all the motors, sensors or else use.
* You can modify it to fit your Robot.
**/
const std::int32_t LEFT_FRONT_WHEEL_MOTOR = 1;
const std::int32_t LEFT_FRONT_WHEEL_MOTOR_REV = 2;
const std::int32_t RIGHT_FRONT_WHEEL_MOTOR = 3;
const std::int32_t RIGHT_FRONT_WHEEL_MOTOR_REV = 4;
const std::int32_t LEFT_BACK_WHEEL_MOTOR = 5;
const std::int32_t LEFT_BACK_WHEEL_MOTOR_REV = 6;
const std::int32_t RIGHT_BACK_WHEEL_MOTOR = 7;
const std::int32_t RIGHT_BACK_WHEEL_MOTOR_REV = 8;
const std::int32_t LEFT_THROW_MOTOR = 9;
const std::int32_t RIGHT_THROW_MOTOR = 10;
const std::int32_t CLAW_MOTOR = 15;
const std::int32_t ARM_MOTOR = 20;

/**
* Motor power Configuration: Power that claws, throws or else uses.
**/
const std::int32_t move_power_set = 63;
const std::int32_t claw_power_set = 100;
const std::int32_t throw_power_set = 100;
const std::int32_t arm_power_set = 200;

/**
* The delay of each control step.
**/
const std::int32_t delay_time = 50;

/**
* Record file Configuration: Path that the record file saves.
**/
const char* const record_path = "/usd/oms_small_auto.txt";

/**
* Whether the code is debugging.
**/
// #define DEBUGGING

/**
* The autonomous part this is to operate.
**/
extern bool isBlue;

/**
* The motors to be used in the opcontrol and autonomous.
**/
extern pros::Motor left_front_wheel_motor;
extern pros::Motor left_front_wheel_motor_rev;
extern pros::Motor right_front_wheel_motor;
extern pros::Motor right_front_wheel_motor_rev;
extern pros::Motor left_back_wheel_motor;
extern pros::Motor left_back_wheel_motor_rev;
extern pros::Motor right_back_wheel_motor;
extern pros::Motor right_back_wheel_motor_rev;
extern pros::Motor left_throw_motor;
extern pros::Motor right_throw_motor;
extern pros::Motor claw_motor;
extern pros::Motor arm_motor;

#endif
