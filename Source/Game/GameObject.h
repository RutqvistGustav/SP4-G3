#pragma once
#include "Vector2.hpp"
#include <memory>

class Collider;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject();

	virtual void Update(const float aDeltaTime);
	virtual void Render(/*RenderQueue* aRenderQueue*/);
	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);

protected:
	CU::Vector2<float> myPosition;
	// Wrapped Tga2D::CSprite;
	std::shared_ptr<Collider> myCollider;
};

