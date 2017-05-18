#include "InputControlTask.h"
using namespace motorcontrol;

InputControlTask::InputControlTask(MotorControl* motorControl, SteeringControl* steeringControl)
{
	this->motorControl = motorControl;
	this->steeringControl = steeringControl;
}


InputControlTask::~InputControlTask()
{
}

void InputControlTask::execute()
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

void InputControlTask::setOverride(boolean active)
{
	overrideFlag = active;
}
