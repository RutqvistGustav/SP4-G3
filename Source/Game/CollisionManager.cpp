#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Player.h"
#include "TiledCollision.h"
#include "TiledTile.h"

#ifdef _DEBUG

#include "RenderQueue.h"
#include "RenderContext.h"
#include "InputInterface.h"
#include "InputManager.h"

#endif // _DEBUG

#include <cassert>
#include <queue>

CollisionManager::CollisionManager(TiledCollision* aTiledCollision)
	: myTiledCollision(aTiledCollision)
{
	assert(aTiledCollision != nullptr && "CollisionManager is being created without a TiledCollision.");
}

CollisionManager::~CollisionManager() = default;

void CollisionManager::Update()
{
	assert(!myUpdateLock.IsLocked());

	myUpdateLock.Lock();

	for (int i = 0; i < myColliders.size() - 1; ++i)
	{
		for (int j = i + 1; j < myColliders.size(); ++j)
		{
			Collider* colliderA = myColliders[i].get();
			Collider* colliderB = myColliders[j].get();

			if (myCollisionFilter.IsIgnored(CollisionFilterKey(colliderA->GetLayer(), colliderB->GetLayer())))
			{
				continue;
			}

			const ContactKey contactKey{ colliderA, colliderB };
			const bool wasColliding = myContactManager.HasContact(contactKey);
			const bool isColliding = colliderA->GetCollision(colliderB);

			if (!wasColliding && isColliding)
			{
				myContactManager.AddContact(contactKey);

				ContactManager::SendOnEnter(colliderA, colliderB);
			}
			else if (wasColliding && !isColliding)
			{
				myContactManager.RemoveContact(contactKey);

				ContactManager::SendOnExit(colliderA, colliderB);
			}
			else if (isColliding)
			{
				ContactManager::SendOnStay(colliderA, colliderB);
			}
		}
	}

	myUpdateLock.Unlock();
}

void CollisionManager::IgnoreCollision(CollisionLayer::Layer aLayerA, CollisionLayer::Layer aLayerB)
{
	myCollisionFilter.AddFilter(CollisionFilterKey(aLayerA, aLayerB));
}

void CollisionManager::PointTestNoAlloc(const CU::Vector2<float>& aPosition, CollisionLayer::Layer aLayerFilter, std::vector<CollisionItem>& aResult)
{
	if (aResult.size() == aResult.capacity())
	{
		return;
	}

	if (myTiledCollision != nullptr)
	{
		const TiledTile* aTile = myTiledCollision->GetTileAt(aPosition);
		if (aTile != nullptr && aLayerFilter == CollisionLayer::MapSolid)
		{
			const CU::Vector2<float> alignedSize = { 64.0f, 64.0f };
			const CU::Vector2<float> alignedPosition = { std::floorf(aPosition.x / alignedSize.x) * alignedSize.x, std::floorf(aPosition.y / alignedSize.y) * alignedSize.y };

			const auto& collisionBoxes = aTile->GetCollisionBoxes();

			CollisionItem::Type type;
			if (aTile->GetType() == TileType::HalfSolid)
			{
				type = CollisionItem::Type::HalfTile;
			}
			else
			{
				type = CollisionItem::Type::Tile;
			}

			if (collisionBoxes.empty())
			{
				//TODO: remove
				aResult.push_back({ type, AABB(alignedPosition, alignedPosition + alignedSize) });
			}
			else
			{
				for (const auto& collisionBox : collisionBoxes)
				{
					const CU::Vector2<float> position = alignedPosition + CU::Vector2<float>(collisionBox.myX, collisionBox.myY);
					const CU::Vector2<float> size = { collisionBox.myWidth, collisionBox.myHeight };

					AABB boxAABB = AABB(position, position + size);

					if (boxAABB.Contains(aPosition))
					{
						aResult.push_back({ type, boxAABB });

						if (aResult.size() >= aResult.capacity())
						{
							break;
						}
					}
				}
			}
		}
	}

	if (aResult.size() >= aResult.capacity())
	{
		return;
	}

	if (aLayerFilter != CollisionLayer::MapSolid)
	{
		assert(!myUpdateLock.IsLocked());
		myUpdateLock.Lock();

		for (int i = 0; i < myColliders.size() && aResult.size() < aResult.capacity(); ++i)
		{
			Collider* collider = myColliders[i].get();

			if (
				!myCollisionFilter.IsIgnored(CollisionFilterKey(collider->GetLayer(), aLayerFilter)) &&
				collider->GetAABB().Contains(aPosition))
			{
				aResult.push_back({ CollisionItem::Type::Collider, collider->GetAABB(), collider->GetGameObject() });
			}
		}

		myUpdateLock.Unlock();
	}
}

void CollisionManager::AddCollider(std::shared_ptr<Collider> aCollider)
{
	if (myUpdateLock.IsLocked())
	{
		// TODO: Add to insert queue if this is called, for now it will not be implemented

		ERROR_PRINT("CollisionManager::AddCollider called inside collision update loop => Ignoring");

		return;
	}

	myColliders.push_back(aCollider);

#ifdef _DEBUG

	myColliders.back().get()->myDebugSprite = std::make_shared<SpriteWrapper>("debugCookieSquare.png");

#endif // _DEBUG
}

void CollisionManager::RemoveCollider(std::shared_ptr<Collider> aCollider)
{
	if (myUpdateLock.IsLocked())
	{
		// TODO: Add to removal queue if this is called, for now it will not be implemented

		ERROR_PRINT("CollisionManager::RemoveCollider called inside collision update loop => Ignoring");

		return;
	}

	auto it = std::find(myColliders.begin(), myColliders.end(), aCollider);
	if (it != myColliders.end())
	{
		std::swap(myColliders.back(), *it);
		myColliders.pop_back();

		myContactManager.DestroyContacts(aCollider.get());
	}
}

#ifdef _DEBUG
void CollisionManager::InitDebug()
{
	for (int i = 0; i < myColliders.size(); ++i)
	{
		myColliders[i]->InitDebug();
	}
}
void CollisionManager::RenderDebug(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (int i = 0; i < myColliders.size() && myDoRender; ++i)
	{
		myColliders[i]->RenderDebug(aRenderQueue, aRenderContext);
	}
}
#endif // _DEBUG
