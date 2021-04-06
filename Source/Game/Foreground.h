#pragma once
#include "RenderQueue.h"
#include "RenderContext.h"
#include "UpdateContext.h"
#include "Vector2.hpp"

class ForegroundImage;

class Foreground
{
public:
	Foreground() = default;
	~Foreground() = default;

	void Init();

	void Update(const float aDeltaTime, const CU::Vector2<float> aPlayerPos, float aSpeed);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

private:
	float myX{};
	float myY{};

	CU::Vector2<int> myLastPlayerPos;
	CU::Vector2<int> myPlayerPos;

	std::shared_ptr<ForegroundImage> myForeground1;
	std::shared_ptr<ForegroundImage> myForeground2;
	std::shared_ptr<ForegroundImage> myForeground3;
	std::shared_ptr<ForegroundImage> myForeground4;

	std::vector<std::shared_ptr<ForegroundImage>> myForegrounds;

	void CreateForeground();
	void MoveForeground(const float aDeltaTime, const float aSpeed);
	void MoveX(std::shared_ptr<ForegroundImage> aImage, const float aDeltaTime);
	void MoveY(std::shared_ptr<ForegroundImage> aImage, const float aDeltaTime);
	void FollowPlayer(std::shared_ptr<ForegroundImage> aImage, const float aDeltaTime, const float aSpeed);
};