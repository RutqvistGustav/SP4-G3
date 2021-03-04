#include "stdafx.h"
#include "CollisionManager.h"

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
	for (int i = 0; i < myColliders.size(); i++)
	{
		for (int j = 0; j < myColliders.size(); j++)
		{
			if (i != j)
			{
				if (myColliders[i]->GetCollision(myColliders[j].get()))
				{
#ifdef _DEBUG
					myColliders[i]->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
					myColliders[j]->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
#endif // _DEBUG

				}
				else
				{
#ifdef _DEBUG
					myColliders[i]->setRenderColor(Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f));
					myColliders[j]->setRenderColor(Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f));
#endif // _DEBUG

				}
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* aCollider)
{
	myColliders.push_back(std::make_shared<Collider>(*aCollider));

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

