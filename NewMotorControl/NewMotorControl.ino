/*
 Name:		NewMotorControl.ino
 Created:	15-May-17 11:25:44 AM
 Author:	Daniel
*/

#include "Arduino.h"

// System Components
#include "SerialInterface.h"
#include "MotorControl.h"

// Tasks
#include "InputControlTask.h"

using namespace motorcontrol;

// Task Definitions
// TODO: List/Vector implementation for Arduino
Task* inputControlTask;


// the setup function runs once when you press reset or power the board
void setup() {
	LOG::INITIALIZE(LOG_LEVEL_DEBUG);
	SerialInterface::initialize(19200);
	MotorControl* motorControl = new MotorControl();

	inputControlTask = new InputControlTask(motorControl);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int time = millis();
	inputControlTask->loop(time);
}
