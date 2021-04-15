#include "stdafx.h"
#include "DamageVolume.h"

#include "GlobalServiceProvider.h"
#include "SpriteSheetAnimation.h"
#include "SpriteWrapper.h"

#include "RenderQueue.h"
#include "RenderCommand.h"

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"

DamageVolume::DamageVolume(Scene* aScene) :
	TriggerVolume(aScene)
{}

void DamageVolume::InitWithJson(const JsonData & someProperties)
{
	Init();

	myDamage = someProperties.value("Damage", 1);
}

void DamageVolume::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{}

void DamageVolume::TriggerStay(GameObject* aGameObject)
{
	if (aGameObject->GetTag() == GameObjectTag::Player)
	{
		Player* player = static_cast<Player*>(aGameObject);
		player->TakeDamage(myDamage);
	}
	if (aGameObject->GetTag() == GameObjectTag::Enemy)
	{
		Enemy* enemy = static_cast<Enemy*>(aGameObject);
		enemy->TakeDamage(myDamage);
	}
}
