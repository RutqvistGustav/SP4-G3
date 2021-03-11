#pragma once
#include "Vector2.hpp"
#include <memory>

class Collider;

class GameObject
{
public:
	GameObject(float aX = 0.f, float aY = 0.f);
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(const float aDeltaTime);
	virtual void Render(/*RenderQueue* aRenderQueue*/);
	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);
	virtual void OnCollision(const GameObject* aGameObject);
	virtual void OnFirstFrameCollision(const GameObject* aGameObject);

	void ResetOnGround();//probably temorary

protected:

	CU::Vector2<float> myPosition;
	CU::Vector2<float> myPositionLastFrame;
	// Wrapped Tga2D::CSprite;

	std::shared_ptr<Collider> myCollider;


	CU::Vector2<float> myVelocity; //temorary variable
	bool myIsPlayer = false; //temorary variable
};

