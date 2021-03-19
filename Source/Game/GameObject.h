#pragma once

#include "GameObjectTag.h"
#include "Vector2.hpp"

#include <memory>

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
		Count
	};

	GameObject() = default;

	GameObject(Scene* aScene, const char* aSpritePath = nullptr);
	GameObject(Scene* aScene, GameObjectTag aTag, const char* aSpritePath = nullptr);

	virtual ~GameObject();

	virtual void Init();
	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	virtual void OnCollision(GameObject* aGameObject);

	const CU::Vector2<float>& GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);

	const Collider* GetCollider()const;
	eObjectType GetType();
	void SetType(eObjectType aType);

	GlobalServiceProvider* GetGlobalServiceProvider();

	inline Scene* GetScene() { return myScene; }

	inline const GameObjectTag GetTag() const { return myTag; }

protected:

	inline void SetTag(const GameObjectTag aTag) { myTag = aTag; }

protected:

	Scene* myScene;
	eObjectType myType = eObjectType::Object;

	GameObjectTag myTag{ GameObjectTag::Default };

	CU::Vector2<float> myPosition;
	CU::Vector2<float> myPositionLastFrame;
	std::shared_ptr<SpriteWrapper> mySprite;

	std::shared_ptr<Collider> myCollider;
};



