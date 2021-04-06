#pragma once
#include "RenderQueue.h"
#include "RenderContext.h"
#include "UpdateContext.h"
#include <Vector2.hpp>

class SpriteWrapper;

class ForegroundImage
{
public:
	ForegroundImage(float aSpeed, CU::Vector2<float> aPos, const char* aSpritePath,
	bool aMoveLeft, bool aMoveUp);
	~ForegroundImage() = default;

	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	float GetSpeed() const;
	void SetSpeed(float aSpeed);
	
	CU::Vector2<float> GetPosition() const;
	void SetPosition(CU::Vector2<float> aPos);

	bool GetMoveLeft();
	bool GetMoveUp();
	void SetMoveLeft(bool aBool);
	void SetMoveUp(bool aBool);

private:
	float mySpeed;
	bool myMoveLeft;
	bool myMoveUp;

	CU::Vector2<float> myPosition;
	std::shared_ptr<SpriteWrapper> mySprite;
};

