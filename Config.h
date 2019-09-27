#pragma once

#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
using namespace rapidjson;

class Config
{
public:
	Config()
	{
	}
	~Config(){}
	bool LoadJson(const char* filename = "config.json")
	{
		std::ifstream f(filename);
		if(f.good())
		{
			std::stringstream buffer;
			buffer << f.rdbuf();
			m_Dom.Parse(buffer.str().c_str());
			return true;
		}
		return false;
	}

	Document& GetDom()
	{
		return m_Dom;
	}
private:
	Document m_Dom;
};

 extern std::unique_ptr<Config> gPtr_Config;