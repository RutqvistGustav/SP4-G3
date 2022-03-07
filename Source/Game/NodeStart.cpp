#include "stdafx.h"
#include "NodeStart.h"

NodeStart::NodeStart()
{
	mName = "Start";
	mCategory = "StartEnd";
	mType = eNodeType::Start;

	CreatePins();
}

NodeStart::NodeStart(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "Start";
	mCategory = "StartEnd";
	mType = eNodeType::Start;
	mGraph = aGraph;

	CreatePins();
}

NodeStart::NodeStart(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	SetStartNode();
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeStart::CreatePins()
{
	SetStartNode();
	CreatePin("Start", PinType::Exec, PinDirection::Out);
	CreatePin("Loop", PinType::Bool);
}

int NodeStart::Run()
{
	return 0;
}
