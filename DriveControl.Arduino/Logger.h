#pragma once

#include "Arduino.h"

#include "SerialInterface.h"

#define LOG Logger
#define LOGLEVEL LogLevel

namespace motorcontrol
{

enum LogLevel {CRITICAL, ERROR, WARNING, INFO, DEBUG, TRACE};

class Logger
{
public:
	static void INITIALIZE(LogLevel logLevel);

	static void CRITICAL(String message);
	static void ERROR(String message);
	static void WARNING(String message);
	static void INFO(String message);
	static void DEBUG(String message);
	static void TRACE(String message);

	~Logger();
	
private:
	static Logger* INSTANCE();
	static void LOG_MESSAGE(LogLevel logLevel, String message);
	
	boolean initialized;
	int logLevel;

	Logger();
	void initialize(LogLevel logLevel);
	void logMessage(LogLevel logLevel, String message);
};

}
