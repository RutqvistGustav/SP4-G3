#pragma once

#include "GameObject.h"

#include <functional>

namespace CommonUtilities
{
	class Input;
}

class SpriteWrapper;
class InputInterface;

class MousePointer :
	public GameObject
{
public:

	using ClickCallback = std::function<void(GameObject* aTarget)>;

	MousePointer(Scene* aScene);
	virtual ~MousePointer() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	void SetClickCallback(const ClickCallback& aClickCallback);

	bool IsMouseDown();
	bool IsMouseHeld();

	void ReadingMouseCoordinates(float aDeltaTime, CommonUtilities::Input* aInput);
	void ReadingLMBInput(InputInterface* aInputInterface);

private:

	virtual void OnStay(const CollisionInfo& someCollisionInfo) override;

private:

	ClickCallback myClickCallback;

	bool myMouseDown{};
	bool myMouseHeld{};

};