#pragma once

#include "TriggerVolume.h"
#include "JsonData.h"
#include "IJsonInitializable.h"

class Player;
class SpriteSheetAnimation;

class DamageVolume :
	public TriggerVolume,
	public IJsonInitializable
{
public:

	DamageVolume(Scene* aScene);

	virtual void InitWithJson(const JsonData& someJsonData) override;

protected:

	using TriggerVolume::GameObject::Init;

	virtual void OnStay(GameObject* aGameObject) override;

	virtual void Damage(Player* aPlayer);

private:

	std::unique_ptr<SpriteSheetAnimation> myAnimation;

	// JSON data
	float myDamage{};
	float myKnockbackStrength{};

};
