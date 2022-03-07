#include "stdafx.h"
#include "NodeButtonClicked.h"
#include "GameMessage.h"
#include "Scene.h"
#include "NodeGraphManager.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"

NodeButtonClicked::NodeButtonClicked()
{
	mName = "ButtonClicked";
	mCategory = "Gameplay";
	mType = eNodeType::ButtonClicked;

	CreatePins();
}

NodeButtonClicked::NodeButtonClicked(const int aId, NodeGraph* aGraph)
{
	mId = aId;
	mName = "ButtonClicked";
	mCategory = "Gameplay";
	mType = eNodeType::ButtonClicked;
	mGraph = aGraph;

	CreatePins();
}

NodeButtonClicked::NodeButtonClicked(std::vector<Pin*> aPins, const std::string& aName, const std::string& aCategory, eNodeType aType, const int aId, NodeGraph* aGraph)
{
	mPins = aPins;
	mName = aName;
	mCategory = aCategory;
	mType = aType;
	mId = aId;
	mGraph = aGraph;
}

void NodeButtonClicked::CreatePins()
{
	CreatePin("", PinType::Exec, PinDirection::In);
	CreatePin("", PinType::Exec, PinDirection::Out);
}

int NodeButtonClicked::Run()
{
	NodeGraphManager::Get()->GetGSP()->GetGameMessenger()->Send(GameMessage::ButtonClicked, nullptr);

	return 1;
}
