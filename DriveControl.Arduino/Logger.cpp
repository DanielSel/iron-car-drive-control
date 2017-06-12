#include "Logger.h"
using namespace motorcontrol;

Logger::Logger()
{
}

Logger::~Logger()
{
}

Logger * Logger::INSTANCE()
{
	static Logger instance;
	return &instance;
}

void Logger::INITIALIZE(LogLevel logLevel)
{
	Logger::INSTANCE()->initialize(logLevel);
}

void Logger::LOG_MESSAGE(LogLevel logLevel, String message)
{
	Logger::INSTANCE()->logMessage(logLevel, message);
}

void Logger::CRITICAL(String message)
{
	LOG_MESSAGE(LogLevel::CRITICAL, "CRITICAL: " + message);
}

void Logger::ERROR(String message)
{
	LOG_MESSAGE(LogLevel::ERROR, "ERROR: " + message);
}

void Logger::WARNING(String message)
{
	LOG_MESSAGE(LogLevel::WARNING, "WARNING: " + message);
}

void Logger::INFO(String message)
{
	LOG_MESSAGE(LogLevel::INFO, "INFO: " + message);
}

void Logger::DEBUG(String message)
{
	LOG_MESSAGE(LogLevel::DEBUG, "DEBUG: " + message);
}

void Logger::TRACE(String message)
{
	LOG_MESSAGE(LogLevel::TRACE, "TRACE: " + message);
}

void Logger::initialize(LogLevel logLevel)
{
	if (!initialized)
	{
		this->logLevel = logLevel;
		initialized = true;
		LOG::TRACE("Logger initialized!");
	}
	else
	{
		LOG::WARNING("Trying to initialize already initialized Logger!");
	}
}

void Logger::logMessage(LogLevel logLevel, String message)
{
	if (this->initialized && logLevel <= this->logLevel)
	{
		SerialInterface::writeMessage(message);
	}
}