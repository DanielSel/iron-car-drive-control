#include "MotorControl.h"
using namespace motorcontrol;


MotorControl::MotorControl()
{
}


MotorControl::~MotorControl()
{
}

void MotorControl::setPower(int power)
{
	// TODO
	LOG::INFO("Motor Control POWER value set to: " + static_cast<String>(power));
}
