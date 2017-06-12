#pragma once
#include "SerialInputControlTask.h"
#include "RcInputControlTask.h"

namespace motorcontrol
{

class SerialInputControlTask;
class RcInputControlTask;

class InputController
{
public:
	InputController();
	~InputController();

	void reset();
	void enableRcOverride();
	void disableRcOverride();

	void setSerialInputControlTask(SerialInputControlTask* serialInputControlTask);
	void setRcInputControlTask(RcInputControlTask* rcInputControlTask);

private:
	SerialInputControlTask* serialInputControlTask;
	RcInputControlTask* rcInputControlTask;
};

}


