#pragma once

#include "Vector2.hpp"
#include <memory>

class Collider;

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;

class GameObject
{
public:

	GameObject(float aX = 0.f, float aY = 0.f);
	GameObject(Scene* aScene);
	virtual ~GameObject();

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);
	virtual void OnCollision(const GameObject* aGameObject);
	virtual void OnFirstFrameCollision(const GameObject* aGameObject);

	void ResetOnGround();//probably temorary

	inline Scene* GetScene() { return myScene; }

protected:


	Scene* myScene;

	CU::Vector2<float> myPosition;
	CU::Vector2<float> myPositionLastFrame;
	// Wrapped Tga2D::CSprite;

	std::shared_ptr<Collider> myCollider;


	CU::Vector2<float> myVelocity; //temorary variable
	bool myIsPlayer = false; //temorary variable
};


};
