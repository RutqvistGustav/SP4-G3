#pragma once
#include "Vector2.hpp"
#include <memory>

class Collider;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(const float aDeltaTime);
	virtual void Render(/*RenderQueue* aRenderQueue*/);
	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);

protected:
	CU::Vector2<float> myPosition;
	// Wrapped Tga2D::CSprite;

	Collider* myCollider;//will be changed to a shared pointer
	//std::shared_ptr<Collider> myCollider;
};

