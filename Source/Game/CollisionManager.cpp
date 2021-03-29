#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Player.h"
#include "TiledCollision.h"
#include "TiledTile.h"
#include <queue>

#ifdef _DEBUG
//#include <tga2d/sprite/sprite.h>
#include "RenderQueue.h"
#include "RenderContext.h"
#include "InputInterface.h"
#include "InputManager.h"
#endif // _DEBUG


CollisionManager::CollisionManager(TiledCollision* aTiledCollision)
	: myTiledCollision(aTiledCollision)
{

	assert(aTiledCollision != nullptr && "CollisionManager is being created without a TiledCollision.");
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	for (int i = 0; i < myColliders.size(); ++i)
	{




		CU::Vector2<float> vecDown = CU::Vector2<float>(0.0f, 1.0f);
		//CU::Vector2<float> vecUp = CU::Vector2<float>(0.f, -1.0f);
		CheckTileCollision(i, vecDown);
		//CheckTileCollision(i, vecUp);
		//CheckTileCollision(i, vecRight);
		//CheckTileCollision(i, vecLeft);


		for (int j = 0; j < myColliders.size(); ++j)
		{


			if (myColliders[i]->GetCollision(myColliders[j].get()) && i != j)
			{

				bool IsDuplicate = false;
				for (std::pair<int, int> nrs : myCollisionIndexes)
				{
					if ((nrs.first == i && nrs.second == j) ||
						(nrs.first == j && nrs.second == i))
					{
						IsDuplicate = true;
					}
				}
				if (!IsDuplicate)
				{
					myCollisionIndexes[i] = j;
					myColliders[i]->myCollisionStage = Collider::eCollisionStage::MiddleFrames;
					myColliders[j]->myCollisionStage = Collider::eCollisionStage::MiddleFrames;
				}


			}
			else if (i != j)
			{

				if (myCollisionIndexes.find(i) != myCollisionIndexes.end() && myCollisionIndexes[i] == j)
				{
					myCollisionIndexes.erase(i);
					myCollisionIndexes.erase(j);
					myColliders[i]->myCollisionStage = Collider::eCollisionStage::NotColliding;
					myColliders[j]->myCollisionStage = Collider::eCollisionStage::NotColliding;
					/*myColliders[i]->GetGameObject()->OnCollision(myColliders[j]->GetGameObject().get());
					myColliders[j]->GetGameObject()->OnCollision(myColliders[i]->GetGameObject().get());*/
					myColliders[i]->GetGameObject()->OnCollision(myColliders[j]->GetGameObject());
					myColliders[j]->GetGameObject()->OnCollision(myColliders[i]->GetGameObject());

				}
			}
		}
	}


	for (std::pair<int, int> pairs : myCollisionIndexes)
	{
		if (pairs.second < myColliders.size())
		{
			myColliders[pairs.first]->myCollisionStage = Collider::eCollisionStage::MiddleFrames;
			myColliders[pairs.second]->myCollisionStage = Collider::eCollisionStage::MiddleFrames;
			myColliders[pairs.first]->GetGameObject()->OnCollision(myColliders[pairs.second]->GetGameObject());
			myColliders[pairs.second]->GetGameObject()->OnCollision(myColliders[pairs.first]->GetGameObject());
		}
	}

}

void CollisionManager::AddCollider(std::shared_ptr<Collider> aCollider)
{
	myColliders.push_back(aCollider);

#ifdef _DEBUG
	myColliders.back().get()->myDebugSprite = std::make_shared<SpriteWrapper>("debugCookieSquare.png");
	//myColliders.back().get()->myDebugSprite = new Tga2D::CSprite("debugCookieSquare.png");
#endif // _DEBUG

}

void CollisionManager::RemoveCollider(std::shared_ptr<Collider> aCollider)
{
	std::queue<int> queue;
	for (int i = 0; i < myColliders.size(); ++i)
	{
		if (aCollider == myColliders[i])
		{
			myColliders.erase(myColliders.begin() + i);

			for (std::pair<int, int> pairs : myCollisionIndexes)
			{
				if (pairs.first == i || pairs.second == i)
				{
					queue.push(pairs.first);
				}
			}

			while (!queue.empty())
			{
				myCollisionIndexes.erase(queue.front());
				queue.pop();
			}
		}
	}
}

void CollisionManager::CheckTileCollision(const int& anIndex, CU::Vector2<float> anOffset)
{
	auto colliderPtr = myColliders[anIndex]->GetCollision(myTiledCollision, anOffset);

	if (colliderPtr != nullptr)
	{
		if (colliderPtr->GetCollisionBoxes().empty())
		{
			myColliders[anIndex]->myCollisionStage = Collider::eCollisionStage::MiddleFrames;
			myColliders[anIndex]->myGameObject->OnCollision(colliderPtr->GetType(), anOffset);
			myColliders[anIndex]->myCheckOffset = CU::Vector2<float>();
		}
		else if (anOffset.y > 0.f) //check bottom
		{
			myColliders[anIndex]->myCheckOffset.y = -colliderPtr->GetCollisionBoxes()[0].myY;
			myColliders[anIndex]->myGameObject->OnCollision(colliderPtr->GetType(), anOffset + myColliders[anIndex]->myCheckOffset);
		}
		
	}
	else if (myColliders[anIndex]->myCollisionStage == Collider::eCollisionStage::MiddleFrames)
	{
		myColliders[anIndex]->myCollisionStage = Collider::eCollisionStage::NotColliding;
		myColliders[anIndex]->myGameObject->OnCollision(TileType::None, CU::Vector2<float>());
	}


	/*const TiledTile* tileToCheck = myTiledCollision->GetTileAt(myColliders[anIndex]->GetPosition() + CU::Vector2<float>(0.f, myColliders[anIndex]->GetWidth() * 0.5f));
	if (tileToCheck != nullptr)
	{
		if (tileToCheck->GetType() == TileType::None)
		{
			myTileCollisionIndexes[anIndex] = myColliders[anIndex]->GetPosition() - CU::Vector2<float>(0.f, myColliders[anIndex]->GetWidth() * 0.5f);
		}
	}*/
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

