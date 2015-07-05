#include "StateMachine.h"
#include <functional>

#pragma once
class CController
{
public:
	CController();
	~CController();
	void Start();
	void Stop();
	
	void addHandler(std::function<void(int)> callback)
	{
		printf("Handler added.../n");
	}
private:

};

