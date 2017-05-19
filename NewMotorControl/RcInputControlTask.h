#pragma once
#include "Task.h"
#include "SerialInputControlTask.h"

namespace motorcontrol 
{

const int RC_INPUT_TOLERANCE = 25;

class RcInputControlTask :
	public Task
{
public:
	RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, MotorControl* motorControl, SteeringControl* steeringControl);
	RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, int interval, MotorControl* motorControl, SteeringControl* steeringControl);
	RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, MotorControl* motorControl, SteeringControl* steeringControl, SerialInputControlTask* serialInputControlTask);
	RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, int interval, MotorControl* motorControl, SteeringControl* steeringControl, SerialInputControlTask* serialInputControlTask);
	~RcInputControlTask();

	void execute() override;

private:
	volatile int* rcMotorPwmValue;
	volatile int* rcSteeringPwmValue;
	MotorControl* motorControl;
	SteeringControl* steeringControl;
	SerialInputControlTask* serialInputControlTask;

};

}


