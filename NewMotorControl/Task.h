#pragma once

namespace motorcontrol
{

const unsigned int TASK_DEFAULT_INTERVAL_MS = 200;

class Task
{
public:
	Task();
	Task(unsigned int interval);
	~Task();

	void loop(unsigned long currentTime);

protected:
	virtual void execute();


private:
	unsigned int interval;
	unsigned long lastExecutionTime;

};

}