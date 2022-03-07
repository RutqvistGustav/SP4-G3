#include "stdafx.h"
#include "NodeFloat.h"

NodeFloat::NodeFloat()
{
	mName = "Float";
	mCategory = "DataTypes";
	mType = eNodeType::Float;

	CreatePins();
}

NodeFloat::NodeFloat(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "Float";
	mCategory = "DataTypes";
	mType = eNodeType::Float;
	mGraph = aGraph;

	CreatePins();
}

NodeFloat::NodeFloat(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeFloat::CreatePins()
{
	CreatePin("In", PinType::Exec, PinDirection::In);
	CreatePin("Value Out", PinType::Float, PinDirection::Out);
}

int NodeFloat::Run()
{
	/*const float value = std::any_cast<float>(mPins[1]->data);
	mPins[2]->data = value;*/

	return 1;
}
