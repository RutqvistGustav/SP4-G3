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
						myColliders[i]->GetGameObject()->OnCollision(myColliders[j]->GetGameObject().get());
						myColliders[j]->GetGameObject()->OnCollision(myColliders[i]->GetGameObject().get());

					}

					/*Player* player = static_cast<Player*>((myColliders[i]->GetGameObject()).get());
					if (player)
					{
						player->ResetOnGround();
					}*/
					//myColliders[i]->GetGameObject()->ResetOnGround();




					//not colliding
					/*myColliders[i]->myIsNotColliding = true;
					myColliders[j]->myIsNotColliding = true;
					myColliders[i]->myIsColliding = false;
					myColliders[j]->myIsColliding = false;*/



				}
			

		}
	}


	/*for (std::pair<int, int> nrsI : collidingPairs)
	{
		for (std::pair<int, int> nrsJ : collidingPairs)
		{
			if (nrsI.first == nrsJ.second
				&& nrsI.second == nrsJ.first)
			{
				collidingPairs.erase(nrsI.first);
			}
		}
	}*/

	/*for (int i = 0; i < myColliders.size(); i++)
	{

		for (int j = 0; j < collidingPairs.size(); j++)
		{*/



	for (std::pair<int, int> pairs : myCollisionIndexes)
	{
		/*if (collidingPairs[i] == j)
		{*/


		myColliders[pairs.first]->GetGameObject()->OnCollision(myColliders[pairs.second]->GetGameObject().get());
		myColliders[pairs.second]->GetGameObject()->OnCollision(myColliders[pairs.first]->GetGameObject().get());


//#ifdef _DEBUG
//		myColliders[pairs.first]->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
//		myColliders[pairs.second]->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
//#endif // _DEBUG

		//		if (myColliders[pairs.first]->myIsNotColliding == true && myColliders[pairs.first]->myIsColliding == false
		//			&& myColliders[pairs.second]->myIsNotColliding == true && myColliders[pairs.second]->myIsColliding == false)
		//		{
		//			myColliders[pairs.first]->myIsNotColliding = false;
		//			myColliders[pairs.second]->myIsNotColliding = false;
		//
		//
		//			myColliders[pairs.first]->GetGameObject()->OnFirstFrameCollision(myColliders[pairs.second]->GetGameObject().get());
		//			myColliders[pairs.second]->GetGameObject()->OnFirstFrameCollision(myColliders[pairs.first]->GetGameObject().get());
		//
		//			myColliders[pairs.first]->myIsColliding = true;
		//			myColliders[pairs.second]->myIsColliding = true;
		//
		//			
		//
		//
		//		}
		//		else if (myColliders[pairs.first]->myIsColliding && myColliders[pairs.second]->myIsColliding)
		//		{
		//			//all middle frames of collision
		//			myColliders[pairs.first]->GetGameObject()->OnCollision(myColliders[pairs.second]->GetGameObject().get());
		//			myColliders[pairs.second]->GetGameObject()->OnCollision(myColliders[pairs.first]->GetGameObject().get());
		//		}
		//		else if (myColliders[pairs.first]->myIsNotColliding == false && myColliders[pairs.first]->myIsColliding == true
		//			&& myColliders[pairs.second]->myIsNotColliding == false && myColliders[pairs.second]->myIsColliding == true)
		//		{
		//			//shuld be last frame of collision
		//
		//			myColliders[pairs.first]->myIsNotColliding = true;
		//			myColliders[pairs.second]->myIsNotColliding = true;
		//			myColliders[pairs.first]->myIsColliding = false;
		//			myColliders[pairs.second]->myIsColliding = false;
		//
		//#ifdef _DEBUG
		//			myColliders[pairs.first]->setRenderColor(Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f));
		//			myColliders[pairs.second]->setRenderColor(Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f));
		//#endif // _DEBUG
		//		}

				//}
				//else
				//{
				//	/*myColliders[i]->myIsNotColliding = true;
				//	myColliders[i]->myIsColliding = false;
				//	myColliders[j]->myIsNotColliding = true;
				//	myColliders[j]->myIsColliding = false;*/
				//}
	}
	//}
	//myColliders[i]->myIsAlreadyColliding = false;
//}


//	for (auto const& [key, val] : collidingPairs)
//	{
//		myColliders[key]->GetGameObject()->OnCollision();
//		myColliders[val]->GetGameObject()->OnCollision();
//#ifdef _DEBUG
//		myColliders[key]->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
//		myColliders[val]->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
//#endif // _DEBUG
//	}
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

