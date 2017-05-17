/*
 Name:		NewMotorControl.ino
 Created:	15-May-17 11:25:44 AM
 Author:	Daniel
*/

#include "Arduino.h"

// System Components
#include "SerialInterface.h"
#include "MotorControl.h"
#include "SteeringControl.h"

// Tasks & Interrupts
#include "InputControlTask.h"


using namespace motorcontrol;

// PIN Definitions
#define MOTOR_PWM_PIN 10
#define STEERING_PWM_PIN 9

// Task Definitions
// TODO: List/Vector implementation for Arduino
Task* inputControlTask;


// the setup function runs once when you press reset or power the board
void setup() {
	LOG::INITIALIZE(LOG_LEVEL_DEBUG);
	SerialInterface::initialize(19200);

	pinMode(MOTOR_PWM_PIN, OUTPUT);
	pinMode(STEERING_PWM_PIN, OUTPUT);
	MotorControl* motorControl = new MotorControl(MOTOR_PWM_PIN);
	SteeringControl* steeringControl = new SteeringControl(STEERING_PWM_PIN);

	inputControlTask = new InputControlTask(motorControl, steeringControl);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int time = millis();
	inputControlTask->loop(time);
}