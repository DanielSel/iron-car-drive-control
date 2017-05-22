#include "SerialInputControlTask.h"
using namespace motorcontrol;


SerialInputControlTask::SerialInputControlTask(InputController* inputController, MotorControl* motorControl, SteeringControl* steeringControl) : SerialInputControlTask(inputController, motorControl, steeringControl, TASK_DEFAULT_INTERVAL_MS)
{
}

SerialInputControlTask::SerialInputControlTask(InputController* inputController, MotorControl* motorControl, SteeringControl* steeringControl, int interval) : Task(interval)
{
	this->inputController = inputController;
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
				inputController->reset();
			}
			else
			{
				LOG::WARNING("Received Invalid RESET Command. Value: " + static_cast<String>(controlMessage.value));
			}
		}
			
		// Only act on User Input if there is no Override by RC
		else if (!overrideFlag)
		{
			switch (controlMessage.code)
			{
			case CONTROL_CODE_MOTOR_POWER: motorControl->setPower(controlMessage.value); LOG::INFO("Executed Command to set MOTOR power to: " + static_cast<String>(controlMessage.value)); break;
				case CONTROL_CODE_STEERING_POWER: steeringControl->setPower(controlMessage.value); LOG::INFO("Executed Command to set STEERING power to: " + static_cast<String>(controlMessage.value)); break;
				default: LOG::WARNING("Received Message with unknown Control Code: " + static_cast<String>(controlMessage.code));
			}
		}

		else if (overrideFlag)
		{
			LOG::INFO("Override from Remote Control is active");
		}

	}
}

void SerialInputControlTask::setOverride(boolean active)
{
	overrideFlag = active;
	LOG::DEBUG("Override: " + overrideFlag ? "On" : "Off");
}
