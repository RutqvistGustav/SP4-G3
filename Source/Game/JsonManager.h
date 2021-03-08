#pragma once

#include "JsonData.h"

#include <string>
#include <map>
#include <fstream>

class JsonManager
{
public:

	JsonManager();
	~JsonManager();

	const JsonData& GetData(const std::string& aFileName) const;

	std::string SetSpritePath(const std::string& aVaribleName, const std::string& aFilePath) const;
	void LoadArrays(const std::string& aVaribleName, const std::string& aFilePath);

private:
	void InitAllFiles();

	const std::string myMainJsonFile = "JSON/MainJson.json";
	std::map<std::string, JsonData> myJsonData;
};

