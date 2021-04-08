#include "stdafx.h"

#include "JsonManager.h"

JsonManager::JsonManager()
{
	InitAllFiles();
}
JsonManager::~JsonManager() = default;

const JsonData& JsonManager::GetData(const std::string& aFileName) const
{
	assert(myJsonData.count(aFileName) > 0 && "Did you forget to add the json file to MainJson.json?");

	return myJsonData.at(aFileName);
}

std::string JsonManager::SetSpritePath(const std::string& aVaribleName, const std::string& aFilePath) const
{
	std::string aSpriteName = myJsonData.at(aFilePath)[aVaribleName];
	return aSpriteName;
}

void JsonManager::InitAllFiles()
{
	std::ifstream mainFile(myMainJsonFile);

	nlohmann::json jsonDataMain = nlohmann::json::parse(mainFile, nullptr, true, true);

	for (int i = 0; i < jsonDataMain["FilePaths"].size(); ++i)
	{
		std::string filePath = jsonDataMain["FilePaths"][i];

		std::ifstream file(filePath);
		nlohmann::json jsonGameFile = nlohmann::json::parse(file, nullptr, true, true);
		myJsonData[filePath] = jsonGameFile;
	}
}
