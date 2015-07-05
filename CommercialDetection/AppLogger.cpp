#include "AppLogger.h"



AppLogger::AppLogger()
{
	AutoPtr<SimpleFileChannel> pChannel(new SimpleFileChannel);
	pChannel->setProperty("path", "CommLogs.log");
	pChannel->setProperty("rotation", "never");
	Logger::root().setChannel(pChannel);
}

AppLogger::AppLogger(std::string path, std::string fileName)
{
	AutoPtr<SimpleFileChannel> pChannel1(new SimpleFileChannel);
	pChannel1->setProperty(path, fileName);
	pChannel1->setProperty("rotation", "never");
	Logger::create(fileName, pChannel1, 1);
	Logger &log1 = Logger::get(fileName);
	log1.information("bla bla");
}

void AppLogger::WriteLogEntry(std::string str)
{
	Poco::LocalDateTime now;
	std::string dateTime = DateTimeFormatter::format(now, "%e %b %Y %H:%M:%S");

	std::string logEntry;
	logEntry.append(dateTime+ " " + str);

	Logger &logger = Logger::get("TestLogger");
	logger.information(logEntry);
}