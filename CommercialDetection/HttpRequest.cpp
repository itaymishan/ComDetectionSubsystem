#include "HttpRequest.h"
#include "AppLogger.h"
#include "ConfigurationManager.h"

HttpRequest::HttpRequest()
{
	bIsFirstTime = true;
}

HttpRequest::HttpRequest(std::string Uri)
{

}

bool HttpRequest::SendHttpPostRequestWithData(std::string url, char *buff)
{
	if(false == ConfigurationManager::GetInstance().nSendDetectionsToServer)
	{
		return false;
	}
	try
	{
		URI uri(url);
		std::string path(uri.getPathAndQuery());
		if (path.empty())
		{
			path = "/";
		}
		
		HTTPClientSession session(uri.getHost(), uri.getPort());
		session.setKeepAlive(true);
		
		Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
		req.setContentType("application/x-www-form-urlencoded");
		req.setKeepAlive(true);
		
		std::string reqBody(buff);
		req.setContentLength( reqBody.length() );
		
		std::ostream& myOStream = session.sendRequest(req);
		myOStream << reqBody;
		
		req.write(std::cout);
		
		HTTPResponse res;
		std::istream& iStr = session.receiveResponse(res);  // get the response from server
		//std::cerr << iStr.rdbuf();  // dump server response so you can view it
		printf("\n-----------------------------------\nSend to server Success\n-----------------------------------\n");

	}
	catch(Exception e)
	{
		printf("\n-----------------------------------\nSend to server Failed!!!\n-----------------------------------\n");
		AppLogger::GetInstance().WriteLogEntry("HTTP Send to server Failed!!!");
		return false;
	}
	return true;
}

bool HttpRequest::SendHttpPostRequestWithData(std::string url, std::string buff)
{
	if(false == ConfigurationManager::GetInstance().nSendDetectionsToServer)
	{
		return false;
	}
	if(bIsFirstTime)
	{
		bIsFirstTime = false;
		return false;
	}

	try
	{
		URI uri(url);
		std::string path(uri.getPathAndQuery());
		if (path.empty())
		{
			path = "/";
		}
		
		HTTPClientSession session(uri.getHost(), uri.getPort());
		session.setKeepAlive(true);
		
		Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
		req.setContentType("application/x-www-form-urlencoded");
		req.setKeepAlive(true);
		
		std::string reqBody(buff);
		req.setContentLength( reqBody.length() );
		
		std::ostream& myOStream = session.sendRequest(req);
		myOStream << reqBody;
		
		req.write(std::cout);
		
		HTTPResponse res;
		std::istream& iStr = session.receiveResponse(res);  // get the response from server
		//std::cerr << iStr.rdbuf();  // dump server response so you can view it
		printf("\n-----------------------------------\nSend to server Success\n-----------------------------------\n");

	}
	catch(Exception e)
	{
		printf("\n-----------------------------------\nSend to server Failed!!!\n-----------------------------------\n");
		AppLogger::GetInstance().WriteLogEntry("HTTP Send to server Failed!!!");
		return false;
	}
	return true;
}