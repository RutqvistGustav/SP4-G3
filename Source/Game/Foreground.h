#pragma once
#include "RenderQueue.h"
#include "RenderContext.h"
#include "UpdateContext.h"

class ForegroundImage;

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

	std::shared_ptr<ForegroundImage> myForeground1;
	std::shared_ptr<ForegroundImage> myForeground2;
	std::shared_ptr<ForegroundImage> myForeground3;
	std::shared_ptr<ForegroundImage> myForeground4;

	std::vector<std::shared_ptr<ForegroundImage>> myForegrounds;

	void CreateForeground();
	void MoveForeground(const float aDeltaTime);
	void MoveX(std::shared_ptr<ForegroundImage> aImage, float aDeltaTime);
	void MoveY(std::shared_ptr<ForegroundImage> aImage, float aDeltaTime);
};