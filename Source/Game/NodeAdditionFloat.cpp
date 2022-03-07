#include "stdafx.h"
#include "NodeAdditionFloat.h"

AdditionFloat::AdditionFloat()
{
	mName = "FloatAddition";
	mCategory = "Math";
	mType = eNodeType::AdditionFloat;

	CreatePins();
}

AdditionFloat::AdditionFloat(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "FloatAddition";
	mCategory = "Math";
	mType = eNodeType::AdditionFloat;
	mGraph = aGraph;

	CreatePins();
}

AdditionFloat::AdditionFloat(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void AdditionFloat::CreatePins()
{
	CreatePin("Float 1", PinType::Float, PinDirection::In);
	CreatePin("Float 2", PinType::Float, PinDirection::In);
	CreatePin("Result", PinType::Float, PinDirection::Out);
}

int AdditionFloat::Run()
{
	mPins[0]->data = std::any_cast<float>(GetPinData(0));
	mPins[1]->data = std::any_cast<float>(GetPinData(1));

	const float float1 = std::any_cast<float>(mPins[0]->data);
	const float float2 = std::any_cast<float>(mPins[1]->data);

	mPins[2]->data = float1 + float2;

	return 2;
}
