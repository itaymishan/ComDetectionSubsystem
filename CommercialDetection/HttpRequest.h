#pragma once

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include <iostream>
#include <stdio.h>

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;


class HttpRequest
{
public:
	~HttpRequest(){}
	HttpRequest();
	HttpRequest(std::string Uri);
	bool SendHttpPostRequestWithData(std::string url, std::string buff);
	bool SendHttpPostRequestWithData(std::string url, char *buff);

private:
	bool bIsFirstTime;

};
