#include "config.h"

void on_center_button() {
	is_blue = !is_blue;
  if (is_blue) {
    pros::lcd::set_text(2, "Blue team now.\n");
  } else {
    pros::lcd::set_text(2, "Red team now.\n");
  }
}

void on_left_button() {
  if (record_id > 1) {
    --record_id;
    record_full_path = record_path + std::to_string(record_id);
    pros::lcd::print(3, "record_id: %d\n", record_id);
  }
}

void on_right_button() {
  ++record_id;
  record_full_path = record_path + std::to_string(record_id);
  pros::lcd::print(3, "record_id: %d\n", record_id);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello OMS-B!");
  if (is_blue) {
    pros::lcd::set_text(2, "Blue team now.\n");
  } else {
    pros::lcd::set_text(2, "Red team now.\n");
  }

  pros::lcd::print(3, "record_id: %d\n", record_id);
	pros::lcd::register_btn1_cb(on_center_button);
  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn2_cb(on_right_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
