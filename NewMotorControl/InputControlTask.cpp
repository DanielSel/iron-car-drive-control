#include "InputControlTask.h"
using namespace motorcontrol;

InputControlTask::InputControlTask(MotorControl* motorControl)
{
	this->motorControl = motorControl;
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

		switch (controlMessage.code)
		{
			case CONTROL_CODE_MOTOR_POWER: motorControl->setPower(controlMessage.value); break;
			default: LOG::WARNING("Received Message with unknown Control Code: " + static_cast<String>(controlMessage.code));
		}

	}
}
