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

	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

protected:

	using TriggerVolume::GameObject::Init;

	virtual void TriggerStay(GameObject* aGameObject) override;

private:

	std::unique_ptr<SpriteSheetAnimation> myAnimation;

	// JSON data
	int myDamage;

};
