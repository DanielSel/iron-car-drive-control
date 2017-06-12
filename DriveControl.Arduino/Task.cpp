#include "Task.h"
using namespace motorcontrol;


Task::Task()
{
	this->interval = TASK_DEFAULT_INTERVAL_MS;
	this->lastExecutionTime = -TASK_DEFAULT_INTERVAL_MS;
}

Task::Task(unsigned int interval)
{
	this->interval = interval;
	this->lastExecutionTime = -interval;
}


Task::~Task()
{
}

void Task::loop(unsigned long currentTime)
{
	if (currentTime - lastExecutionTime > interval)
	{
		lastExecutionTime = currentTime;
		execute();
	}
}

void Task::execute()
{
}
