#pragma once

#include "Vector2.hpp"
#include <memory>
#include "TileType.h"

class Collider;

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;
class SpriteWrapper;

class GameObject
{
public:
	enum class eObjectType
	{
		Object,
		Player,
		Enemy,
		PlayButton,
		QuitButton,
		MousePointer,
		MuteSound,
		OptionsButton,
		BackButton,
		LevelSelect,
		Level1,
		Count
	};

	GameObject() = default;
	GameObject(Scene* aScene, const char* aSpritePath = nullptr);
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);
	virtual void OnCollision(GameObject* aGameObject);//TODO:create another OnCollision that uses Tiles
	virtual void OnCollision(TileType aTileType, CU::Vector2<float> anOffset);

	const Collider* GetCollider()const;
	eObjectType GetType();
	void SetType(eObjectType aType);
	inline Scene* GetScene() { return myScene; }

protected:

	Scene* myScene;
	eObjectType myType = eObjectType::Object;
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



