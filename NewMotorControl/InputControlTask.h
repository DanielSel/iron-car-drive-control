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
	void setOverride(boolean active);

private:
	boolean overrideFlag;
	MotorControl* motorControl;
	SteeringControl* steeringControl;
};

}
