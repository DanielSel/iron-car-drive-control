#include <EnableInterrupt.h>

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
#define MOTOR_PWM_PIN 11
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

 enableInterrupt(12, debugProcessEdgeChangeRISING, RISING);
 enableInterrupt(12, debugProcessEdgeChangeFALLING, FALLING);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int time = millis();
	inputControlTask->loop(time);
}

// ------------------
// DEBUG STUFF
// ------------------

volatile int previousTime = 0;
volatile int pwmTime = 0;

void debugLoop(int time)
{
  static int lastExecutionTime = 0;
  if (time - lastExecutionTime > 500)
  {
    Serial.println("PIN12 says: " + static_cast<String>(pwmTime));
  }
}

void debugProcessEdgeChangeRISING()
{
  previousTime = micros();
}
void debugProcessEdgeChangeFALLING()
{
  pwmTime = micros() - previousTime;
}
