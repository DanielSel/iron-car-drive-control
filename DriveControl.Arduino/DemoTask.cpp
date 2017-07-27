#include "DemoTask.h"

using namespace motorcontrol;

DemoTask::DemoTask(MotorControl* motorControl, SteeringControl* steeringControl, int interval) : Task(interval)
{
	this->motorControl = motorControl;
	this->steeringControl = steeringControl;
}


DemoTask::~DemoTask()
{
}

void DemoTask::execute()
{
	if(waitTimeOver == false)
	{
		waitTimeOver = true;
	}

	else
	{
		if(done == false)
		{
			// Circle Left
			if(demoScenario == 1)
			{
				steeringControl->setPower(STEERING_PWM_VALUE_MIN);
				motorControl->setPower(MOTOR_PWM_VALUE_NEUTRAL + 80);
			}

			// Circle Right
			if (demoScenario == 2)
			{
				steeringControl->setPower(STEERING_PWM_VALUE_MAX);
				motorControl->setPower(MOTOR_PWM_VALUE_NEUTRAL + 80);
			}

			done = true;
		}
	}
}

void DemoTask::setDemoMessageValue(int value)
{
	demoScenario = value;
	waitTimeOver = false;
	done = false;
}
