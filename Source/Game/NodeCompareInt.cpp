#include "stdafx.h"
#include "NodeCompareInt.h"

NodeCompareInt::NodeCompareInt()
{
	mName = "CompareInt";
	mCategory = "Math";
	mType = eNodeType::CompareInt;

	CreatePins();
}

NodeCompareInt::NodeCompareInt(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "CompareInt";
	mCategory = "Math";
	mType = eNodeType::CompareInt;
	mGraph = aGraph;

	CreatePins();
}

NodeCompareInt::NodeCompareInt(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeCompareInt::CreatePins()
{
	CreatePin("Int 1", PinType::Int, PinDirection::In);
	CreatePin("Int 2", PinType::Int, PinDirection::In);
	CreatePin("Out", PinType::Bool, PinDirection::Out);
}

int NodeCompareInt::Run()
{
	mPins[0]->data = std::any_cast<int>(GetPinData(0));
	mPins[1]->data = std::any_cast<int>(GetPinData(1));

	int int1 = std::any_cast<int>(GetPinData(0));
	int int2 = std::any_cast<int>(GetPinData(1));

	bool b = false;
	if (int1 == int2) b = true;

	mPins[2]->data = b;

	return 2;
}