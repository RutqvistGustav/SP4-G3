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

namespace Tga2D
{
	class CColor;
}

class TiledCollision;
class RenderQueue;
class RenderContext;

class CollisionManager
{
public:

	CollisionManager() = default;
	CollisionManager(TiledCollision* aTiledCollision);
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;
	~CollisionManager();

	void Update();

	void IgnoreCollision(CollisionLayer::Layer aLayerA, CollisionLayer::Layer aLayerB);

	void PointTestNoAlloc(const CU::Vector2<float>& aPosition, CollisionLayer::Layer aLayerFilter, std::vector<CollisionItem>& aResult);

	void AddCollider(std::shared_ptr<Collider> aCollider);
	void RemoveCollider(std::shared_ptr<Collider> aCollider);
	
#ifdef _DEBUG
	
	void InitDebug();
	void RenderDebug(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
	bool myDoRender = true;

#endif // _DEBUG

private:

	std::vector<std::shared_ptr<Collider>> myColliders;
	
	CollisionFilter myCollisionFilter;

	ContactManager myContactManager;
	LockedSection myUpdateLock;
	
	TiledCollision* myTiledCollision;

};

//TODO:make colliders with fall-through
//TODO:man kan fråga collision manager om collisions
//TODO:make colliders be able to collide with multiple things
//TODO:auto remove Colliders
//TODO:caotiy time