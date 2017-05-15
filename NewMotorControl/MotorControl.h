#pragma once

#include "Arduino.h"
#include "Logger.h"

namespace motorcontrol
{

class MotorControl
{
public:
	MotorControl();
	~MotorControl();

	void setPower(int power);
};

}