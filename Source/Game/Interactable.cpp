#include "stdafx.h"
#include "Interactable.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "InputInterface.h"

#include "Player.h"

#include "GameMessenger.h"
#include "InteractableMessage.h"

#include <cassert>

Interactable::Interactable(Scene* aScene) :
	TriggerVolume(aScene, GameObjectTag::Player)
{}

void Interactable::TriggerStay(GameObject* aGameObject)
{
	assert(aGameObject != nullptr);

	SetInRange(true);

	Player* player = static_cast<Player*>(aGameObject);

	const bool wasInteracting = myIsInteracting;
	myIsInteracting = IsInteracting(player);

	if (!wasInteracting && myIsInteracting)
	{
		OnInteract(player);
	}
}

void Interactable::TriggerExit(GameObject* aGameObject)
{
	assert(aGameObject != nullptr);

	SetInRange(false);
}

bool Interactable::IsInteracting(Player* /*aPlayer*/)
{
	return GetScene()->GetGlobalServiceProvider()->GetInputInterface()->IsPressingUse();
}

void Interactable::SetInRange(bool anInRange)
{
	if (myInRange == anInRange)
		return;

	myInRange = anInRange;

	InteractableMessageData messageData{};
	messageData.myInteractable = this;

	const GameMessage messageType = anInRange ? GameMessage::InteractableEnter : GameMessage::InteractableExit;

	GetScene()->GetGlobalServiceProvider()->GetGameMessenger()->Send(messageType, &messageData);
}
