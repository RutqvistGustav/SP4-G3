#pragma once

#include "Scene.h"

class MenuScene :
	public Scene
{
public:
	MenuScene();
	virtual ~MenuScene() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

protected:
	void AddInterfaceElement(std::shared_ptr<GameObject> anElement);

protected:

	std::unique_ptr<MousePointer> myMousePointer;

};
