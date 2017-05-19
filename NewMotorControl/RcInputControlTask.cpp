#include "RcInputControlTask.h"
using namespace motorcontrol;

RcInputControlTask::RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, MotorControl * motorControl, SteeringControl * steeringControl) : RcInputControlTask(rcMotorPwmValue, rcSteeringPwmValue, TASK_DEFAULT_INTERVAL_MS, motorControl, steeringControl, nullptr)
{
}

RcInputControlTask::RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, int interval, MotorControl * motorControl, SteeringControl * steeringControl) : RcInputControlTask(rcMotorPwmValue, rcSteeringPwmValue, interval, motorControl, steeringControl, nullptr)
{
}

RcInputControlTask::RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, MotorControl * motorControl, SteeringControl * steeringControl, SerialInputControlTask * serialInputControlTask) : RcInputControlTask(rcMotorPwmValue, rcSteeringPwmValue, TASK_DEFAULT_INTERVAL_MS, motorControl, steeringControl, serialInputControlTask)
{
}

RcInputControlTask::RcInputControlTask(volatile int* rcMotorPwmValue, volatile int* rcSteeringPwmValue, int interval, MotorControl * motorControl, SteeringControl * steeringControl, SerialInputControlTask * serialInputControlTask) : Task(interval)
{
	this->rcMotorPwmValue = rcMotorPwmValue;
	this->rcSteeringPwmValue = rcSteeringPwmValue;
	this->motorControl = motorControl;
	this->steeringControl = steeringControl;
	this->serialInputControlTask = serialInputControlTask;
}

RcInputControlTask::~RcInputControlTask()
{
}

void RcInputControlTask::execute()
{
	// If the Motor Input from RC has a real signal and is not NEUTRAL, override serial commands and use RC values
	if (*(this->rcMotorPwmValue) > MOTOR_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE
		|| *(this->rcMotorPwmValue) < MOTOR_PWM_VALUE_NEUTRAL - RC_INPUT_TOLERANCE
		&& *(this->rcMotorPwmValue) > MOTOR_PWM_VALUE_NOSIGNAL + RC_INPUT_TOLERANCE)
	{
		if (serialInputControlTask != nullptr)
		{
			serialInputControlTask->setOverride(true);
		}
		motorControl->setPower(*(this->rcMotorPwmValue));
	}

	// If the Steering Input from RC has a real signal and is not NEUTRAL, override serial commands and use RC values
	if (*(this->rcSteeringPwmValue) > STEERING_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE
		|| *(this->rcSteeringPwmValue) < STEERING_PWM_VALUE_NEUTRAL - RC_INPUT_TOLERANCE
		&& *(this->rcSteeringPwmValue) > STEERING_PWM_VALUE_NOSIGNAL + RC_INPUT_TOLERANCE)
	{
		if (serialInputControlTask != nullptr)
		{
			serialInputControlTask->setOverride(true);
		}
		steeringControl->setPower(*(this->rcSteeringPwmValue));
	}
}
