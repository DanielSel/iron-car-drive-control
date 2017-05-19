#pragma once

#include "Task.h"
#include "SerialInterface.h"
#include "MotorControl.h"
#include "SteeringControl.h"

namespace motorcontrol
{

class SerialInputControlTask :
	public Task
{
public:
	SerialInputControlTask(MotorControl* motorControl, SteeringControl* steeringControl);
	SerialInputControlTask(int interval, MotorControl* motorControl, SteeringControl* steeringControl);
	~SerialInputControlTask();

	void execute() override;
	void setOverride(boolean active);

private:
	boolean overrideFlag;
	MotorControl* motorControl;
	SteeringControl* steeringControl;
};

}
