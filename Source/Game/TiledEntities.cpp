#include "stdafx.h"
#include "TiledEntities.h"

#include "TiledParser.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "JsonManager.h"

#include "EnemyMessage.h"

#include "DialogueBox.h"

#include "GoalZone.h"

#include "DamageVolume.h"

#include <cassert>

TiledEntities::TiledEntities(const TiledParser* aParser, Scene* aScene) :
	myParser(aParser),
	myScene(aScene)
{}

const TiledEntity* TiledEntities::FindEntityWithType(const std::string& aType)
{
	for (const auto& entity : myParser->myResult->GetEntities())
	{
		if (entity.GetType() == aType)
		{
			return &entity;
		}
	}

	return nullptr;
}

void TiledEntities::SpawnEntities()
{
	for (const auto& entity : myParser->myResult->GetEntities())
	{
		const std::string& type = entity.GetType();

		if (type == "Enemy")
		{
			EnemyMessageData enemyMessageData{};
			enemyMessageData.mySpawnPosition = entity.GetPosition();

			if (entity.GetSubType() == "Zombie")
			{
				enemyMessageData.myEnemyType = EnemyFactory::EnemyType::Zombie;
			}
			else if (entity.GetSubType() == "EliteZombie")
			{
				enemyMessageData.myEnemyType = EnemyFactory::EnemyType::EliteZombie;
			}
			else
			{
				assert(false && "Invalid enemy subtype!");
			}

			myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnEnemy, &enemyMessageData);
		}
		else if (type == "DialogBox")
		{
			std::shared_ptr<DialogueBox> textbox = std::make_shared<DialogueBox>(myScene);
			textbox->Init(entity.GetProperty("DialogID"));
			textbox->SetPosition(entity.GetPosition());
			myScene->AddGameObject(textbox);
		}
		else if (type == "Goal")
		{
			std::shared_ptr<GoalZone> goalZone = std::make_shared<GoalZone>(myScene);
			goalZone->Init();
			goalZone->SetPosition(entity.GetPosition());
			goalZone->SetTriggerSize(entity.GetSize());

			myScene->AddGameObject(goalZone);
		}
		else if (type == "Hazard")
		{
			const std::string subType = entity.HasProperty("SubType") ? entity.GetProperty("SubType") : "Default";
			const JsonData& data = GetEntityData(type)[subType];

			std::shared_ptr<DamageVolume> damageVolume = std::make_shared<DamageVolume>(myScene);
			damageVolume->InitWithJson(data);

			damageVolume->SetPosition(entity.GetPosition());
			damageVolume->SetTriggerSize(entity.GetSize());

			myScene->AddGameObject(damageVolume);
		}
	}
}

const JsonData& TiledEntities::GetEntityData(const std::string& aType)
{
	return myScene->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Entities.json")[aType];
}
