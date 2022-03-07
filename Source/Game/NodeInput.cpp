#include "stdafx.h"
#include "NodeInput.h"
#include "InputKeyMap.h"
#include "NodeGraph.h"
#include "InputManager.h"

NodeInput::NodeInput()
{
	mName = "Input";
	mCategory = "General";
	mType = eNodeType::Input;

	CreatePins();
}

NodeInput::NodeInput(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "Input";
	mCategory = "General";
	mType = eNodeType::Input;
	mGraph = aGraph;

	CreatePins();
}

NodeInput::NodeInput(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeInput::CreatePins()
{
	CreatePin("Run", PinType::Exec, PinDirection::In);
	CreatePin("Input Key", PinType::String);
	CreatePin("", PinType::Exec, PinDirection::Out);
}

int NodeInput::Run()
{
	std::string key = std::any_cast<std::string>(mPins[1]->data);

	auto input = mGraph->GetInput();
	
	if (input->IsKeyPressed((InputKeyMap::Get()->GetKey(key))))
	{
		mPins[2]->data = true;
		return 2;
	}

	mPins[2]->data = false;
	return -1;
}
