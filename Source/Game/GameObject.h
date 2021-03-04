#pragma once

#include "Vector2.hpp"

struct UpdateContext;
struct RenderContext;
class RenderQueue;

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);

protected:

	CU::Vector2<float> myPosition;
	// Wrapped Tga2D::CSprite;
	// Collider

};
