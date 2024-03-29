#include "MotorControl.h"

using namespace motorcontrol;


MotorControl::MotorControl(int pwmPin)
{
	this->pwmPin = pwmPin;
	motorPwmInterface.attach(pwmPin);
	setPower(MOTOR_PWM_VALUE_NEUTRAL);
}


MotorControl::~MotorControl()
{
	motorPwmInterface.detach();
}

void MotorControl::setPower(int power)
{
	if(power < MOTOR_PWM_VALUE_MIN)
	{
		motorPwmInterface.writeMicroseconds(MOTOR_PWM_VALUE_MIN);
		LOG::DEBUG("Too low Motor Control POWER value: " + static_cast<String>(power));
		LOG::DEBUG("Motor Control POWER value set to: " + static_cast<String>(MOTOR_PWM_VALUE_MIN));
	}
	else if (power > MOTOR_PWM_VALUE_MAX)
	{
		motorPwmInterface.writeMicroseconds(MOTOR_PWM_VALUE_MAX);
		LOG::DEBUG("Too high Motor Control POWER value: " + static_cast<String>(power));
		LOG::DEBUG("Motor Control POWER value set to: " + static_cast<String>(MOTOR_PWM_VALUE_MAX));
	}
	else
	{
		motorPwmInterface.writeMicroseconds(power);
		LOG::DEBUG("Motor Control POWER value set to: " + static_cast<String>(power));
	}
}
