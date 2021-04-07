#pragma once

#include "ContactKey.h"
#include "CollisionLayer.h"

#include "AABB.h"
#include "Vector2.hpp"

#ifdef _DEBUG

#include "SpriteWrapper.h"

#endif // _DEBUG

#include <any>

class GameObject;
class SpriteWrapper;
class TiledCollision;
class TiledTile;
class RenderQueue;
struct RenderContext;
class CollisionListener;

class Collider
{
public:
	
	Collider();
	Collider(const CU::Vector2<float>& aPos, const CU::Vector2<float>& aSize);
	virtual ~Collider();

	void Init(const CU::Vector2<float>& aPos, const CU::Vector2<float>& aSize);

	void SetBoxSize(const CU::Vector2<float> aSize);
	CU::Vector2<float> GetBoxSize();

	void SetPosition(const CU::Vector2<float> aPos);
	const CU::Vector2<float> GetPosition()const;
	
	AABB GetAABB() const;

	const float GetWidth()const;
	const float GetHight()const;

	inline void SetGameObject(GameObject* aGameObject) { myGameObject = aGameObject; }
	inline GameObject* GetGameObject() const { return myGameObject; }

	inline void SetCollisionListener(CollisionListener* aListener) { myCollisionListener = aListener; }
	inline CollisionListener* GetCollisionListener() const { return myCollisionListener; }

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

	bool GetCollision(const Collider* aCollider);

	void AddContact(const ContactKey& aContactKey);
	void RemoveContact(const ContactKey& aContactKey);
	void ClearContacts();

private:

	CommonUtilities::Vector2<float> myPos;
	CU::Vector2<float> mySize;

	CollisionListener* myCollisionListener{};
	GameObject* myGameObject{};

	bool myIsTrigger{};

	CollisionLayer::Layer myCollisionLayer{ CollisionLayer::Default };
	std::vector<ContactKey> myContacts;

};
