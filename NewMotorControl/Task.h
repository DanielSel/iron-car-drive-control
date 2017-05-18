#pragma once

namespace motorcontrol
{

const int TASK_DEFAULT_INTERVAL_MS = 200;

class Task
{
public:
	Task();
	Task(int interval);
	~Task();

	void loop(int currentTime);

protected:
	virtual void execute();


private:
	int interval;
	int lastExecutionTime;

};

}