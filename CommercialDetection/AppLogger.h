#pragma once
/// MOVE ///
#include "Poco/Logger.h"
#include "Poco/SimpleFileChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/Message.h"
#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"


using Poco::Logger;
using Poco::SimpleFileChannel;
using Poco::AutoPtr;
using Poco::Message;
using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::Timestamp;




class AppLogger
{
public:
	AppLogger();
	AppLogger(std::string path, std::string fileName);
	~AppLogger(){};

	void WriteLogEntry(std::string str);
	
	static AppLogger& GetInstance()
	{
		static AppLogger LOGGER;
		return LOGGER;
	}


private:
	
};

