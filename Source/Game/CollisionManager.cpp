#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Player.h"

#ifdef _DEBUG
#include <tga2d/sprite/sprite.h>
#endif // _DEBUG


CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	//std::map<int, int> myCollisionIndexes;
	for (int i = 0; i < myColliders.size(); ++i)
	{
		for (int j = 0; j < myColliders.size(); ++j)
		{


			if (myColliders[i]->GetCollision(myColliders[j].get()) && i != j)
			{
				/*Player* player = static_cast<Player*>((myColliders[i]->GetGameObject()).get());
				if (player)
				{
					player->OnCollision();
				}*/
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
		//int aNr = myColliders[i].use_count();
	}



	for (std::pair<int, int> pairs : myCollisionIndexes)
	{
		/*Player* player = dynamic_cast<Player*>((myColliders[pairs.first]->GetGameObject()).get());
		if (player)
		{
			player->StopMovement();
		}
		else
		{
			Player* player = dynamic_cast<Player*>((myColliders[pairs.second]->GetGameObject()).get());
			if (player)
			{
				player->StopMovement();
			}
		}*/

		myColliders[pairs.first]->GetGameObject()->OnCollision(myColliders[pairs.second]->GetGameObject());
		myColliders[pairs.second]->GetGameObject()->OnCollision(myColliders[pairs.first]->GetGameObject());

		
	}

}

void CollisionManager::AddCollider(std::shared_ptr<Collider> aCollider)
{
	myColliders.push_back(aCollider);

#ifdef _DEBUG
	myColliders.back().get()->myDebugSprite = new Tga2D::CSprite("debugCookie.png");
#endif // _DEBUG

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

