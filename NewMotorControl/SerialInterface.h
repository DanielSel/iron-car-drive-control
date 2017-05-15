#pragma once

#include "Arduino.h"
#include "Logger.h"
#include "ControlMessage.h"

namespace motorcontrol
{

const int SERIAL_DEFAULT_BAUDRATE = 19200;
const int CONTROL_CODE_MOTOR_POWER = 1;

class SerialInterface
{
public:
	static void initialize();
	static void initialize(int baudrate);
	static bool isMessageAvailable();
	static void writeMessage(String message);
	static ControlMessage readControlMessage();

private:
	static bool initialized;
};

}

