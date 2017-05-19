#include "InputController.h"
using namespace motorcontrol;

InputController::InputController()
{
}


InputController::~InputController()
{
}

void InputController::reset()
{
	this->serialInputControlTask->setOverride(false);
	this->rcInputControlTask->resetInputError();
}

void InputController::enableRcOverride()
{
	this->serialInputControlTask->setOverride(true);
}

void InputController::disableRcOverride()
{
	this->serialInputControlTask->setOverride(false);
}

void InputController::setSerialInputControlTask(SerialInputControlTask * serialInputControlTask)
{
	this->serialInputControlTask = serialInputControlTask;
}

void InputController::setRcInputControlTask(RcInputControlTask * rcInputControlTask)
{
	this->rcInputControlTask = rcInputControlTask;
}
