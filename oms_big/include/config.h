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
const int LEFT_FRONT_WHEEL_MOTOR = 1;
const int LEFT_MIDDLE_WHEEL_MOTOR = 2;
const int LEFT_BACK_WHEEL_MOTOR = 3;
const int RIGHT_FRONT_WHEEL_MOTOR = 4;
const int RIGHT_MIDDLE_WHEEL_MOTOR = 5;
const int RIGHT_BACK_WHEEL_MOTOR = 6;
const int LEFT_ARM_MOTOR = 7;
const int RIGHT_ARM_MOTOR = 8;
const int EJECT_LEFT_MOTOR = 10;
const int EJECT_RIGHT_MOTOR = 11;
const int CLAW_MOTOR = 12;
const int SCROLL_MOTOR = 13;

/**
* Motor power Configuration: Power that claws, throws or else uses.
**/
const int move_power_set = 50;
const int scroll_power_set = -150;
const int eject_power_set = 75;
const int arm_power_set = 60;
const int claw_power_set = 100;
const int turn_over_cooldown_set = 2150 / delay_time;

/**
* Record file Configuration: Path that the record file saves.
**/
extern std::string record_path;
extern int record_id;
extern std::string record_full_path;

/**
* Whether the code is debugging.
**/
#define DEBUGGING

/**
* The autonomous part this is to operate.
**/
extern bool is_blue;

/**
* The motors to be used in the opcontrol and autonomous.
**/
extern pros::Motor left_front_wheel_motor;
extern pros::Motor left_middle_wheel_motor;
extern pros::Motor left_back_wheel_motor;
extern pros::Motor right_front_wheel_motor;
extern pros::Motor right_middle_wheel_motor;
extern pros::Motor right_back_wheel_motor;
extern pros::Motor left_arm_motor;
extern pros::Motor right_arm_motor;
extern pros::Motor eject_left_motor;
extern pros::Motor eject_right_motor;
extern pros::Motor claw_motor;
extern pros::Motor scroll_motor;

#endif
