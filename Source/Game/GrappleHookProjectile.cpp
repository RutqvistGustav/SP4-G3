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
		Movement(aDeltaTime);
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
	//if (/*GameObject is valid target*/)
	//{
	//	myGrapplingPoint = aGrapplingPoint;
	//	myHasFoundValidTarget = true;
	//}
}

void GrappleHookProjectile::Movement(const float aDeltaTime)
{
	myDistanceTraveled += myHookSpeed * aDeltaTime;
	if (myDistanceTraveled < myMaxDistance)
	{
		SetPosition(myPosition * myHookSpeed * aDeltaTime);
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

void GrappleHookProjectile::SetIsFiring(const CU::Vector2<float> aPlayerPosition, const CU::Vector2<float> aDirection)
{
	myIsFiring = true;
	SetPosition(aPlayerPosition);
	// direction
}

void GrappleHookProjectile::ResetProjectile()
{
	myIsFiring = false;
	myHasFoundValidTarget = false;

	myDistanceTraveled = 0.0f;
	myGrapplingPoint = { 0.0f,0.0f };
}

CU::Vector2<float>& GrappleHookProjectile::GetGrapplingPoint()
{
	return myGrapplingPoint;
}
