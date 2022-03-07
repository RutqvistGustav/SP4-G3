#include "stdafx.h"
#include "NodeCompareBool.h"

NodeCompareBool::NodeCompareBool()
{
	mName = "CompareBool";
	mCategory = "Math";
	mType = eNodeType::CompareBool;

	CreatePins();
}

NodeCompareBool::NodeCompareBool(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "CompareBool";
	mCategory = "Math";
	mType = eNodeType::CompareBool;
	mGraph = aGraph;

	CreatePins();
}

NodeCompareBool::NodeCompareBool(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeCompareBool::CreatePins()
{
	CreatePin("Bool 1", PinType::Bool, PinDirection::In);
	CreatePin("Bool 2", PinType::Bool, PinDirection::In);
	CreatePin("Out", PinType::Bool, PinDirection::Out);
	CreatePin("In Value", PinType::Bool, PinDirection::Out);
}

int NodeCompareBool::Run()
{
	mPins[0]->data = std::any_cast<bool>(GetPinData(0));
	mPins[1]->data = std::any_cast<bool>(GetPinData(1));

	bool bool1 = std::any_cast<bool>(GetPinData(0));
	bool bool2 = std::any_cast<bool>(GetPinData(1));

	bool result = false;
	if (bool1 == bool2) result = true;

	mPins[2]->data = result;

	return 2;
}