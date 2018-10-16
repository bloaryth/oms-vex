#include "main.h"
#include <fstream>

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I'm squeesed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello OMS!");

	pros::lcd::register_btn1_cb(on_center_button);

	// std::fstream record ("/usd/example .txt", std::ios_base::out);

	// FILE* usd_file_write = fopen("/usd/example.txt", "w");
	// fputs("Example text", usd_file_write);
	// fclose(usd_file_write);
	//
	// FILE* usd_file_read = fopen("/usd/example.txt", "r");
	// char buf[50]; // This just needs to be larger than the contents of the file
	// for (int i = 0; i < 50; ++i) {
	// 	buf[i] = '\0';
	// }
	// fread(buf, 1, 50, usd_file_read); // passing 1 because a `char` is 1 byte, and 50 b/c it's the length of buf
	// // printf("%s\n", buf); // print the string read from the file
	// pros::lcd::set_text(4, buf);
	// // Should print "Example text" to the terminal
	// fclose(usd_file_read); // always close files when you're done with them


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
