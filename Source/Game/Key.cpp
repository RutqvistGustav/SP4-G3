#include "stdafx.h"
#include "Key.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

// TODO: REMOVE
#include <iostream>

Key::Key(Scene* aScene, PowerUpType aPowerupType)
	: Collectable(aScene, aPowerupType)
{
	InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Entities.json").at("Key"));
}

void Key::InitWithJson(const JsonData& someProperties)
{
	mySprite = std::make_shared<SpriteWrapper>(someProperties.at("SpritePath"));
}

void Key::OnCollect(Player* /*aPlayer*/)
{
	// TODO Activate dialogue box
	// Then start transition to nextlevel.
}
