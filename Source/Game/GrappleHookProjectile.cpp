#include "stdafx.h"
#include "GrappleHookProjectile.h"

#include "RenderQueue.h"
#include "RenderContext.h"
#include "RenderCommand.h"
#include "SpriteWrapper.h"

#include "CollisionManager.h"
#include <iostream>

GrappleHookProjectile::GrappleHookProjectile(Scene* aScene)
	: GameObject(aScene)
{
	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/Hook.dds");
}

void GrappleHookProjectile::Init(const JsonData& someJsonData)
{
	//myMaxDistance = someJsonData["maxDistance"];
	//myHookSpeed = someJsonData["hookSpeed"];
	//myContractSpeed = someJsonData["contractSpeed"];

	CollisionManager::GetInstance()->RemoveCollider(myCollider);
	myCollider.reset();
}

void GrappleHookProjectile::SetVariables(float aMaxDistance, float aHookSpeed, float aContractSpeed)
{
	myMaxDistance = aMaxDistance;
	myHookSpeed = aHookSpeed;
	myContractSpeed = aContractSpeed;

	CollisionManager::GetInstance()->RemoveCollider(myCollider);
	myCollider.reset();
}

void GrappleHookProjectile::Update(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition)
{
	if (myIsFiring == true)
	{
		Movement(aDeltaTime, aPlayerPosition);
	}
}

void GrappleHookProjectile::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (myIsFiring == true)
	{
		aRenderQueue->Queue(RenderCommand(mySprite));
	}
}

void GrappleHookProjectile::OnCollision(GameObject* aGrapplingPoint)
{
	//if (/*GameObject is valid target*/) // should not collide with Player
	//{
	//	myGrapplingPoint = aGrapplingPoint;
	//	myHasFoundValidTarget = true;
	//}
}

void GrappleHookProjectile::Movement(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition)
{


	
	//SetPosition();

	/*if (myDistanceTraveled.Length() < myMaxDistance)
	{
		
	}
	else 
	{
		ResetProjectile();
	}*/
}

bool GrappleHookProjectile::HasFoundGrapplingTarget()
{
	return myHasFoundValidTarget;
}

void GrappleHookProjectile::SpawnProjectile(const CU::Vector2<float> aDirection)
{
	myIsFiring = true;
	myDirection = aDirection;
}

void GrappleHookProjectile::ResetProjectile()
{
	myIsFiring = false;
	myHasFoundValidTarget = false;

	myDistanceTraveled = { 0.0f,0.0f };
	myGrapplingPoint = { 0.0f,0.0f };
}

CU::Vector2<float>& GrappleHookProjectile::GetGrapplingPoint()
{
	return myGrapplingPoint;
}
