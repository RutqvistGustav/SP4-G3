#pragma once

#include "GenericGameMessageSubscriber.h"
#include "ParticleEffectType.h"

#include "Vector2.hpp"

struct SpawnParticleEffectMessageData
{
	CU::Vector2<float> myPosition;
	float myRotation{};

	ParticleEffectType myType;
};

using SpawnParticleEffectMessage = GenericGameMessageSubscriber<SpawnParticleEffectMessageData>;
