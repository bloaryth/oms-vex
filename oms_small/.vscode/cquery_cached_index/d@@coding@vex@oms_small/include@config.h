#include "main.h"

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
  const std::int32_t CLAW_MOTOR = 11;

  /**
  * Motor power Configuration: Power that claws, throws or else uses.
  **/
  const std::int32_t claw_power_set = 200;
  // const std::int32_t throw_power_set = 127;
  const std::int32_t throw_power_set = 63;

  /**
  * The delay of each control step.
  **/
  const std::int32_t delay_time = 10;

  // /**
  // * The motors to be used in the opcontrol and autonomous.
  // **/
  // pros::Motor left_front_wheel_motor (LEFT_FRONT_WHEEL_MOTOR);
  // pros::Motor left_front_wheel_motor_rev (LEFT_FRONT_WHEEL_MOTOR_REV, true);
  // pros::Motor right_front_wheel_motor (RIGHT_FRONT_WHEEL_MOTOR, true);
  // pros::Motor right_front_wheel_motor_rev (RIGHT_FRONT_WHEEL_MOTOR_REV);
  // pros::Motor left_back_wheel_motor (LEFT_BACK_WHEEL_MOTOR);
  // pros::Motor left_back_wheel_motor_rev (LEFT_BACK_WHEEL_MOTOR_REV, true);
  // pros::Motor right_back_wheel_motor (RIGHT_BACK_WHEEL_MOTOR, true);
  // pros::Motor right_back_wheel_motor_rev (RIGHT_BACK_WHEEL_MOTOR_REV);
  // pros::Motor left_throw_motor (LEFT_THROW_MOTOR);
  // pros::Motor right_throw_motor (RIGHT_THROW_MOTOR, true);
  // pros::Motor claw_motor (CLAW_MOTOR);
