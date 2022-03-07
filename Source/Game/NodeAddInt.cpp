#include "stdafx.h"
#include "NodeAddInt.h"

NodeAddInt::NodeAddInt()
{
	SetData();
	CreatePins();
}

NodeAddInt::NodeAddInt(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mGraph = aGraph;
	SetData();
	CreatePins();
}

NodeAddInt::NodeAddInt(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeAddInt::SetData()
{
	mName = "Add Int";
	mCategory = "Math";
	mType = eNodeType::AddInt;
}

void NodeAddInt::CreatePins()
{
	CreatePin("Exec", PinType::Exec, PinDirection::In);
	CreatePin("Int In", PinType::Int, PinDirection::In);
	CreatePin("Add Value", PinType::Int, PinDirection::In);
	CreatePin("Result", PinType::Int, PinDirection::Out);
}

int NodeAddInt::Run()
{
	int in = std::any_cast<int>(GetPinData(1));
	int result = in + std::any_cast<int>(GetPinData(2));

	mPins[3]->data = result;

	return 3;
}
