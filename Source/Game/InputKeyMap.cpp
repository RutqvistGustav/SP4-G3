#include "stdafx.h"
#include "InputKeyMap.h"

InputKeyMap* InputKeyMap::ourInstance = nullptr;

InputKeyMap* InputKeyMap::Get()
{
	if (!ourInstance)
	{
		ourInstance = new InputKeyMap();
		ourInstance->Init();
	}
	return ourInstance;
}

void InputKeyMap::Init()
{
	keyMap.push_back(std::make_pair<std::string, int>("A", 0x41));
	keyMap.push_back(std::make_pair<std::string, int>("W", 0x57));
	keyMap.push_back(std::make_pair<std::string, int>("S", 0x53));
	keyMap.push_back(std::make_pair<std::string, int>("D", 0x44));
	keyMap.push_back(std::make_pair<std::string, int>("Space", 0x20));
}
