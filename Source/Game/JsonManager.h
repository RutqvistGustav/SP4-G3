#pragma once
#include <string>
#include <map>
#include <fstream>
#include "../Externals/nlohmann/json.hpp"

class JsonManager
{
public:
	JsonManager();
	~JsonManager();

	std::map<std::string, nlohmann::json>& GetJsonData();
	std::string SetSpritePath(const std::string& aVaribleName, const std::string& aFilePath) const;
	void LoadArrays(const std::string& aVaribleName, const std::string& aFilePath);

private:
	void InitAllFiles();

	const std::string myMainJsonFile = "JSON/MainJson.json";
	std::map<std::string, nlohmann::json> myJsonData;
};

