#pragma once

#include "JsonData.h"
#include "TriggerVolume.h"
#include "IJsonInitializable.h"
#include "PowerUpType.h"

class Player;
class SpriteSheetAnimation;

class Collectable :
	public TriggerVolume,
	public IJsonInitializable
{
public:

	Collectable(Scene* aScene, PowerUpType aPowerupType);
	virtual ~Collectable() override;

	virtual void InitWithJson(const JsonData& someJsonData) override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
	const PowerUpType GetType();

protected:

	using TriggerVolume::GameObject::Init;

	virtual void TriggerStay(GameObject* aGameObject) override;

	virtual bool CanCollect(Player* aPlayer);
	virtual void OnCollect(Player* aPlayer) = 0;

protected:
	PowerUpType myPowerupType;
	bool myIsCollected{};
	std::unique_ptr<SpriteSheetAnimation> myAnimation;

};
