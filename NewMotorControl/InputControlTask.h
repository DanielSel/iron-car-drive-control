#pragma once

#include "Task.h"
#include "SerialInterface.h"
#include "MotorControl.h"
#include "SteeringControl.h"

namespace motorcontrol
{

class InputControlTask :
	public Task
{
public:
	InputControlTask(MotorControl* motorControl, SteeringControl* steeringControl);
	~InputControlTask();

	void execute() override;

private:
	MotorControl* motorControl;
	SteeringControl* steeringControl;
};

}
