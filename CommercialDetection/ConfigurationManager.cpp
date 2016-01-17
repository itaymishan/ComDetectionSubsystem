#include "ConfigurationManager.h"

using namespace Poco::Util;
using namespace std;

ConfigurationManager::ConfigurationManager()
{
	try
	{
		AbstractConfiguration *cfg = new XMLConfiguration("..\\Resources\\app_config.xml");

		nNumOfPositiveTemplates = cfg->getInt("NumOfPositiveTemplates");
		nNumOfNegativeTemplates = cfg->getInt("NumOfNegativeTemplates");
		nDebugPrintScreen		= cfg->getInt("configModePrintScreen");
		nSendDetectionsToServer = cfg->getInt("SendDetectionsToServer");

		activeChannel		= cfg->getString("ActiveChannel");

		PrintCoordinates	= cfg->getInt("PrintCoordinates");
		commercialsUrl		= cfg->getString("UrlSendDetectionResults");
	
		pos1Path			= cfg->getString("Pos1.ImagePath");
		pos1XLoc			= cfg->getInt("Pos1.X_LOC");
		pos1YLoc			= cfg->getInt("Pos1.Y_LOC");
		pos1MaxTolerance	= cfg->getInt("Pos1.MAX_TOLERANCE");

		pos2Path			= cfg->getString("Pos2.ImagePath");
		pos2XLoc			= cfg->getInt("Pos2.X_LOC");
		pos2YLoc			= cfg->getInt("Pos2.Y_LOC");
		pos2MaxTolerance	= cfg->getInt("Pos2.MAX_TOLERANCE");

		pos3Path			= cfg->getString("Pos3.ImagePath");
		pos3XLoc			= cfg->getInt("Pos3.X_LOC");
		pos3YLoc			= cfg->getInt("Pos3.Y_LOC");
		pos3MaxTolerance	= cfg->getInt("Pos3.MAX_TOLERANCE");

		pos4Path			= cfg->getString("Pos4.ImagePath");
		pos4XLoc			= cfg->getInt("Pos4.X_LOC");
		pos4YLoc			= cfg->getInt("Pos4.Y_LOC");
		pos4MaxTolerance	= cfg->getInt("Pos4.MAX_TOLERANCE");

		neg1Path			= cfg->getString("Neg1.ImagePath");
		neg1XLoc			= cfg->getInt("Neg1.X_LOC");
		neg1YLoc			= cfg->getInt("Neg1.Y_LOC");
		neg1MaxTolerance	= cfg->getInt("Neg1.MAX_TOLERANCE");

		neg2Path			= cfg->getString("Neg2.ImagePath");
		neg2XLoc			= cfg->getInt("Neg2.X_LOC");
		neg2YLoc			= cfg->getInt("Neg2.Y_LOC");
		neg2MaxTolerance	= cfg->getInt("Neg2.MAX_TOLERANCE");

		neg3Path			= cfg->getString("Neg3.ImagePath");
		neg3XLoc			= cfg->getInt("Neg3.X_LOC");
		neg3YLoc			= cfg->getInt("Neg3.Y_LOC");
		neg3MaxTolerance	= cfg->getInt("Neg3.MAX_TOLERANCE");

		neg4Path			= cfg->getString("Neg4.ImagePath");
		neg4XLoc			= cfg->getInt("Neg4.X_LOC");
		neg4YLoc			= cfg->getInt("Neg4.Y_LOC");
		neg4MaxTolerance	= cfg->getInt("Neg4.MAX_TOLERANCE");
	}
	catch(exception e)
	{
		printf("Failed to read config file /n");
	}

}
