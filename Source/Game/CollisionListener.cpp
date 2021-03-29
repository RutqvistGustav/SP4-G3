#include "stdafx.h"
#include "CollisionListener.h"
#include <memory>
#include "Scene.h"
#include <any>

CollisionListener::CollisionListener(Scene* aScene)
	: myColliderL(std::make_shared<Collider>())
	, myLScene(aScene)
{

}

CollisionListener::~CollisionListener()
{
	if (myColliderL != nullptr)
	{
		myLScene->GetCollisionManager()->RemoveCollider(myColliderL);
	}
	myLScene = nullptr;
}

void CollisionListener::Init(Scene* aScene)
{
	assert(aScene != nullptr && "Trying to create a CollisionListener without a scene.");
	myLScene = aScene;
	myColliderL->Init(this, CU::Vector2<float>());
	aScene->GetCollisionManager()->AddCollider(myColliderL);
}

void CollisionListener::OnCollision(std::any aGameObject)
{
	

}

void CollisionListener::OnCollision(TileType aTileType, CU::Vector2<float> anOffset)
{
	
}
