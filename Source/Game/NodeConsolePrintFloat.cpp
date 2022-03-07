#include "stdafx.h"
#include "NodeConsolePrintFloat.h"
#include <any>
#include <iostream>

ConsolePrintFloat::ConsolePrintFloat()
{
	mName = "PrintFloat";
	mCategory = "Console";
	mType = eNodeType::ConsolePrintFloat;

	CreatePins();
}

ConsolePrintFloat::ConsolePrintFloat(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "PrintFloat";
	mCategory = "Console";
	mType = eNodeType::ConsolePrintFloat;
	mGraph = aGraph;

	CreatePins();
}

ConsolePrintFloat::ConsolePrintFloat(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void ConsolePrintFloat::CreatePins()
{
	CreatePin("Exec", PinType::Exec, PinDirection::In);
	CreatePin("Value", PinType::Float, PinDirection::In);
	CreatePin("Out", PinType::Exec, PinDirection::Out);
}

int ConsolePrintFloat::Run()
{
	mPins[1]->data = std::any_cast<float>(GetPinData(1));
	float sum = std::any_cast<float>(mPins[1]->data);
	std::cout << sum << std::endl;

	return 2;
}
