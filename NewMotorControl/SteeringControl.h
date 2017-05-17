#pragma once

#include "Logger.h"
#include "Servo.h"

namespace motorcontrol
{

const int STEERING_PWM_VALUE_MAX = 2100;
const int STEERING_PWM_VALUE_MIN = 900;
const int STEERING_PWM_VALUE_NEUTRAL = 1500;

class SteeringControl
{
public:
	SteeringControl(int pwmPin);
	~SteeringControl();

	void setPower(int power);

private:
	int pwmPin;
	Servo steeringPwmInterface;
};

}


