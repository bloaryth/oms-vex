#include "config.h"
#include <vector>
#include <tuple>
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

inline int analog_to_g18_velocity(int analog) {
  return analog / 127.0 * 200;
}

void opcontrol() {
  /**
	* Prepare for the autonomous program.
	**/
	using robot_motors_tuple = std::tuple<int, int, int, int, int, int>;
	std::vector<robot_motors_tuple> robot_motors_vector;
  robot_motors_vector.reserve(1000 / delay_time * 60);  // 60 s
	bool is_recording = false;

  /**
  * Runing step of Robot.
  **/
  left_arm_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_arm_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  claw_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  int arm_target,claw_target;
  left_arm_motor.set_zero_position(0);
  claw_motor.set_zero_position(0);
  arm_target = left_arm_motor.get_position();
  claw_target=claw_motor.get_position();
  int scroll_direction = 0;
	int change_scroll_cooldown = 0;
  int turn_over_cooldown = 0;
  pros::Controller master (pros::E_CONTROLLER_MASTER);
  pros::lcd::set_text(4, "opcontrol mode.\n");
  while (true) {
    // Start or end recording.
    if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_Y)) {
      is_recording = ! is_recording;
      if (is_recording) {
        pros::lcd::set_text(4, "Record start...\n");
      } else {
        FILE* record = fopen (record_full_path.c_str(), "w");
        for (auto& robot_motors : robot_motors_vector) {
          fprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\n", std::move(std::get<0>(robot_motors)), std::move(std::get<1>(robot_motors)),
                  std::move(std::get<2>(robot_motors)), std::move(std::get<3>(robot_motors)), std::move(std::get<4>(robot_motors)),
                  std::move(std::get<5>(robot_motors)));
        }
        fclose(record);
        robot_motors_vector.clear();
        pros::lcd::set_text(4, "Record end...\n");
      }
      pros::delay(1000);
    }

    // Arcade Control
		int	straight_power;
    if (master.get_digital(DIGITAL_UP)) {
			straight_power = 50;
		} else if (master.get_digital(DIGITAL_DOWN)){
			straight_power = -50;
		} else {
			straight_power = master.get_analog(ANALOG_LEFT_Y);
		}
		straight_power = analog_to_g18_velocity(straight_power);

    int turn_power;
    if (master.get_digital(DIGITAL_LEFT)) {
			turn_power = - move_power_set;
		} else if (master.get_digital(DIGITAL_RIGHT)) {
			turn_power = move_power_set;
		} else {
			turn_power = master.get_analog(ANALOG_RIGHT_X);
		}
		turn_power = analog_to_g18_velocity(turn_power);

    if (is_recording) {
      //straight_power /=2;
      turn_power /= 3;//speed up
    }

    int left_wheel_power = 1.2*straight_power + turn_power;
    int right_wheel_power = 1.2*straight_power - turn_power;

    /*if (master.get_digital(DIGITAL_R1)) {
      left_wheel_power /= 3;
      right_wheel_power /= 3;
    }*/

    left_front_wheel_motor.move_velocity(left_wheel_power);
    left_middle_wheel_motor.move_velocity(left_wheel_power);
    left_back_wheel_motor.move_velocity(left_wheel_power);
    right_front_wheel_motor.move_velocity(right_wheel_power);
    right_middle_wheel_motor.move_velocity(right_wheel_power);
    right_back_wheel_motor.move_velocity(right_wheel_power);

    // Scroll Control
		int scroll_power;
    if (!change_scroll_cooldown) {
      if (master.get_digital(DIGITAL_B)) {
        // (-1 -> 1) (0 ->1) (1 -> 0)
        scroll_direction = !((scroll_direction + 1) / 2);
      } else if (master.get_digital(DIGITAL_Y)) {
        // (-1 -> 0) (0 -> -1) (1 -> -1)
        scroll_direction = -!((scroll_direction - 1) / 2);
      }
      change_scroll_cooldown = 150 / delay_time;
    } else if (change_scroll_cooldown > 0) {
			--change_scroll_cooldown;
		}
		scroll_power = scroll_power_set * scroll_direction;
		scroll_motor.move_velocity(scroll_power);

    // Eject Control
		int eject_power;
    if (master.get_digital(DIGITAL_A)) {
      eject_power = eject_power_set;
    } else {
      eject_power = 0;
    }
		eject_left_motor.move_velocity(eject_power);
		eject_right_motor.move_velocity(eject_power);

    // Arm Control
		arm_target = left_arm_motor.get_position();
		int arm_power;
    if (master.get_digital(DIGITAL_L2)) {
			arm_power = arm_power_set;
    } else if (master.get_digital(DIGITAL_L1)) {
			arm_power = - arm_power_set;
		} else {
      arm_power = 0;
    }
		left_arm_motor.move_velocity(arm_power);
		right_arm_motor.move_velocity(arm_power);

    // Claw Control
		int claw_power = 0;
    /*if (master.get_digital(DIGITAL_LEFT) && turn_over_cooldown == 0) {
        turn_over_cooldown = turn_over_cooldown_set;
    }
    if (turn_over_cooldown > 0) {
      // turn over the plate with button LEFT
      if (turn_over_cooldown > 1450 / delay_time) {
        claw_power = claw_power_set;
      } else if (turn_over_cooldown > 700 / delay_time) {
        claw_power = 0;
      } else {
        claw_power = - claw_power_set;
      }
      --turn_over_cooldown;
    } else {*/
      if (master.get_digital(DIGITAL_R1)) {
        claw_power =100;
      } else if (master.get_digital(DIGITAL_R2)) {
        claw_power = - 160;
      } else {
      //  if((abs(claw_motor.get_position()-claw_target)<150.0))claw_motor=1;
        //一直加小电流的话，机械爪的电机会过热保护
       claw_power = 0;
      }
      //}
		claw_motor.move_velocity(claw_power);

    // Record
    if (is_recording) {
      printf("%d %d %d %d %d %d\n", straight_power, turn_power, scroll_power, eject_power, arm_power, claw_power);
      robot_motors_vector.emplace_back(std::make_tuple(straight_power, turn_power, scroll_power, eject_power, arm_power, claw_power));
    }

    pros::lcd::print(5,"claw temp: %d",claw_motor.get_temperature());
    pros::delay(delay_time);
  }
}
