#include "stdafx.h"
#include "NodeBranch.h"

NodeBranch::NodeBranch()
{
	mName = "Branch";
	mCategory = "Statements";
	mType = eNodeType::Branch;

	CreatePins();
}

NodeBranch::NodeBranch(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "Branch";
	mCategory = "Statements";
	mType = eNodeType::Branch;
	mGraph = aGraph;

	CreatePins();
}

NodeBranch::NodeBranch(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeBranch::CreatePins()
{
	CreatePin("Bool In", PinType::Bool, PinDirection::In);
	CreatePin("True", PinType::Bool, PinDirection::Out);
	CreatePin("False", PinType::Bool, PinDirection::Out);
}

int NodeBranch::Run()
{
	bool b = std::any_cast<bool>(GetPinData(0));

	if (b)
	{
		return 1;
	}
    return 2;
}
