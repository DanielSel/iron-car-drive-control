#pragma once

#define EI_ARDUINO_INTERRUPTED_PIN
#define LIBCALL_ENABLEINTERRUPT
#include "EnableInterrupt.h"

namespace motorcontrol
{

class ReadPwmInterrupt
{
public:
	ReadPwmInterrupt(int pwmPin, volatile unsigned long* pwmValue);
	~ReadPwmInterrupt();

	static void handleInterruptRising();
	static void handleInterruptFalling();

private:
	static ReadPwmInterrupt** pinToInterruptMap;
	void handlePwmPinRising();
	void handlePwmPinFalling();

	int pwmPin;
	volatile unsigned long* pwmValue;
	volatile unsigned long prevTime;
};

}
