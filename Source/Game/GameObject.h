#pragma once

#include "GameObjectTag.h"
#include "Vector2.hpp"

#include <memory>
#include "TileType.h"

#ifdef _DEBUG
#include "tga2d/math/vector2.h"
#include "tga2d/sprite/sprite.h"
#endif // _DEBUG

class Collider;

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;
class SpriteWrapper;
class GlobalServiceProvider;

class GameObject
{
public:

	GameObject(Scene* aScene, const char* aSpritePath = nullptr);
	GameObject(Scene* aScene, GameObjectTag aTag, const char* aSpritePath = nullptr);

	virtual ~GameObject();

	virtual void Init();
	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);
	virtual void OnCollision(GameObject* aGameObject);//TODO:create another OnCollision that uses Tiles
	virtual void OnCollision(TileType aTileType, CU::Vector2<float> anOffset);

	const Collider* GetCollider()const;
	void RemoveCollider();

	GlobalServiceProvider* GetGlobalServiceProvider();

	inline Scene* GetScene() { return myScene; }

	inline const GameObjectTag GetTag() const { return myTag; }

	bool GetDeleteThisFrame();
	void SetDeleteThisFrame();

protected:

	inline void SetTag(const GameObjectTag aTag) { myTag = aTag; }

protected:

	Scene* myScene;
	bool myDeleteThisFrame = false;

	GameObjectTag myTag{ GameObjectTag::Default };

	CU::Vector2<float> myPosition;
	CU::Vector2<float> myPositionLastFrame;
	std::shared_ptr<SpriteWrapper> mySprite;

	std::shared_ptr<Collider> myCollider;
};



