#pragma once
#include "../Externals/nlohmann/json.hpp"
#include <string>
#include <map>
#include <fstream>

class JsonManager
{
public:
	JsonManager();
	~JsonManager();

	std::map<std::string, nlohmann::json>& GetJsonData();

	std::string SetSpritePath(const std::string&, const std::string&) const;
	void LoadArrays(const std::string&, const std::string&);

private:

	void InitAllFiles();
	const std::string myMainJsonFile = "JsonFiles/MainJson.json";

	std::map<std::string, nlohmann::json> myJsonData;

};
