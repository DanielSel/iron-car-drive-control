#pragma once
#include "Task.h"
#include "MotorControl.h"
#include "SteeringControl.h"

namespace motorcontrol
{

class DemoTask :
	public Task
{
public:
	DemoTask(MotorControl* motorControl, SteeringControl* steeringControl, int interval);
	~DemoTask();

	void execute() override;
	void setDemoMessageValue(int value);

private:
	int demoScenario;
	bool waitTimeOver = false;
	bool done = false;
	MotorControl* motorControl;
	SteeringControl* steeringControl;
};

}