#pragma once

#include "AABB.h"
#include "CollisionItem.h"
#include "Collider.h"

#include "ContactManager.h"
#include "CollisionFilter.h"
#include "LockedSection.h"

#include <map>
#include <memory>
#include <set>

#include "IGameMessageSubscriber.h"

namespace Tga2D
{
	class CColor;
}

class TiledCollision;
class RenderQueue;
class GlobalServiceProvider;
struct RenderContext;

class CollisionManager : public IGameMessageSubscriber
{
public:

	CollisionManager() = default;
	CollisionManager(TiledCollision* aTiledCollision, GlobalServiceProvider* aGSP);
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;
	~CollisionManager();

	void Update();

	void IgnoreCollision(CollisionLayer::Layer aLayerA, CollisionLayer::Layer aLayerB);

	void PointTestNoAlloc(const CU::Vector2<float>& aPosition, CollisionLayer::Layer aLayerFilter, std::vector<CollisionItem>& aResult);

	void AddCollider(std::shared_ptr<Collider> aCollider);
	void RemoveCollider(std::shared_ptr<Collider> aCollider);
	
	virtual GameMessageAction OnMessage(const GameMessage aMessage, const void* someMessageData) override;
#ifndef _RETAIL
	
	inline const bool GetShowColliders() { return myShowColliders; }
	void InitDebug();
	bool myDoRender = true;
	void RenderDebug(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

#endif

private:
	std::vector<std::shared_ptr<Collider>> myColliders;
	
	CollisionFilter myCollisionFilter;

	ContactManager myContactManager;
	LockedSection myUpdateLock;
	
	TiledCollision* myTiledCollision{};

	GlobalServiceProvider* myGSP;

	bool myShowColliders;
};

//TODO:make colliders with fall-through
//TODO:man kan fr�ga collision manager om collisions
//TODO:make colliders be able to collide with multiple things
//TODO:auto remove Colliders
//TODO:caotiy time