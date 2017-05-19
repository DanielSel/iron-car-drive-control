#pragma once
#include "Logger.h"
#include "Task.h"
#include "MotorControl.h"
#include "SteeringControl.h"
#include "InputController.h"

namespace motorcontrol 
{

const int RC_INPUT_TOLERANCE = 25;
const int RC_SANITY_THRESHOLD = 250;

class InputController;

class RcInputControlTask :
	public Task
{
public:
	RcInputControlTask(volatile unsigned long* rcMotorPwmValue, volatile unsigned long* rcSteeringPwmValue, InputController* inputController, MotorControl* motorControl, SteeringControl* steeringControl);
	RcInputControlTask(volatile unsigned long* rcMotorPwmValue, volatile unsigned long* rcSteeringPwmValue, InputController* inputController, MotorControl* motorControl, SteeringControl* steeringControl, int interval);
	~RcInputControlTask();

	void execute() override;
	void resetInputError();

private:
	volatile unsigned long* rcMotorPwmValue;
	volatile unsigned long* rcSteeringPwmValue;
	MotorControl* motorControl;
	SteeringControl* steeringControl;
	InputController* inputController;

	bool triggerMotor;
	bool triggerSteering;
	bool inputError;
};

}


