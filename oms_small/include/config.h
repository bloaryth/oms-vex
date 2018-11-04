#include "main.h"
#include <string>

#ifndef CONFIG
#define CONFIG

/**
* Configurations that autonomous.cpp and opcontrol use.
**/

/**
* The delay of each control step.
**/
const int delay_time = 50;

/**
* Port Configuration: Ports that all the motors, sensors or else use.
* You can modify it to fit your Robot.
**/
const int LEFT_FRONT_WHEEL_MOTOR = 13;
const int LEFT_FRONT_WHEEL_MOTOR_REV = 14;
const int RIGHT_FRONT_WHEEL_MOTOR = 15;
const int RIGHT_FRONT_WHEEL_MOTOR_REV = 16;
const int LEFT_BACK_WHEEL_MOTOR = 17;
const int LEFT_BACK_WHEEL_MOTOR_REV = 18;
const int RIGHT_BACK_WHEEL_MOTOR = 19;
const int RIGHT_BACK_WHEEL_MOTOR_REV = 20;
const int LEFT_THROW_MOTOR = 10;
const int RIGHT_THROW_MOTOR = 9;
const int CLAW_MOTOR = 7;
const int ARM_MOTOR = 8;

/**
* Motor power Configuration: Power that claws, throws or else uses.
**/
const int move_power_set = 63;
const int claw_power_set = 200;
const int throw_power_set = 100;
const int arm_power_set = 200;
const int arm_up_cooldown_set = 300 / delay_time;

/**
* Record file Configuration: Path that the record file saves.
**/
extern std::string record_path;
extern int record_id;
extern std::string record_full_path;

/**
* Whether the code is debugging.
**/
// #define DEBUGGING

/**
* The autonomous part this is to operate.
**/
extern bool is_blue;

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
