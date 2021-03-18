#include "stdafx.h"
#include "GrappleHookProjectile.h"

#include "RenderQueue.h"
#include "RenderContext.h"
#include "RenderCommand.h"
#include "SpriteWrapper.h"

#include "CollisionManager.h"
#include <iostream>

GrappleHookProjectile::GrappleHookProjectile(Scene* aScene, IWeaponHolder* aWeaponHolder)
	: GameObject(aScene)
{
	myWeaponHolder = aWeaponHolder;
	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/Hook.dds");
}

void GrappleHookProjectile::Init(const JsonData& someJsonData)
{
	//myMaxDistance = someJsonData["maxDistance"];
	//myHookSpeed = someJsonData["hookSpeed"];
	//myContractSpeed = someJsonData["contractSpeed"];

}

void GrappleHookProjectile::SetVariables(float aMaxDistance, float aHookSpeed, float aContractSpeed)
{
	myMaxDistance = aMaxDistance;
	myHookSpeed = aHookSpeed;
	myContractSpeed = aContractSpeed;

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
	if (aGrapplingPoint->GetTag() == GameObjectTag::Default && myHasSentPosition == false) // should not collide with Player
	{
		myWeaponHolder->OnGrappleHit(GetPosition());
		myHasSentPosition = true;
	}
}

void GrappleHookProjectile::Movement(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition)
{
	if (myDistanceTraveled < myMaxDistance)
	{
		myDistanceTraveled += myHookSpeed * aDeltaTime;
		SetPosition(aPlayerPosition + myDistanceTraveled * myDirection);
	}
	else 
	{
		ResetProjectile();
	}
}



void GrappleHookProjectile::SpawnProjectile(const CU::Vector2<float> aDirection)
{
	myIsFiring = true;
	myDirection = aDirection;
}

void GrappleHookProjectile::ResetProjectile()
{
	myHasSentPosition = false;
	myIsFiring = false;
	myHasFoundValidTarget = false;

	myDistanceTraveled = 0;
	myGrapplingPoint = { 0.0f,0.0f };
}

bool GrappleHookProjectile::HasFoundGrapplingTarget()
{
	return myHasFoundValidTarget;
}

CU::Vector2<float>& GrappleHookProjectile::GetGrapplingPoint()
{
	return myGrapplingPoint;
}
