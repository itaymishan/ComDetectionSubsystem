#include "JsonParser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/ParseHandler.h>

using namespace std;
using namespace Poco::JSON;
using namespace Poco::Dynamic;


JsonParser::JsonParser()
{
	ifstream t("..\\Config\\file.json");
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	cout << str << endl;

	Parser parser;
	ParseHandler *ptrHandler = new ParseHandler();
	parser.setHandler(ptrHandler);
	
	Var ParseResult				= parser.parse(str);
	Var result					= ptrHandler->asVar();
	Object::Ptr object			= result.extract<Object::Ptr>();
	
	Var logo_X_loc				= object->get("logo_X_loc");
	int nlogo_X_loc				= logo_X_loc.convert<int>();

	Var logo_Y_loc				= object->get("logo_Y_loc");
	int nlogo_Y_loc				= logo_Y_loc.convert<int>();

	Var logo_tolerance_value	= object->get("logo_tolerance_value");
	int nlogo_tolerance_value	= logo_tolerance_value.convert<int>();
	t.close();

	Var imagePath				= object->get("image_template_file_path");
	//char *pchImagePath			= imagePath.convert<char[]>();
	t.close();
}


JsonParser::~JsonParser()
{
}
