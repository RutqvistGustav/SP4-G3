#pragma once

#include <memory>
#include "Collectable.h"
#include "PowerUpType.h"

class DialogueBox;

class Key : public Collectable
{
public:
	Key(Scene* aScene, PowerUpType aPowerupType);
	virtual void InitWithJson(const JsonData& someProperties) override;
	virtual void OnCollect(Player* aPlayer) override;
	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
	virtual void TriggerStay(GameObject* aGameObject) override;

private:
	std::unique_ptr<DialogueBox> myDialogBox;
};
