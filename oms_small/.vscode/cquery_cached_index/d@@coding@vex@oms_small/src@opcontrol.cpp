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

void opcontrol() {
	/**
	* Prepare for the autonomous program.
	**/
	using robot_motors_tuple = std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t, std::int32_t>;
	std::vector<robot_motors_tuple> robot_motors_vector;
  robot_motors_vector.reserve(1000 / delay_time * 60);  // 60 s
	bool isRecording = false;

	/**
	* Runing step of Robot.
	**/
	pros::Controller master (pros::E_CONTROLLER_MASTER);
  bool is_forward = true;
  std::int32_t change_direction_cooldown = 0;
	while (true) {
		// Start or end recording.
		if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_Y)) {
			isRecording = ! isRecording;
			if (isRecording) {
				pros::lcd::set_text(3, "Record start...\n");
			} else {
        FILE* record = fopen (record_path, "w");
				for (auto& robot_motors : robot_motors_vector) {
          fprintf(record, "%d\t%d\t%d\t%d\t%d\n", std::move(std::get<0>(robot_motors)), std::move(std::get<1>(robot_motors)),
                  std::move(std::get<2>(robot_motors)), std::move(std::get<3>(robot_motors)), std::move(std::get<4>(robot_motors)));
				}
        fclose(record);
        robot_motors_vector.clear();
        pros::lcd::set_text(3, "Record end...\n");
			}
			pros::delay(1000);
		}

    // change direction with 1s delay_time cool down.
    if (!change_direction_cooldown && master.get_digital(DIGITAL_Y)) {
      is_forward = !is_forward;
      change_direction_cooldown = 1000 / delay_time;
    } else if (change_direction_cooldown > 0) {
      --change_direction_cooldown;
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
    if (!is_forward) {
      straight_power = - straight_power;
    }
    straight_power = analog_to_g18_velocity(straight_power);

    std::int32_t turn_power;
    if (master.get_digital(DIGITAL_LEFT)) {
      turn_power = move_power_set;
    } else if (master.get_digital(DIGITAL_RIGHT)) {
      turn_power = - move_power_set;
    } else {
      turn_power = master.get_analog(ANALOG_RIGHT_X);
    }
    turn_power = analog_to_g18_velocity(turn_power);

    if (isRecording) {
      straight_power /= 2;
      turn_power /= 4;
    }

    std::int32_t left_wheel_power = straight_power - turn_power;
    std::int32_t right_wheel_power = straight_power + turn_power;

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

    // Arm Control
    std::int32_t arm_power;
    if (master.get_digital(DIGITAL_A)) {
      arm_power = arm_power_set;
    } else if (master.get_digital(DIGITAL_B)) {
      arm_power = - arm_power_set;
    } else {
      arm_power = 0;
    }
    arm_motor.move_velocity(arm_power);

		// Record
		if (isRecording) {
      #ifdef DEBUGGING
      printf("%d %d %d %d %d\n", straight_power, turn_power, claw_power, throw_power, arm_power);
      #endif
			robot_motors_vector.emplace_back(std::make_tuple(straight_power, turn_power, claw_power, throw_power, arm_power));
		}

		// Delay
		pros::delay(delay_time);
	}

}
