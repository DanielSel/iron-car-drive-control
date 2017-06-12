#include "RcInputControlTask.h"
using namespace motorcontrol;

RcInputControlTask::RcInputControlTask(volatile unsigned long* rcMotorPwmValue, volatile unsigned long* rcSteeringPwmValue, InputController* inputController, MotorControl * motorControl, SteeringControl * steeringControl) : RcInputControlTask(rcMotorPwmValue, rcSteeringPwmValue, inputController, motorControl, steeringControl, TASK_DEFAULT_INTERVAL_MS)
{
}

RcInputControlTask::RcInputControlTask(volatile unsigned long* rcMotorPwmValue, volatile unsigned long* rcSteeringPwmValue, InputController* inputController, MotorControl * motorControl, SteeringControl * steeringControl, int interval) : Task(interval)
{
	this->rcMotorPwmValue = rcMotorPwmValue;
	this->rcSteeringPwmValue = rcSteeringPwmValue;
	this->inputController = inputController;
	this->motorControl = motorControl;
	this->steeringControl = steeringControl;
}

RcInputControlTask::~RcInputControlTask()
{
}

void RcInputControlTask::execute()
{
	// Don't do anything until reset if input error occured 
	if (inputError)
	{
		return;
	}

	// Sanity check values and stop if suspicious
	else if (*(this->rcMotorPwmValue) > MOTOR_PWM_VALUE_MAX + RC_SANITY_THRESHOLD
		|| (*(this->rcMotorPwmValue) < MOTOR_PWM_VALUE_MIN - RC_SANITY_THRESHOLD
			&& *(this->rcMotorPwmValue) > MOTOR_PWM_VALUE_NOSIGNAL + RC_SANITY_THRESHOLD)
		|| *(this->rcSteeringPwmValue) > STEERING_PWM_VALUE_MAX + RC_SANITY_THRESHOLD
		|| (*(this->rcSteeringPwmValue) < STEERING_PWM_VALUE_MIN - RC_SANITY_THRESHOLD
			&& *(this->rcSteeringPwmValue) > STEERING_PWM_VALUE_NOSIGNAL + RC_SANITY_THRESHOLD))
	{
		inputError = true;
		LOG::ERROR("Invalid PWM Signal from Remote Control. Reset device after resolving the Input Error.");
		return;
	}

	// Normal Operation
	else
	{
		// If the Motor Input from RC has a real signal and is not NEUTRAL, override serial commands and use RC values
		if (*(this->rcMotorPwmValue) > MOTOR_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE
			|| *(this->rcMotorPwmValue) < MOTOR_PWM_VALUE_NEUTRAL - RC_INPUT_TOLERANCE
			&& *(this->rcMotorPwmValue) > MOTOR_PWM_VALUE_NOSIGNAL + RC_INPUT_TOLERANCE)
		{
			this->inputController->enableRcOverride();
			this->motorControl->setPower(*(this->rcMotorPwmValue));
			this->triggerMotor = true;
		}
		// If the Motor was active (triggered) and is returning to a neutral state, set neutral signal and disable override
		else if (this->triggerMotor
			&& (
			(*(this->rcMotorPwmValue) < MOTOR_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE
				&& *(this->rcMotorPwmValue) < MOTOR_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE)
				|| (
					*(this->rcMotorPwmValue) >= MOTOR_PWM_VALUE_NOSIGNAL
					&& *(this->rcMotorPwmValue) < MOTOR_PWM_VALUE_NOSIGNAL + RC_INPUT_TOLERANCE)))
		{
			this->motorControl->setPower(MOTOR_PWM_VALUE_NEUTRAL);
			this->inputController->disableRcOverride();
			this->triggerMotor = false;
		}

		// If the Steering Input from RC has a real signal and is not NEUTRAL, override serial commands and use RC values
		if (*(this->rcSteeringPwmValue) > STEERING_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE
			|| *(this->rcSteeringPwmValue) < STEERING_PWM_VALUE_NEUTRAL - RC_INPUT_TOLERANCE
			&& *(this->rcSteeringPwmValue) > STEERING_PWM_VALUE_NOSIGNAL + RC_INPUT_TOLERANCE)
		{
			this->inputController->enableRcOverride();
			this->steeringControl->setPower(*(this->rcSteeringPwmValue));
			this->triggerSteering = true;
		}

		// If the Steering was active (triggered) and is returning to a neutral state, set neutral signal and disable override
		else if (this->triggerSteering
			&& (
			(*(this->rcSteeringPwmValue) < STEERING_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE
				&& *(this->rcSteeringPwmValue) < STEERING_PWM_VALUE_NEUTRAL + RC_INPUT_TOLERANCE)
				|| (
					*(this->rcSteeringPwmValue) >= STEERING_PWM_VALUE_NOSIGNAL
					&& *(this->rcSteeringPwmValue) < STEERING_PWM_VALUE_NOSIGNAL + RC_INPUT_TOLERANCE)))
		{
			this->steeringControl->setPower(STEERING_PWM_VALUE_NEUTRAL);
			this->inputController->disableRcOverride();
			this->triggerSteering = false;
		}
	}
}

void RcInputControlTask::resetInputError()
{
	this->inputError = false;
}