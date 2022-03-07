#pragma once
#include <filesystem>
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

class Tool
{
public:
	Tool(const char* aConfigPath, GlobalServiceProvider* aGSP) :
		myIsEnabled(false), myHasChanged(false), myConfigPath(aConfigPath)
	{
		if (aConfigPath)
		{
			myData = aGSP->GetJsonManager()->GetData(aConfigPath);
		}
	};

	Tool() :
		myIsEnabled(false), myHasChanged(false), myConfigPath(nullptr)
	{
	};

	virtual ~Tool() = default;

	virtual void Update() = 0;

	inline void SaveData()
	{
		std::ofstream file(myConfigPath);
		file << std::setw(4) << myData << std::endl;
		file.close();
	}

protected:
	JsonData myData;
	const char* myConfigPath;

	bool myIsEnabled;
	bool myHasChanged;
};