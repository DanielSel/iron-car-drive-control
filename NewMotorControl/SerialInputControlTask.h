#pragma once
#include "Logger.h"
#include "Task.h"
#include "SerialInterface.h"
#include "MotorControl.h"
#include "SteeringControl.h"
#include "InputController.h"

namespace motorcontrol
{

class InputController;

class SerialInputControlTask :
	public Task
{
public:
	SerialInputControlTask(InputController* inputController, MotorControl* motorControl, SteeringControl* steeringControl);
	SerialInputControlTask(InputController* inputController, MotorControl* motorControl, SteeringControl* steeringControl, int interval);
	~SerialInputControlTask();

	void execute() override;
	void setOverride(boolean active);

private:
	boolean overrideFlag;
	MotorControl* motorControl;
	SteeringControl* steeringControl;
	InputController* inputController;
};

}
