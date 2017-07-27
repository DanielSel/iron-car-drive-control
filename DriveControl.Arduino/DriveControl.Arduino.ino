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
#include "InputController.h"

// Tasks & Interrupts
#include "Task.h"
#include "SerialInputControlTask.h"
#include "RcInputControlTask.h"
#include "ReadPwmInterrupt.h"
#include "DemoTask.h"

using namespace motorcontrol;


// PIN Definitions
#define RC_INPUT_MOTOR_PIN 12
#define RC_INPUT_STEERING_PIN 11
#define MOTOR_OUTPUT_PIN 10
#define STEERING_OUTPUT_PIN 9

// Input Controller
InputController* inputController;

// Task Definitions
SerialInputControlTask* serialInputControlTask;
RcInputControlTask* rcInputControlTask;
DemoTask* demoTask;

// Interrupt Definitions
ReadPwmInterrupt* readRcMotorPwm;
ReadPwmInterrupt* readRcSteeringPwm;

// Input PWM Signals
volatile unsigned long rcMotorPwmValue;
volatile unsigned long rcSteeringPwmValue;


// the setup function runs once when you press reset or power the board
void setup() {
	// Initialize Logging and Serial Communication
	LOG::INITIALIZE(LOGLEVEL::INFO);
	SerialInterface::initialize(19200);

	// Setup Pins
	pinMode(RC_INPUT_MOTOR_PIN, INPUT_PULLUP);
	pinMode(RC_INPUT_STEERING_PIN, INPUT_PULLUP);
	pinMode(MOTOR_OUTPUT_PIN, OUTPUT);
	pinMode(STEERING_OUTPUT_PIN, OUTPUT);

	// Initialize Control Components
	MotorControl* motorControl = new MotorControl(MOTOR_OUTPUT_PIN);
	SteeringControl* steeringControl = new SteeringControl(STEERING_OUTPUT_PIN);

	// Setup Input Control
	inputController = new InputController();
	serialInputControlTask = new SerialInputControlTask(inputController, motorControl, steeringControl, 200);
	rcInputControlTask = new RcInputControlTask(&rcMotorPwmValue, &rcSteeringPwmValue, inputController, motorControl, steeringControl, 20);
	inputController->setSerialInputControlTask(serialInputControlTask);
	inputController->setRcInputControlTask(rcInputControlTask);

	// Attach PWM Interrupts
	readRcMotorPwm = new ReadPwmInterrupt(RC_INPUT_MOTOR_PIN, &rcMotorPwmValue);
	readRcSteeringPwm = new ReadPwmInterrupt(RC_INPUT_STEERING_PIN, &rcSteeringPwmValue);

	// Demo Task
	demoTask = new DemoTask(motorControl, steeringControl, 7000);
	inputController->setDemoTask(demoTask);

	// Reset Input Controller to finish initialization
	inputController->reset();
	LOG::INFO("ECU initialized.");
}

// the loop function runs over and over again until power down or reset
void loop() {
	unsigned long time = millis();
	serialInputControlTask->loop(time);
	rcInputControlTask->loop(time);
	demoTask->loop(time);
	//debugLoop(time);
}

// ------------------
// DEBUG STUFF
// ------------------

void debugLoop(unsigned long time)
{
  static unsigned long lastExecutionTime = 0;
  if (time - lastExecutionTime > 500)
  {
    Serial.println("PWM Motor: " + static_cast<String>(rcMotorPwmValue));
	Serial.println("PWM Steering: " + static_cast<String>(rcSteeringPwmValue));
	lastExecutionTime = time;
  }
}
