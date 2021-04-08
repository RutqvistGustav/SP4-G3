#include "stdafx.h"
#include "ParticleEffectManager.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"

#include "SpriteSheetParticleEffect.h"

ParticleEffectManager::ParticleEffectManager(Scene* aScene) :
	myScene(aScene)
{
	mySpriteSheetParticleAnimationPaths.insert({ ParticleEffectType::MuzzleFlash, "Animations/Particles/MuzzleFlash.json" });
	mySpriteSheetParticleAnimationPaths.insert({ ParticleEffectType::BloodSplatter, "Animations/Particles/BloodSplatter.json" });

	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::SpawnParticleEffect, this);
}

ParticleEffectManager::~ParticleEffectManager()
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::SpawnParticleEffect, this);
}

void ParticleEffectManager::SpawnParticleEffect(ParticleEffectType aType, const CU::Vector2<float>& aPosition, const float aRotation)
{
	const std::string& animationPath = mySpriteSheetParticleAnimationPaths.at(aType);
	std::shared_ptr<SpriteSheetParticleEffect> particleEffect = std::make_shared<SpriteSheetParticleEffect>(myScene, animationPath);
	particleEffect->Init();
	particleEffect->SetPosition(aPosition);
	particleEffect->SetRotation(aRotation);

	// TODO: If needed we could keep track of all active particle effects in our own vector

	myScene->AddGameObject(particleEffect);
}

GameMessageAction ParticleEffectManager::OnMessage(const GameMessage aMessage, const SpawnParticleEffectMessageData* someMessageData)
{
	assert(aMessage == GameMessage::SpawnParticleEffect);

	SpawnParticleEffect(someMessageData->myType, someMessageData->myPosition, someMessageData->myRotation);

	return GameMessageAction::Keep;
}
