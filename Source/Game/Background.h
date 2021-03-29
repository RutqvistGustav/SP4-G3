#pragma once
#include "RenderQueue.h"
#include "RenderContext.h"
#include "UpdateContext.h"

class SpriteWrapper;

class Background
{
public:
	Background() = default;
	~Background() = default;

	void Init();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

private:
	float myX;
	float myY;

	std::shared_ptr<SpriteWrapper> myForeground1;
	std::shared_ptr<SpriteWrapper> myForeground2;
	std::shared_ptr<SpriteWrapper> myForeground3;
	std::shared_ptr<SpriteWrapper> myForeground4;

	std::vector<std::shared_ptr<SpriteWrapper>> myForegrounds;

	void CreateForeground();
	void MoveForeground(const float aDeltaTime);
};

