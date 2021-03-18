#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Player.h"
#include "TiledCollision.h"
#include "TiledTile.h"

#ifdef _DEBUG
#include <tga2d/sprite/sprite.h>
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

		//CheckTileCollision(i);

		//TileType* tileToCheck = myColliders[i]->GetCollision(myTiledCollision);

		if (myColliders[i]->GetCollision(myTiledCollision) != nullptr)
		{
			myColliders[i]->myCollisionStage = Collider::eCollisionStage::MiddleFrames;
			myColliders[i]->myGameObject->OnCollision(myColliders[i]->GetCollision(myTiledCollision)->GetType());
		}
		else if(myColliders[i]->myCollisionStage == Collider::eCollisionStage::MiddleFrames)
		{
			myColliders[i]->myCollisionStage = Collider::eCollisionStage::NotColliding;
			myColliders[i]->myGameObject->OnCollision(TileType::None);
		}

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
		myColliders[pairs.first]->GetGameObject()->OnCollision(myColliders[pairs.second]->GetGameObject());
		myColliders[pairs.second]->GetGameObject()->OnCollision(myColliders[pairs.first]->GetGameObject());
	}
	for (std::pair<int, CU::Vector2<float>> pairs : myTileCollisionIndexes)
	{
		myColliders[pairs.first]->GetGameObject()->SetPosition(pairs.second);
		myColliders[pairs.first]->myCollisionStage = Collider::eCollisionStage::NotColliding;
		//myTileCollisionIndexes.erase(pairs.first);

		//myColliders[pairs.first]->GetGameObject()->OnCollision(myColliders[j]->GetGameObject());
	}

}

void CollisionManager::AddCollider(std::shared_ptr<Collider> aCollider)
{
	myColliders.push_back(aCollider);

#ifdef _DEBUG
	myColliders.back().get()->myDebugSprite = new Tga2D::CSprite("debugCookie.png");
#endif // _DEBUG

}

void CollisionManager::RemoveCollider(std::shared_ptr<Collider> aCollider)
{
	for (int i = 0; i < myColliders.size(); ++i)
	{
		if (aCollider == myColliders[i])
		{
			myColliders.erase(myColliders.begin() + i);
		}
	}
}

void CollisionManager::CheckTileCollision(const int& anIndex)
{
	const TiledTile* tileToCheck = myTiledCollision->GetTileAt(myColliders[anIndex]->GetPosition() + CU::Vector2<float>(0.f, myColliders[anIndex]->GetWidth() * 0.5f));
	if (tileToCheck != nullptr)
	{
		if (tileToCheck->GetType() == TileType::None)
		{
			myTileCollisionIndexes[anIndex] = myColliders[anIndex]->GetPosition() - CU::Vector2<float>(0.f, myColliders[anIndex]->GetWidth() * 0.5f);
		}
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
void CollisionManager::RenderDebug()
{
	for (int i = 0; i < myColliders.size(); ++i)
	{
		myColliders[i]->RenderDebug();
	}
}
#endif // _DEBUG

