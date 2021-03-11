#pragma once

#include "Vector2.hpp"

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

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);

	inline Scene* GetScene() { return myScene; }

protected:

	Scene* myScene;

	CU::Vector2<float> myPosition;
	std::shared_ptr<SpriteWrapper> mySprite;
	// Collider

};
