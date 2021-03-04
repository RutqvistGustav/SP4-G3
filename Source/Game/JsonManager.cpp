#include "stdafx.h"
#include "JsonManager.h"
#include "stdafx.h"
#include "JsonManager.h"


JsonManager::JsonManager()
{
	InitAllFiles();
}
JsonManager::~JsonManager()
{

}

std::map<std::string, nlohmann::json>& JsonManager::GetJsonData()
{
	return myJsonData;
}

std::string JsonManager::SetSpritePath(const std::string& aVaribleName, const std::string& aFilePath) const
{
	std::string aSpriteName = myJsonData.at(aFilePath)[aVaribleName];
	return aSpriteName;
}

void JsonManager::LoadArrays(const std::string& aVaribleName, const std::string& aFilePath)
{
	if (myJsonData.at(aFilePath).is_array())
	{
		for (int i = 0; i < myJsonData.at(aFilePath)[aVaribleName].size(); i++)
		{

		}
	}
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