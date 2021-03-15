#pragma once

#include "Vector2.hpp"
#include <memory>

class Collider;

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;
class SpriteWrapper;

class GameObject
{
public:


	GameObject(Scene* aScene, const char* aSpritePath = nullptr);
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);
	virtual void OnCollision(GameObject* aGameObject);

	inline Scene* GetScene() { return myScene; }

protected:


	Scene* myScene;

	CU::Vector2<float> myPosition;
	CU::Vector2<float> myVel;
	std::shared_ptr<SpriteWrapper> mySprite;

	std::shared_ptr<Collider> myCollider;


	bool myIsPlayer = false; //temorary variable
	float myGravity;//temorary variable
};



