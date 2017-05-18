/*
 Name:		NewMotorControl.ino
 Created:	15-May-17 11:25:44 AM
 Author:	Daniel
*/

// Libraries
#define EI_ARDUINO_INTERRUPTED_PIN
#include "EnableInterrupt.h"
#include "Servo.h"
#include "Arduino.h"

// System Components
#include "SerialInterface.h"
#include "MotorControl.h"
#include "SteeringControl.h"

// Tasks & Interrupts
#include "Task.h"
#include "InputControlTask.h"
#include "ReadPwmInterrupt.h"


using namespace motorcontrol;

// PIN Definitions
#define RC_INPUT_MOTOR_PIN 12
#define RC_INPUT_STEERING_PIN 11
#define MOTOR_OUTPUT_PIN 10
#define STEERING_OUTPUT_PIN 9

// Task Definitions
InputControlTask* inputControlTask;

// Interrupt Definitions
ReadPwmInterrupt* readRcMotorPwm;
ReadPwmInterrupt* readRcSteeringPwm;

// Input PWM Signals
volatile int rcMotorPwmValue;
volatile int rcSteeringPwmValue;


// the setup function runs once when you press reset or power the board
void setup() {
	// Initialize Logging and Serial Communication
	LOG::INITIALIZE(LOG_LEVEL_DEBUG);
	SerialInterface::initialize(19200);

	// Setup Pins
	pinMode(RC_INPUT_MOTOR_PIN, INPUT_PULLUP);
	pinMode(RC_INPUT_STEERING_PIN, INPUT_PULLUP);
	pinMode(MOTOR_OUTPUT_PIN, OUTPUT);
	pinMode(STEERING_OUTPUT_PIN, OUTPUT);

	// Initialize Control Components
	MotorControl* motorControl = new MotorControl(MOTOR_OUTPUT_PIN);
	SteeringControl* steeringControl = new SteeringControl(STEERING_OUTPUT_PIN);

	// Create Input Control Task
	inputControlTask = new InputControlTask(motorControl, steeringControl);

	// Attach PWM Interrupts
	readRcMotorPwm = new ReadPwmInterrupt(RC_INPUT_MOTOR_PIN, &rcMotorPwmValue);
	readRcSteeringPwm = new ReadPwmInterrupt(RC_INPUT_STEERING_PIN, &rcSteeringPwmValue);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int time = millis();
	inputControlTask->loop(time);
	debugLoop(time);
}

// ------------------
// DEBUG STUFF
// ------------------

void debugLoop(int time)
{
  static int lastExecutionTime = 0;
  if (time - lastExecutionTime > 500)
  {
    Serial.println("PWM Motor: " + static_cast<String>(rcMotorPwmValue));
	Serial.println("PWM Steering: " + static_cast<String>(rcSteeringPwmValue));
	lastExecutionTime = time;
  }
}