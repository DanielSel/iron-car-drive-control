#include "SerialInterface.h"

using namespace motorcontrol;

void SerialInterface::initialize()
{
	SerialInterface::initialize(SERIAL_DEFAULT_BAUDRATE);
}

void SerialInterface::initialize(int baudrate)
{
	Serial.begin(baudrate);
	LOG::DEBUG("Serial Interface initialized with baudrate: " + static_cast<String>(baudrate));
}

bool SerialInterface::isMessageAvailable()
{
	LOG::TRACE("Available bytes on Serial Channel: " + static_cast<String>(Serial.available()));
	bool available = Serial.available() > 0;
	if (available)
	{
		LOG::TRACE("Message available on Serial Channel");
	}

	return available;
}

void SerialInterface::writeMessage(String message)
{
	Serial.println(message);
}

ControlMessage SerialInterface::readControlMessage()
{
	// TODO: Error Handling
	int controlCode = Serial.readStringUntil(':').toInt();
	int controlValue = Serial.readStringUntil(';').toInt();

	LOG::DEBUG("Received new Control Message - Code: " + static_cast<String>(controlCode) + " - Value: " + static_cast<String>(controlValue));
	return ControlMessage{controlCode, controlValue};
}
