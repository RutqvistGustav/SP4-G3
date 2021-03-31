#include "stdafx.h"
#include "GoalZone.h"

#include "GlobalServiceProvider.h"
#include "GameMessenger.h"

#include "StageClearMessage.h"

// TODO: DEBUG: Remove
#include <iostream>

GoalZone::GoalZone(Scene* aScene) :
	TriggerVolume(aScene, GameObjectTag::Player)
{}

void GoalZone::TriggerEnter(GameObject* /*aGameObject*/)
{
	StageClearMessageData messageData{};

	GetScene()->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::StageClear, &messageData);

	// TODO: DEBUG: Remove
	std::cout << "GoalZone::TriggerEnter" << std::endl;
}
