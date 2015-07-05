#include "StateMachine.h"
#include "AppLogger.h"
#include "ConfigurationManager.h"


StateMachine::StateMachine() : m_eCurrentState(eUNKNOWN_STATE)
{
	m_httpAdapter = new HttpRequest();
}


eSTATE StateMachine::GetState()
{
	return m_eCurrentState;
}

void StateMachine::SetState(eSTATE eState)
{
	if(eState == m_eCurrentState)
	{
		return;
	}
	switch(eState)
	{
		case eNEGATIVE_IMAGE_FOUND_STATE:
		{
			printf("Current state is: eNEGATIVE_IMAGE_FOUND_STATE\n");
			m_eCurrentState = eNEGATIVE_IMAGE_FOUND_STATE;
			//char *data = "cid=1&start=1";
			std::string buffer = "cid=" + ConfigurationManager::GetInstance().activeChannel + "&" + "start=1";

			std::cout << "\n---------------------------------------------\nSend Commercial Start!!!\n---------------------------------------------\n" << std::endl;
			std::cout << buffer << std::endl;
			m_httpAdapter->SendHttpPostRequestWithData(ConfigurationManager::GetInstance().commercialsUrl, buffer);
			//m_httpAdapter->SendHttpPostRequestWithData("http://46.121.98.47:7879/comfree/dev/commercials.php", buffer);
			AppLogger::GetInstance().WriteLogEntry("Send Commercial Start");
			
		}
		break;
		case ePOSITIVE_IMAGE_FOUND_STATE:
		{
			printf("Current state is: ePOSITIVE_IMAGE_FOUND_STATE\n");
			m_eCurrentState = ePOSITIVE_IMAGE_FOUND_STATE;
			//char * json = "cid=1&start=0";
			std::string buffer = "cid=" + ConfigurationManager::GetInstance().activeChannel + "&" + "start=0";
			std::cout << "\n---------------------------------------------\n Send Commercial Stop!!!\n---------------------------------------------\n" << std::endl;
			std::cout << buffer << std::endl;
			m_httpAdapter->SendHttpPostRequestWithData(ConfigurationManager::GetInstance().commercialsUrl, buffer);
			//m_httpAdapter->SendHttpPostRequestWithData("http://46.121.98.47:7879/comfree/dev/commercials.php", buffer);
			AppLogger::GetInstance().WriteLogEntry("Send Commercial End");
		}
		break;
		case eUNKNOWN_STATE:
		{
			printf("Current state is: eUNKNOWN_STATE\n");
			m_eCurrentState = eUNKNOWN_STATE;
		}
		break;
		default:
		{
			printf("Current state is: Not legal\n");
		}
		break;
	}
}
