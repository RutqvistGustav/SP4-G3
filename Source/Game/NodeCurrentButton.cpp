#include "stdafx.h"
#include "NodeCurrentButton.h"
#include "GameMessage.h"
#include "Scene.h"
#include "NodeGraphManager.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"

NodeCurrentButton::NodeCurrentButton()
{
	mName = "CurrentButton";
	mCategory = "Gameplay";
	mType = eNodeType::CurrentButton;

	CreatePins();
}

NodeCurrentButton::NodeCurrentButton(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "CurrentButton";
	mCategory = "Gameplay";
	mType = eNodeType::CurrentButton;
	mGraph = aGraph;

	CreatePins();
}

NodeCurrentButton::NodeCurrentButton(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeCurrentButton::CreatePins()
{
	CreatePin("", PinType::Exec, PinDirection::In);
	CreatePin("Next Index", PinType::Int, PinDirection::In);
	CreatePin("Index", PinType::Int, PinDirection::Out);
	CreatePin("", PinType::Exec, PinDirection::Out);
}

int NodeCurrentButton::Run()
{
	int index = std::any_cast<int>(GetPinData(1));

	NodeGraphManager::Get()->GetGSP()->GetGameMessenger()->Send(GameMessage::CurrentButton, &index);

	return 3;
}
