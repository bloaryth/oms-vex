#include "config.h"

/**
* The autonomous part this is to operate.
**/
bool is_blue = true;

/**
* The motors to be used in the opcontrol and autonomous.
**/
pros::Motor left_front_wheel_motor (LEFT_FRONT_WHEEL_MOTOR);
pros::Motor left_middle_wheel_motor (LEFT_MIDDLE_WHEEL_MOTOR);
pros::Motor left_back_wheel_motor (LEFT_BACK_WHEEL_MOTOR);
pros::Motor right_front_wheel_motor (RIGHT_FRONT_WHEEL_MOTOR, true);
pros::Motor right_middle_wheel_motor (RIGHT_MIDDLE_WHEEL_MOTOR, true);
pros::Motor right_back_wheel_motor (RIGHT_BACK_WHEEL_MOTOR, true);
pros::Motor left_arm_motor (LEFT_ARM_MOTOR);
pros::Motor right_arm_motor (RIGHT_ARM_MOTOR, true);
pros::Motor eject_left_motor (EJECT_LEFT_MOTOR);
pros::Motor eject_right_motor (EJECT_RIGHT_MOTOR, true);
pros::Motor claw_motor (CLAW_MOTOR);
pros::Motor scroll_motor (SCROLL_MOTOR);
