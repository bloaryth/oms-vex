#include "main.h"
// #include "okapi/api.hpp"
//
// #include <stdlib.h>
// #include <time.h>
//
// using namespace okapi;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  const std::int32_t LEFT_FRONT_WHEEL_MOTOR = 1;
  const std::int32_t LEFT_FRONT_WHEEL_MOTOR_REV = 2;
  const std::int32_t RIGHT_FRONT_WHEEL_MOTOR = 3;
  const std::int32_t RIGHT_FRONT_WHEEL_MOTOR_REV = 4;
  const std::int32_t LEFT_BACK_WHEEL_MOTOR = 5;
  const std::int32_t LEFT_BACK_WHEEL_MOTOR_REV = 6;
  const std::int32_t RIGHT_BACK_WHEEL_MOTOR = 7;
  const std::int32_t RIGHT_BACK_WHEEL_MOTOR_REV = 8;

  // auto chassis = okapi::ChassisControllerFactory::create(
  //   {-LEFT_FRONT_WHEEL_MOTOR, LEFT_FRONT_WHEEL_MOTOR_REV, -LEFT_BACK_WHEEL_MOTOR, LEFT_BACK_WHEEL_MOTOR_REV},
  //   {RIGHT_FRONT_WHEEL_MOTOR, -RIGHT_FRONT_WHEEL_MOTOR_REV, RIGHT_BACK_WHEEL_MOTOR, -RIGHT_BACK_WHEEL_MOTOR_REV},
  //   okapi::AbstractMotor::gearset::green);
  //
  // chassis.setMaxVelocity(100);
  //
  // chassis.moveDistance(12.56_in);
  // chassis.turnAngle(2060);

  pros::Motor left_front_wheel_motor (LEFT_FRONT_WHEEL_MOTOR, true);
  pros::Motor left_front_wheel_motor_rev (LEFT_FRONT_WHEEL_MOTOR_REV);
  pros::Motor right_front_wheel_motor (RIGHT_FRONT_WHEEL_MOTOR);
  pros::Motor right_front_wheel_motor_rev (RIGHT_FRONT_WHEEL_MOTOR_REV, true);
  pros::Motor left_back_wheel_motor (LEFT_BACK_WHEEL_MOTOR, true);
  pros::Motor left_back_wheel_motor_rev (LEFT_BACK_WHEEL_MOTOR_REV);
  pros::Motor right_back_wheel_motor (RIGHT_BACK_WHEEL_MOTOR);
  pros::Motor right_back_wheel_motor_rev (RIGHT_BACK_WHEEL_MOTOR_REV, true);

  left_front_wheel_motor.move_relative(1000, 50);
  left_front_wheel_motor_rev.move_relative(1000, 50);
  right_front_wheel_motor.move_relative(1000, 50);
  right_front_wheel_motor_rev.move_relative(1000, 50);
  left_back_wheel_motor.move_relative(1000, 50);
  left_back_wheel_motor_rev.move_relative(1000, 50);
  right_back_wheel_motor.move_relative(1000, 50);
  right_back_wheel_motor_rev.move_relative(1000, 50);

  // pros::delay(1000);

}
