#include "stdafx.h"
#include "SpriteSheetParticleEffect.h"

#include "GlobalServiceProvider.h"

#include "GameLayer.h"

#include "SpriteWrapper.h"
#include "SpriteSheetAnimation.h"

SpriteSheetParticleEffect::SpriteSheetParticleEffect(Scene* aScene, const std::string& anAnimationPath) :
	GameObject(aScene)
{
	myAnimation = std::make_unique<SpriteSheetAnimation>(GetScene()->GetGlobalServiceProvider()->GetJsonManager(), anAnimationPath);
	myCollider.reset();
}

void SpriteSheetParticleEffect::Init()
{
	GameObject::Init();

	mySprite->SetLayer(GameLayer::ParticleEffects);

	myAnimation->SetState("default");
	myAnimation->SetIsLooping(false);

	myAnimation->ApplyToSprite(mySprite);
}

void SpriteSheetParticleEffect::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	GameObject::Update(aDeltaTime, anUpdateContext);

	myAnimation->Update(aDeltaTime);
	myAnimation->ApplyToSprite(mySprite);
	mySprite->SetSize(mySprite->GetSize() * myScale);

	if (myAnimation->HasEnded())
	{
		SetDeleteThisFrame();
	}
}

void SpriteSheetParticleEffect::SetRotation(float aRotation)
{
	mySprite->SetRotation(aRotation);
}

void SpriteSheetParticleEffect::SetScale(float aScale)
{
	myScale = aScale;
}
