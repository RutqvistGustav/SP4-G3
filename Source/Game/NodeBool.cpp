#include "stdafx.h"
#include "NodeBool.h"

NodeBool::NodeBool()
{
	mName = "Bool";
	mCategory = "Variables";
	mType = eNodeType::Bool;

	CreatePins();
}

NodeBool::NodeBool(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "Bool";
	mCategory = "Variables";
	mType = eNodeType::Bool;
	mGraph = aGraph;

	CreatePins();
}

NodeBool::NodeBool(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeBool::CreatePins()
{
	CreatePin("Exec", PinType::Exec, PinDirection::In);
	CreatePin("Value In", PinType::Bool, PinDirection::In);
	CreatePin("Value Out", PinType::Bool, PinDirection::Out);
}

int NodeBool::Run()
{
	return 2;
}
