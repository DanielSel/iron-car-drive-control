#pragma once
#include "Arduino.h"
#include "Task.h"
#include "SerialInterface.h"
#include "MotorControl.h"

namespace motorcontrol
{

class InputControlTask :
	public Task
{
public:
	InputControlTask(MotorControl* motorControl);
	~InputControlTask();

	void execute() override;

private:
	MotorControl* motorControl;
};

}