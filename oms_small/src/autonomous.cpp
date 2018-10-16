#include "config.h"
#include <fstream>
#include <string>

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
  /**
  * The motors to be used in the opcontrol and autonomous.
  **/
  pros::Motor left_front_wheel_motor (LEFT_FRONT_WHEEL_MOTOR);
  pros::Motor left_front_wheel_motor_rev (LEFT_FRONT_WHEEL_MOTOR_REV, true);
  pros::Motor right_front_wheel_motor (RIGHT_FRONT_WHEEL_MOTOR, true);
  pros::Motor right_front_wheel_motor_rev (RIGHT_FRONT_WHEEL_MOTOR_REV);
  pros::Motor left_back_wheel_motor (LEFT_BACK_WHEEL_MOTOR);
  pros::Motor left_back_wheel_motor_rev (LEFT_BACK_WHEEL_MOTOR_REV, true);
  pros::Motor right_back_wheel_motor (RIGHT_BACK_WHEEL_MOTOR, true);
  pros::Motor right_back_wheel_motor_rev (RIGHT_BACK_WHEEL_MOTOR_REV);
  pros::Motor left_throw_motor (LEFT_THROW_MOTOR);
  pros::Motor right_throw_motor (RIGHT_THROW_MOTOR, true);
  pros::Motor claw_motor (CLAW_MOTOR);

  std::fstream record_stream (record_path, std::ios_base::in);

  while (true) {
    // Arcade control
    std::int32_t left_wheel_power, right_wheel_power;
    record_stream >> left_wheel_power >> right_wheel_power;

    left_front_wheel_motor.move(left_wheel_power);
    left_front_wheel_motor_rev.move(left_wheel_power);
    left_back_wheel_motor.move(left_wheel_power);
    left_back_wheel_motor_rev.move(left_wheel_power);

  	right_front_wheel_motor.move(right_wheel_power);
  	right_front_wheel_motor_rev.move(right_wheel_power);
  	right_back_wheel_motor.move(right_wheel_power);
  	right_back_wheel_motor_rev.move(right_wheel_power);

    // Claw Control
    std::int32_t claw_power;
    record_stream >> claw_power;
    claw_motor.move_velocity(claw_power);

    // Throw Control
    std::int32_t throw_power;
    record_stream >> throw_power;
    left_throw_motor.move(throw_power);
    right_throw_motor.move(throw_power);

    // Delay
    pros::delay(delay_time);
  }

}
