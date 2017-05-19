#include "ReadPwmInterrupt.h"
using namespace motorcontrol;


ReadPwmInterrupt::ReadPwmInterrupt(int pwmPin, volatile unsigned long* pwmValue)
{
	this->pwmPin = pwmPin;
	this->pwmValue = pwmValue;
	*(this->pwmValue) = 0;
	this->prevTime = 0;
	pinToInterruptMap[pwmPin] = this;
	enableInterrupt(pwmPin, ReadPwmInterrupt::handleInterruptRising, RISING);
}

ReadPwmInterrupt::~ReadPwmInterrupt()
{
	disableInterrupt(pwmPin);
	*(this->pwmValue) = 0;
}

ReadPwmInterrupt** ReadPwmInterrupt::pinToInterruptMap = new ReadPwmInterrupt*[14];

void ReadPwmInterrupt::handleInterruptRising()
{
	pinToInterruptMap[arduinoInterruptedPin]->handlePwmPinRising();
}

void ReadPwmInterrupt::handleInterruptFalling()
{
	pinToInterruptMap[arduinoInterruptedPin]->handlePwmPinFalling();
}

void ReadPwmInterrupt::handlePwmPinRising()
{
	prevTime = micros();
	enableInterrupt(pwmPin, ReadPwmInterrupt::handleInterruptFalling, FALLING);
}

void ReadPwmInterrupt::handlePwmPinFalling()
{
	*pwmValue = micros() - prevTime;
	enableInterrupt(pwmPin, ReadPwmInterrupt::handleInterruptRising, RISING);
}