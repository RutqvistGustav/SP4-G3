#include "stdafx.h"
#include "NodeConsolePrint.h"
#include <any>
#include <iostream>

ConsolePrint::ConsolePrint()
{
	mName = "PrintString";
	mCategory = "Console";
	mType = eNodeType::ConsolePrint;

	CreatePins();
}

ConsolePrint::ConsolePrint(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "PrintString";
	mCategory = "Console";
	mType = eNodeType::ConsolePrint;
	mGraph = aGraph;

	CreatePins();
}

ConsolePrint::ConsolePrint(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void ConsolePrint::CreatePins()
{
	CreatePin("Exec", PinType::Exec, PinDirection::In);
	CreatePin("To Console", PinType::String);
	CreatePin("Out", PinType::Exec, PinDirection::Out);
}

int ConsolePrint::Run()
{
	std::string s = std::any_cast<std::string>(mPins[1]->data);

	std::cout << s << std::endl;

	return 2;
}
