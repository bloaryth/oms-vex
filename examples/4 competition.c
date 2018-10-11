#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    DJ_4,           sensorAnalog)
#pragma config(Sensor, in5,    DJ_5,           sensorAnalog)
#pragma config(Sensor, in6,    DJ_6,           sensorAnalog)
#pragma config(Sensor, dgtl1,  hand,           sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  arm,            sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  mr_left,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  mr_right,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  tou9,           sensorTouch)
#pragma config(Sensor, dgtl10, tou10,          sensorTouch)
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop) //wheel
#pragma config(Motor,  port2,           motor2,        tmotorVex393_MC29, openLoop) //wheel
#pragma config(Motor,  port3,           motor3,        tmotorVex393_MC29, openLoop) //wheel
#pragma config(Motor,  port4,           motor4,        tmotorVex393_MC29, openLoop) //up down
#pragma config(Motor,  port5,           motor5,        tmotorVex393_MC29, openLoop) //pick
#pragma config(Motor,  port6,           motor6,        tmotorVex393_MC29, openLoop) //up down
#pragma config(Motor,  port7,           motor7,        tmotorVex393_MC29, openLoop) //pick
#pragma config(Motor,  port8,           motor8,        tmotorVex393_MC29, openLoop) //wheel
#pragma config(Motor,  port9,           motor9,        tmotorVex393_MC29, openLoop) //wheel
#pragma config(Motor,  port10,          motor10,       tmotorVex393_HBridge, openLoop) //wheel

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#include "JoystickDriver.c"

int threshold = 45;
char a, b;
int mode;
int arma;
float rt = 0.0;
int joy_turn = 0;
int joy_forward = 0;
int after = 0;
int before = 0;
int signal1 = 0;
int signal2 = 0;
int signal3 = 0;
int signal4 = 0;
int signal5 = 0;
int signal6 = 0;
int signal7 = 0;
int up_and_down_speed = 90;
bool hasValueChange = true;

void move(int joy_forward, int joy_turn, int sturn1, int sturn2)
{
	a = 1.4; b = 1.4;
	if (abs(joy_forward) < threshold) joy_forward = 0;
	if (abs(joy_turn) < threshold) joy_turn = 0;

	if (sturn1 == 0 && sturn2 == 0)
	{
		motor[motor1] = joy_turn / a + joy_forward / b;
		motor[motor2] = joy_turn / a + joy_forward / b;
		motor[motor3] = joy_turn / a + joy_forward / b;
		motor[motor8] = joy_turn / a - joy_forward / b;
		motor[motor9] = joy_turn / a - joy_forward / b;
		motor[motor10] = joy_turn / a - joy_forward / b;
	}
	else {
		if (joy_turn == 0 && sturn1 == 0 && sturn2 == 1)
		{
			motor[motor1] = 50;
			motor[motor2] = 50;
			motor[motor3] = 50;
			motor[motor8] = 50;
			motor[motor9] = 50;
			motor[motor10] = 50;
		}
		if (joy_turn == 0 && sturn1 == 1 && sturn2 == 0)
		{
			motor[motor1] = -50;
			motor[motor2] = -50;
			motor[motor3] = -50;
			motor[motor8] = -50;
			motor[motor9] = -50;
			motor[motor10] = -50;
		}
	}
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}



void reading()
{
	rt = 0.60*vexRT[Ch1];
	joy_turn = (int)rt;
	joy_forward = vexRT[Ch3];
	signal1 = vexRT[Btn5U];
	signal2 = vexRT[Btn5D];
	signal3 = vexRT[Btn6U];
	signal4 = vexRT[Btn6D];
	signal5 = vexRT[Btn8L];
	signal6 = vexRT[Btn8R];
	signal7 = vexRT[Btn7U];
}

task getValueChange()
{
	int delt = 0;
	int count = 0;
	while (count < 8)
	{
		SensorValue(hand) = 0;
		wait1Msec(10);
		delt = abs(SensorValue(hand));
		writeDebugStreamLine("%d", delt);
		if (delt < 3)
		{
			count++;
		}
	}
	writeDebugStreamLine("keep=false");
	hasValueChange = false;
}

void zpick(int signal3, int signal4) //Pick with low current and protection
{
	if (signal3 == 1 && signal4 == 0 && hasValueChange)
	{
		startTask(getValueChange);
		motor[motor5] = -100;//pick
		motor[motor7] = -100;
		after = 1;
		before = 0;
	}
	else if (signal3 == 1 && signal4 == 0 && hasValueChange == false)
	{
		motor[motor5] = -50;
		motor[motor7] = -50;
		after = 1;
		before = 0;
	}
	else if (signal3 == 0 && signal4 == 1)
	{
		stopTask(getValueChange);
		hasValueChange = true;
		motor[motor5] = 100;
		motor[motor7] = 100;
		before = 1;
		after = 0;
	}
	else if (signal3 == 0 && signal4 == 0 && before == 1)
	{
		motor[motor5] = 15;
		motor[motor7] = 15;
	}
	else if (signal3 == 0 && signal4 == 0 && after == 1)
	{
		motor[motor5] = -15;
		motor[motor7] = -15;
	}
	else
	{
		motor[motor5] = 0;
		motor[motor7] = 0;
	}
}

void npick(int signal3, int signal4) //Pick without low current
{
	if (signal3 == 1 && signal4 == 0)
	{
		motor[motor5] = -100;//pick
		motor[motor7] = -100;
	}
	else if (signal3 == 0 && signal4 == 1)
	{
		motor[motor5] = 100;
		motor[motor7] = 100;
		before = 1;
	}
	else
	{
		motor[motor5] = 0;
		motor[motor7] = 0;
	}
}

void updown(int signal1, int signal2) //up or down with low current
{
	if (signal1 > 0 && signal2 == 0)//up
	{
		motor[motor4] = up_and_down_speed;
		motor[motor6] = up_and_down_speed;
		arma = 1;
	}
	else if (signal1 == 0 && signal2 > 0)//down
	{
		motor[motor4] = -up_and_down_speed;
		motor[motor6] = -up_and_down_speed;
		arma = 0;
	}
	else if (signal1 == 0 && signal2 == 0 && arma == 0)  //down low current
	{
		motor[motor4] = -20;
		motor[motor6] = -20;
	}
	else if (signal1 == 0 && signal2 == 0 && arma == 1) //up low current
	{
		motor[motor4] = 10;
		motor[motor6] = 10;
	}
	else
	{
		motor[motor4] = 0;
		motor[motor6] = 0;
	}
}

void nupdown(int signal1, int signal2) //up or down without low current
{
	if (signal1 > 0 && signal2 == 0)//up
	{
		motor[motor4] = up_and_down_speed;
		motor[motor6] = up_and_down_speed;
	}
	else if (signal1 == 0 && signal2 > 0)//down
	{
		motor[motor4] = -up_and_down_speed;
		motor[motor6] = -up_and_down_speed;
	}
	else
	{
		motor[motor4] = 0;
		motor[motor6] = 0;
	}
}

void manualConrtol()
{
	while (true)
	{
		if (mode % 2 == 0) //with low current
		{
			while (true)
			{
				reading();
				move(joy_forward, joy_turn, signal5, signal6);
				updown(signal1, signal2);
				zpick(signal3, signal4);
				if (signal7 == 1)break;
			}
			mode++;
		}
		wait10Msec(30);
		if (mode % 2 == 1)
		{
			while (true) //without low current
			{
				reading();
				move(joy_forward, joy_turn, signal5, signal6);
				nupdown(signal1, signal2);
				npick(signal3, signal4);
				if (signal7 == 1)break;
			}
			mode++;
		}
		wait10Msec(30);
	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	/*if(SensorValue(DJ_4)==0&&SensorValue(DJ_5)==0&&SensorValue(DJ_6)==0)
	{
	Beijingleft();
	}
	else if(SensorValue(DJ_4)>0&&SensorValue(DJ_5)==0&&SensorValue(DJ_6)==0)
	{
	JCLeftmiddle();
	}
	else if(SensorValue(DJ_4)==0&&SensorValue(DJ_5)>0&&SensorValue(DJ_6)==0)
	{
	JCLeftright();
	}
	else if(SensorValue(DJ_4)==0&&SensorValue(DJ_5)==0&&SensorValue(DJ_6)>0)
	{
	Beijingleftwait();
	}
	else if(SensorValue(DJ_4)>0&&SensorValue(DJ_5)>0&&SensorValue(DJ_6)==0)
	{
	JCLeftmiddlewait();
	}
	else if(SensorValue(DJ_4)>0&&SensorValue(DJ_5)>0&&SensorValue(DJ_6)>0)
	{
	JCLeftrightwait();
	}
	/*	else if(SensorValue(DJ_4)==0&&SensorValue(DJ_5)>0&&SensorValue(DJ_6)>0)
	{	JCRightleft();}
	else if(SensorValue(DJ_4)>0&&SensorValue(DJ_5)>0&&SensorValue(DJ_6)>0)
	{	JCRightrighttui();}*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop
	manualConrtol();
}
