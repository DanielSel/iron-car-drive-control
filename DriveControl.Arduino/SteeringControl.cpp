#include "SteeringControl.h"
using namespace motorcontrol;


SteeringControl::SteeringControl(int pwmPin)
{
	this->pwmPin = pwmPin;
	steeringPwmInterface.attach(pwmPin);
	setPower(STEERING_PWM_VALUE_NEUTRAL);
}


SteeringControl::~SteeringControl()
{
	steeringPwmInterface.detach();
}

void SteeringControl::setPower(int power)
{
	if (power < STEERING_PWM_VALUE_MIN)
	{
		steeringPwmInterface.writeMicroseconds(STEERING_PWM_VALUE_MIN);
		LOG::DEBUG("Too low Steering Control POWER value: " + static_cast<String>(power));
		LOG::DEBUG("Steering Control POWER value set to: " + static_cast<String>(STEERING_PWM_VALUE_MIN));
	}
	else if (power > STEERING_PWM_VALUE_MAX)
	{
		steeringPwmInterface.writeMicroseconds(STEERING_PWM_VALUE_MAX);
		LOG::DEBUG("Too high Steering Control POWER value: " + static_cast<String>(power));
		LOG::DEBUG("Steering Control POWER value set to: " + static_cast<String>(STEERING_PWM_VALUE_MAX));
	}
	else
	{
		steeringPwmInterface.writeMicroseconds(power);
		LOG::DEBUG("Steering Control POWER value set to: " + static_cast<String>(power));
	}
}
