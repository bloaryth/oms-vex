#include "config.h"

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
  int arm_target = 0;
	bool isScroll = false;
	int change_scroll_cooldown = 0;
  pros::Controller master (pros::E_CONTROLLER_MASTER);
  while (true) {
		std::int32_t	straight_power;
		if (master.get_digital(DIGITAL_UP)) {
			straight_power = move_power_set;
		} else if (master.get_digital(DIGITAL_DOWN)){
			straight_power = - move_power_set;
		} else {
			straight_power = master.get_analog(ANALOG_LEFT_Y);
		}
		straight_power = analog_to_g18_velocity(straight_power);

    std::int32_t turn_power;
		if (master.get_digital(DIGITAL_LEFT)) {
			turn_power = - move_power_set;
		} else if (master.get_digital(DIGITAL_RIGHT)) {
			turn_power = move_power_set;
		} else {
			turn_power = master.get_analog(ANALOG_RIGHT_X);
		}
		turn_power = analog_to_g18_velocity(turn_power);

    std::int32_t left_wheel_power = straight_power + turn_power;
    std::int32_t right_wheel_power = straight_power - turn_power;

    left_front_wheel_motor.move_velocity(left_wheel_power);
    left_middle_wheel_motor.move_velocity(left_wheel_power);
    left_back_wheel_motor.move_velocity(left_wheel_power);
    right_front_wheel_motor.move_velocity(right_wheel_power);
    right_middle_wheel_motor.move_velocity(right_wheel_power);
    right_back_wheel_motor.move_velocity(right_wheel_power);

    // scroll
		std::int32_t scroll_power;
		if (!change_scroll_cooldown && master.get_digital(DIGITAL_B)) {
			isScroll = !isScroll;
			change_scroll_cooldown = 1000 / delay_time;
		} else if (change_scroll_cooldown > 0) {
			--change_scroll_cooldown;
		}
		if (isScroll) {
			scroll_power = scroll_power_set;
		} else {
			scroll_motor = 0;
		}
		scroll_motor.move_velocity(scroll_power);

    // eject
		std::int32_t eject_power;
    if (master.get_digital(DIGITAL_A)) {
      eject_power = eject_power_set;
    } else {
      eject_power = 0;
    }
		eject_left_motor.move_velocity(eject_power);
		eject_right_motor.move_velocity(eject_power);

    // arm up and down
		arm_target = left_arm_motor.get_position();
		std::int32_t arm_power;
    if (master.get_digital(DIGITAL_L2)) {
			arm_power = arm_power_set;
    } else if (master.get_digital(DIGITAL_L1)) {
			arm_power = - arm_power_set;
    } else {
			arm_power = 0;
		}
		left_arm_motor.move_velocity(arm_power);
		right_arm_motor.move_velocity(arm_power);

    // claw up and down
		std::int32_t claw_power;
    if (master.get_digital(DIGITAL_R1)) {
      claw_power = claw_power_set;
    } else if (master.get_digital(DIGITAL_R2)) {
      claw_power = - claw_power_set;
    } else {
      claw_power = 0;
    }
		claw_motor.move_velocity(claw_power);

    // turn over the plate with button Y
    // if (master.get_digital(DIGITAL_Y)) {
    //   claw_motor.move_velocity(90);
    //   pros::delay(700);
    //   claw_motor.move_velocity(0);
    //   pros::delay(750);
    //   claw_motor.move_velocity(-90);
    //   pros::delay(700);
    // }

    pros::delay(delay_time);
  }
}
