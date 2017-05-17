#pragma once

#include "Arduino.h"

#include "SerialInterface.h"

#define LOG Logger

namespace motorcontrol
{
	const int LOG_LEVEL_CRITICAL = 5;
	const int LOG_LEVEL_ERROR = 4;
	const int LOG_LEVEL_WARNING = 3;
	const int LOG_LEVEL_INFO = 2;
	const int LOG_LEVEL_DEBUG = 1;
	const int LOG_LEVEL_TRACE = 0;

class Logger
{
public:
	static void INITIALIZE(int logLevel);

	static void CRITICAL(String message);
	static void ERROR(String message);
	static void WARNING(String message);
	static void INFO(String message);
	static void DEBUG(String message);
	static void TRACE(String message);

	~Logger();

private:
	static Logger* INSTANCE();
	static void LOG_MESSAGE(int logLevel, String message);
	
	boolean initialized;
	int logLevel;

	Logger();
	void initialize(int logLevel);
	void logMessage(int logLevel, String message);
};

}
