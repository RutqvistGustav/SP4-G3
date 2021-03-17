#include "stdafx.h"
#include "GrappleHookProjectile.h"

GrappleHookProjectile::GrappleHookProjectile(Scene* aScene)
	: GameObject(aScene)
{
}

void GrappleHookProjectile::Init()
{
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
		// render
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
	myDistanceTraveled += myDirection * aDeltaTime;
	if (myDistanceTraveled.Length() < myMaxDistance)
	{
		CU::Vector2<float> currentPosition = (aPlayerPosition + myDistanceTraveled) * aDeltaTime;
		SetPosition(currentPosition);
	}
	else
	{
		ResetProjectile();
	}
}

bool GrappleHookProjectile::HasFoundGrapplingTarget()
{
	return myHasFoundValidTarget;
}

void GrappleHookProjectile::SpawnProjectile(const CU::Vector2<float> aDirection)
{
	myIsFiring = true;
	myDirection = aDirection;
	myDirection *= myHookSpeed;
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
