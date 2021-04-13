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
	TriggerVolume(aScene, GameObjectTag::Player)
{}

void DamageVolume::InitWithJson(const JsonData & someProperties)
{
	Init();

	myDamage = someProperties.value("Damage", 1);
	myKnockbackStrength = someProperties.value("Knockback", 1000.0f);
	myKnockbackInterval = someProperties.value("KnockbackInterval", 0.1f);
}

void DamageVolume::Update(const float aDeltaTime, UpdateContext& /*anUpdateContext*/)
{
	if (myKnockbackTimer > 0.0f)
	{
		myKnockbackTimer -= aDeltaTime;
	}
}

void DamageVolume::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{}

void DamageVolume::TriggerStay(GameObject* aGameObject)
{
	if (aGameObject->GetTag() == GameObjectTag::Player)
	{
		Player* player = static_cast<Player*>(aGameObject);

		Damage(player);
	}
	else if (aGameObject->GetTag() == GameObjectTag::Enemy)
	{
		Enemy* enemy = static_cast<Enemy*>(aGameObject);
		enemy->TakeDamage(myDamage);

		if (myKnockbackTimer <= 0.0f)
		{
			enemy->ApplyForce((enemy->GetPosition() - GetPosition()).GetNormalized() * myKnockbackStrength);

			myKnockbackTimer = myKnockbackInterval;
		}
	}

}

void DamageVolume::Damage(Player* aPlayer)
{
	aPlayer->TakeDamage(myDamage);

	if (myKnockbackTimer <= 0.0f)
	{
		aPlayer->ApplyForce((aPlayer->GetPosition() - GetPosition()).GetNormalized() * myKnockbackStrength);

		myKnockbackTimer = myKnockbackInterval;
	}
}
