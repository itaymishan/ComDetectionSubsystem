#pragma once
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/Util/XMLConfiguration.h>

class ConfigurationManager
{
public:
	ConfigurationManager();
	~ConfigurationManager();

	static ConfigurationManager& GetInstance()
	{
		static ConfigurationManager configMgr;
		return configMgr;
	}

	int nNumOfPositiveTemplates;
	int nNumOfNegativeTemplates;
	int nDebugPrintScreen;
	int nSendDetectionsToServer;

	std::string activeChannel;

	std::string commercialsUrl;
	int PrintCoordinates;

	std::string pos1Path;
	int pos1XLoc;
	int pos1YLoc;
	int pos1MaxTolerance;

	std::string pos2Path;
	int pos2XLoc;
	int pos2YLoc;
	int pos2MaxTolerance;

	std::string pos3Path;
	int pos3XLoc;
	int pos3YLoc;
	int pos3MaxTolerance;

	std::string pos4Path;
	int pos4XLoc;
	int pos4YLoc;
	int pos4MaxTolerance;

	std::string neg1Path;
	int neg1XLoc;
	int neg1YLoc;
	int neg1MaxTolerance;

	std::string neg2Path;
	int neg2XLoc;
	int neg2YLoc;
	int neg2MaxTolerance;

	std::string neg3Path;
	int neg3XLoc;
	int neg3YLoc;
	int neg3MaxTolerance;

	std::string neg4Path;
	int neg4XLoc;
	int neg4YLoc;
	int neg4MaxTolerance;


};

