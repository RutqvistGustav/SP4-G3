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

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

protected:

	using TriggerVolume::GameObject::Init;

	virtual void TriggerStay(GameObject* aGameObject) override;

	virtual void Damage(Player* aPlayer);

private:

	std::unique_ptr<SpriteSheetAnimation> myAnimation;

	// JSON data
	float myDamage{};
	float myKnockbackStrength{};

};
