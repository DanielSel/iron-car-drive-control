#include "SerialInputControlTask.h"
using namespace motorcontrol;


SerialInputControlTask::SerialInputControlTask(MotorControl* motorControl, SteeringControl* steeringControl) : SerialInputControlTask(TASK_DEFAULT_INTERVAL_MS, motorControl, steeringControl)
{
}

SerialInputControlTask::SerialInputControlTask(int interval, MotorControl* motorControl, SteeringControl* steeringControl) : Task(interval)
{
	this->motorControl = motorControl;
	this->steeringControl = steeringControl;
}

SerialInputControlTask::~SerialInputControlTask()
{
}

void SerialInputControlTask::execute()
{
	LOG::TRACE("Executing Input Control Task...");
	if (SerialInterface::isMessageAvailable())
	{
		LOG::TRACE("Reading Control Message...");
		ControlMessage controlMessage = SerialInterface::readControlMessage();

		// Handle RESET Command
		if (controlMessage.code == CONTROL_CODE_RESET)
		{
			if (controlMessage.value == 0)
			{
				LOG::INFO("Received RESET Command");
				motorControl->setPower(MOTOR_PWM_VALUE_NEUTRAL);
				steeringControl->setPower(STEERING_PWM_VALUE_NEUTRAL);
				setOverride(false);
			}
			else
			{
				LOG::WARNING("Received Invalid RESET Command. Value: " + static_cast<String>(controlMessage.value));
			}
		}
			
		// Only act on User Input if there is no Override by RC
		if (!overrideFlag)
		{
			switch (controlMessage.code)
			{
				case CONTROL_CODE_MOTOR_POWER: motorControl->setPower(controlMessage.value); break;
				case CONTROL_CODE_STEERING_POWER: steeringControl->setPower(controlMessage.value); break;
				default: LOG::WARNING("Received Message with unknown Control Code: " + static_cast<String>(controlMessage.code));
			}
		}

	}
}

void SerialInputControlTask::setOverride(boolean active)
{
	overrideFlag = active;
}
