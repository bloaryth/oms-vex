#include "main.h"
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
void opcontrol() {
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
	 const std::int32_t claw_power_set = 100;
	 const std::int32_t throw_power_set = 100;

	 /**
	 * Record file Configuration: Path that the record file saves.
	 **/
	 const std::string record_path = "TO BE FILLED";

	/**
	* The motors to be used in the opcontrol.
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

	/**
	* Prepare for the autonomous program.
	**/
	using robot_motors_tuple = std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>;
	std::vector<robot_motors_tuple> robot_motors_vector;
	bool isRecording = false;

	/**
	* Runing step of Robot.
	**/
	pros::Controller master (pros::E_CONTROLLER_MASTER);
	while (true) {
		// Start or end recording.
		if (master.get_digital(DIGITAL_A)) {
			isRecording = ! isRecording;
			pros::delay(1000);
			if (master.get_digital(DIGITAL_B)) {
				std::fstream record_fstream (record_path, std::ios_base::out);
				for (auto& robot_motors : robot_motors_vector) {
					record_fstream << std::move(std::get<0>(robot_motors)) << '\t';
					record_fstream << std::move(std::get<1>(robot_motors)) << '\t';
					record_fstream << std::move(std::get<2>(robot_motors)) << '\t';
					record_fstream << std::move(std::get<3>(robot_motors)) << '\n';
				}
				record_fstream.close();
				break;
			}
		}

		// Arcade Control
		std::int32_t straight_power = master.get_analog(ANALOG_LEFT_Y);
		std::int32_t turn_power = master.get_analog(ANALOG_RIGHT_X);

		std::int32_t left_wheel_power = straight_power + turn_power;
		std::int32_t right_wheel_power = straight_power - turn_power;

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
			robot_motors_vector.emplace_back(std::make_tuple(left_wheel_power, right_wheel_power, claw_power, throw_power));
		}

		pros::delay(10);
	}

	// In case of record stop
	while (true) {
		pros::delay(1000);
	}
}
