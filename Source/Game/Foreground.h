#pragma once
#include "RenderQueue.h"
#include "RenderContext.h"
#include "UpdateContext.h"

class SpriteWrapper;

class Foreground
{
public:
	Foreground() = default;
	~Foreground() = default;

	void Init();

	void Update(const float aDeltaTime);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

private:
	float myX;
	float myY;
	bool myMoveLeft;
	bool myMoveUp;

	std::shared_ptr<SpriteWrapper> myForeground1;
	std::shared_ptr<SpriteWrapper> myForeground2;
	std::shared_ptr<SpriteWrapper> myForeground3;
	std::shared_ptr<SpriteWrapper> myForeground4;

	std::vector<std::shared_ptr<SpriteWrapper>> myForegrounds;

	void CreateForeground();
	void MoveForeground(const float aDeltaTime);
	void MoveX(float& aPosX, const float aDeltaTime);
	void MoveY(float& aPosY, const float aDeltaTime);
};