#include "config.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <utility>

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

inline std::int32_t analog_to_g18_velocity(std::int32_t analog) {
  return analog / 127.0 * 200;
}

/**
* Slow start but quick end.
**/
inline std::int32_t smooth_power (std::int32_t old_velocity, std::int32_t new_velocity) {
  std::int32_t inc = std::min(abs(old_velocity / 10), 3) + 1;
  if (new_velocity - old_velocity > inc) {
    return old_velocity + inc;
  } else if (new_velocity - old_velocity < - inc) {
    return old_velocity - inc;
  } else {
    return new_velocity;
  }
}

void opcontrol() {
  /**
  * The motors to be used in the opcontrol and autonomous.
  **/
  pros::Motor left_front_wheel_motor (LEFT_FRONT_WHEEL_MOTOR, true);
  pros::Motor left_front_wheel_motor_rev (LEFT_FRONT_WHEEL_MOTOR_REV);
  pros::Motor right_front_wheel_motor (RIGHT_FRONT_WHEEL_MOTOR);
  pros::Motor right_front_wheel_motor_rev (RIGHT_FRONT_WHEEL_MOTOR_REV, true);
  pros::Motor left_back_wheel_motor (LEFT_BACK_WHEEL_MOTOR, true);
  pros::Motor left_back_wheel_motor_rev (LEFT_BACK_WHEEL_MOTOR_REV);
  pros::Motor right_back_wheel_motor (RIGHT_BACK_WHEEL_MOTOR);
  pros::Motor right_back_wheel_motor_rev (RIGHT_BACK_WHEEL_MOTOR_REV, true);
  pros::Motor left_throw_motor (LEFT_THROW_MOTOR);
  pros::Motor right_throw_motor (RIGHT_THROW_MOTOR, true);
  pros::Motor claw_motor (CLAW_MOTOR);

  /**
  * Record file Configuration: Path that the record file saves.
  **/
  const char* record_path = "/usd/oms_small_auto.txt";

	/**
	* Prepare for the autonomous program.
	**/
	using robot_motors_tuple = std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>;
	std::vector<robot_motors_tuple> robot_motors_vector;
  robot_motors_vector.reserve(6000);  // 60 s
	bool isRecording = false;

	/**
	* Runing step of Robot.
	**/
	pros::Controller master (pros::E_CONTROLLER_MASTER);
  std::int32_t old_straight_power = 0;
	while (true) {
		// Start or end recording.
		if (master.get_digital(DIGITAL_X)) {
			isRecording = ! isRecording;
			if (isRecording) {
				pros::lcd::set_text(3, "Record start...\n");
				master.set_text(0, 0, "Record start...\n");
			} else {
        FILE* record = fopen (record_path, "w");
				for (auto& robot_motors : robot_motors_vector) {
          fprintf(record, "%d\t%d\t%d\t%d\n", std::move(std::get<0>(robot_motors)), std::move(std::get<1>(robot_motors)),
                  std::move(std::get<2>(robot_motors)), std::move(std::get<3>(robot_motors)));
				}
        fclose(record);
				break;
			}
			pros::delay(1000);
		}

		// Arcade Control
    std::int32_t straight_power;
    if (master.get_digital(DIGITAL_UP)) {
      straight_power = move_power_set;
    } else if (master.get_digital(DIGITAL_DOWN)) {
      straight_power = - move_power_set;
    } else {
      straight_power = master.get_analog(ANALOG_LEFT_Y);
    }
    straight_power = smooth_power(old_straight_power, straight_power);
    old_straight_power = straight_power;

    std::int32_t turn_power;
    turn_power = master.get_analog(ANALOG_RIGHT_X) / 2;
    // if (master.get_digital(DIGITAL_RIGHT)) {
    //   turn_power = move_power_set;
    // } else if (master.get_digital(DIGITAL_LEFT)) {
    //   turn_power = - move_power_set;
    // } else {
    //   turn_power = master.get_analog(ANALOG_RIGHT_X);
    // }

    std::int32_t left_wheel_power = analog_to_g18_velocity(straight_power - turn_power);
    std::int32_t right_wheel_power = analog_to_g18_velocity(straight_power + turn_power);

		left_front_wheel_motor.move_velocity(left_wheel_power);
		left_front_wheel_motor_rev.move_velocity(left_wheel_power);
		left_back_wheel_motor.move_velocity(left_wheel_power);
		left_back_wheel_motor_rev.move_velocity(left_wheel_power);

		right_front_wheel_motor.move_velocity(right_wheel_power);
		right_front_wheel_motor_rev.move_velocity(right_wheel_power);
		right_back_wheel_motor.move_velocity(right_wheel_power);
		right_back_wheel_motor_rev.move_velocity(right_wheel_power);

		// Claw Control
    std::int32_t claw_power;
		if (master.get_digital(DIGITAL_L1)) {
			claw_power = claw_power_set;
		} else if (master.get_digital(DIGITAL_L2)) {
			claw_power = - claw_power_set;
		} else {
			claw_power = 0;
		}
		claw_motor.move_velocity(claw_power);

		// Throw Control
    std::int32_t throw_power;
		if (master.get_digital(DIGITAL_R1)) {
			throw_power = throw_power_set;
		} else if (master.get_digital(DIGITAL_R2)) {
			throw_power = - throw_power_set;
		} else {
			throw_power = 0;
		}
		left_throw_motor.move_velocity(throw_power);
		right_throw_motor.move_velocity(throw_power);

		// Record
		if (isRecording) {
      printf("%d %d %d %d\n", left_wheel_power, right_wheel_power, claw_power, throw_power);
			robot_motors_vector.emplace_back(std::make_tuple(left_wheel_power, right_wheel_power, claw_power, throw_power));
		}

		// Delay
		pros::delay(delay_time);
	}

	// In case of record stop
	pros::lcd::set_text(3, "Record end...\n");
	master.print(0, 0, "Record end...\n");
	while (true) {
		pros::delay(1000);
	}
}
