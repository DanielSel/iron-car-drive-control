#pragma once
#include "SerialInputControlTask.h"
#include "RcInputControlTask.h"
#include "DemoTask.h"

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
	void setDemoTaskScenario(int scenario);

	void setSerialInputControlTask(SerialInputControlTask* serialInputControlTask);
	void setRcInputControlTask(RcInputControlTask* rcInputControlTask);
	void setDemoTask(DemoTask* demoTask);

private:
	SerialInputControlTask* serialInputControlTask;
	RcInputControlTask* rcInputControlTask;
	DemoTask* demoTask;
};

}


