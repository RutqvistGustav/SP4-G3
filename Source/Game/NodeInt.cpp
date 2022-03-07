#include "stdafx.h"
#include "NodeInt.h"

NodeInt::NodeInt()
{
	SetData();
	CreatePins();
}

NodeInt::NodeInt(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mGraph = aGraph;
	SetData();
	CreatePins();
}

NodeInt::NodeInt(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeInt::SetData()
{
	mName = "Int";
	mCategory = "Variables";
	mType = eNodeType::Int;
}

void NodeInt::CreatePins()
{
	CreatePin("", PinType::Exec, PinDirection::In);
	CreatePin("Value Out", PinType::Int, PinDirection::Out);
	CreatePin("", PinType::Exec, PinDirection::Out);
}

int NodeInt::Run()
{
	return 2;
}
