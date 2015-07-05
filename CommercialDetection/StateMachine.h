#include <stdio.h>
#include "HttpRequest.h"

#pragma once

static enum eSTATE
{
	eNEGATIVE_IMAGE_FOUND_STATE,
	ePOSITIVE_IMAGE_FOUND_STATE,
	eUNKNOWN_STATE
};

class StateMachine
{
public:

	~StateMachine(){};
	void SetState(eSTATE eState);
	eSTATE GetState();
	static StateMachine& GetInstance()
	{
		static StateMachine INSTANCE;
		return INSTANCE;
	}
	
private:
	StateMachine();
	eSTATE m_eCurrentState;
	HttpRequest *m_httpAdapter;

};

