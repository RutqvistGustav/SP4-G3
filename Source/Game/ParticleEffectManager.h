#pragma once

#include "SpawnParticleEffectMessage.h"

class Scene;

class ParticleEffectManager :
	public SpawnParticleEffectMessage
{
public:

	ParticleEffectManager(Scene* aScene);
	~ParticleEffectManager();

	void SpawnParticleEffect(ParticleEffectType aType, const CU::Vector2<float>& aPosition, const float aRotation);

private:

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const SpawnParticleEffectMessageData* someMessageData) override;

private:

	Scene* myScene;

	std::unordered_map<ParticleEffectType, std::string> mySpriteSheetParticleAnimationPaths;

};
