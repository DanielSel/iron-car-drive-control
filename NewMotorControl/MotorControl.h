#pragma once

#include "Logger.h"
#include "Servo.h"

namespace motorcontrol
{

const int MOTOR_PWM_VALUE_MAX = 2025;
const int MOTOR_PWM_VALUE_MIN = 955;
const int MOTOR_PWM_VALUE_NEUTRAL = 1500;

class MotorControl
{
public:
	MotorControl(int pwmPin);
	~MotorControl();

	void setPower(int power);

private:
	int pwmPin;
	Servo motorPwmInterface;

};

}
