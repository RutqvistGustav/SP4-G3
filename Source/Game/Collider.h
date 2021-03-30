#pragma once

#include "ContactKey.h"
#include "CollisionLayer.h"

#include "AABB.h"
#include "Vector2.hpp"

#ifdef _DEBUG
namespace Tga2D
{
	class CSprite;
}
#include "SpriteWrapper.h"
#endif // _DEBUG

class SpriteWrapper;
class GameObject;
class TiledCollision;
class TiledTile;
class RenderQueue;
class RenderContext;

class Collider
{
public:
	
	Collider();
	Collider(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius = 100.f);
	Collider(GameObject* aGameObject, float aX, float aY, float aRadius = 100.f);
	virtual ~Collider();
	
	void Init(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius = 100.f);

	void SetPos(const CU::Vector2<float> aPos);

	bool GetCollision(const Collider* aCollider);

	GameObject* GetGameObject()const;

	void SetBoxSize(const CU::Vector2<float> aSize);
	CU::Vector2<float> GetBoxSize();

	const CU::Vector2<float> GetPosition()const;
	
	AABB GetAABB() const;

	const float GetWidth()const;
	const float GetHight()const;

	inline void SetIsTrigger(bool anIsTrigger) { myIsTrigger = anIsTrigger; }
	inline bool IsTrigger() const { return myIsTrigger; }

	inline void SetLayer(CollisionLayer::Layer aCollisionLayer) { myCollisionLayer = aCollisionLayer; }
	inline CollisionLayer::Layer GetLayer() const { return myCollisionLayer; }

#ifdef _DEBUG
	void InitDebug();

	void RenderDebug(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
	void setRenderColor(Tga2D::CColor aColor);
	std::shared_ptr<SpriteWrapper> myDebugSprite;
	bool myDoRender = true;
#endif // _DEBUG

private:

	friend class CollisionManager;
	friend class ContactManager;

	void AddContact(const ContactKey& aContactKey);
	void RemoveContact(const ContactKey& aContactKey);
	void ClearContacts();

private:

	CU::Vector2<float> myCheckOffset = CU::Vector2<float>(0.0f, 0.0f);

	CommonUtilities::Vector2<float> myPos;
	CU::Vector2<float> myDimentions;

	GameObject* myGameObject = nullptr;

	bool myIsTrigger{};

	CollisionLayer::Layer myCollisionLayer{ CollisionLayer::Default };
	std::vector<ContactKey> myContacts;

};

//TODO:Sync colliders with correct positon
//TODO:man kan fr�ga collision manager om collisions

