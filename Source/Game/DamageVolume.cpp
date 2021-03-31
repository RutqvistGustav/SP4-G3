#include "stdafx.h"
#include "DamageVolume.h"

#include "GlobalServiceProvider.h"
#include "SpriteSheetAnimation.h"
#include "SpriteWrapper.h"

#include "RenderQueue.h"
#include "RenderCommand.h"

#include "Scene.h"
#include "Player.h"

DamageVolume::DamageVolume(Scene* aScene) :
	TriggerVolume(aScene, GameObjectTag::Player)
{}

void DamageVolume::InitWithJson(const JsonData & someProperties)
{
	Init();

	myDamage = someProperties.value("Damage", 1);
	myKnockbackStrength = someProperties.value("Knockback", 1000.0f);
	myKnockbackInterval = someProperties.value("KnockbackInterval", 0.1f);

	const std::string animationPath = someProperties.value("Animation", "");
	if (animationPath.empty())
	{
		assert(!animationPath.empty() && "No animation path in properties");

		return;
	}

	myAnimation = std::make_unique<SpriteSheetAnimation>(GetScene()->GetGlobalServiceProvider()->GetJsonManager(), animationPath);

	myAnimation->SetState("default");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerSize(mySprite->GetSize());
}

void DamageVolume::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myKnockbackTimer > 0.0f)
	{
		myKnockbackTimer -= aDeltaTime;
	}

	myAnimation->Update(aDeltaTime);
	myAnimation->ApplyToSprite(mySprite);

	mySprite->SetSize(GetTriggerSize());
}

void DamageVolume::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(mySprite));
}

void DamageVolume::TriggerStay(GameObject* aGameObject)
{
	Player* player = static_cast<Player*>(aGameObject);

	Damage(player);
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
