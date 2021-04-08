#pragma once

#include "GenericGameMessageSubscriber.h"
#include "ParticleEffectType.h"

#include "Vector2.hpp"

struct SpawnParticleEffectMessageData
{
	CU::Vector2<float> myPosition;
	float myRotation{};
	float myScale{ 1.0f };
	bool myFlip{};

	ParticleEffectType myType;
};

using SpawnParticleEffectMessage = GenericGameMessageSubscriber<SpawnParticleEffectMessageData>;
