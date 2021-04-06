#include "stdafx.h"
#include "TriggerVolume.h"

#include "Collider.h"
#include "CollisionInfo.h"
#include <cassert>

TriggerVolume::TriggerVolume(Scene* aScene, std::optional<GameObjectTag> aFilter) :
	GameObject(aScene, GameObjectTag::Trigger),
	myFilter(aFilter)
{}

//void TriggerVolume::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
//{
//	// NOTE: Do not render anything for a TriggerVolume
//}

void TriggerVolume::SetTriggerSize(const CU::Vector2<float>& aSize)
{
	myCollider->SetBoxSize(aSize);
}

const CU::Vector2<float>& TriggerVolume::GetTriggerSize() const
{
	return myCollider->GetBoxSize();
}

void TriggerVolume::TriggerEnter(GameObject* /*aGameObject*/)
{}

void TriggerVolume::TriggerStay(GameObject* /*aGameObject*/)
{}

void TriggerVolume::TriggerExit(GameObject* /*aGameObject*/)
{}

void TriggerVolume::OnEnter(const CollisionInfo& someCollisionInfo)
{
	if (IsCollisionAccepted(someCollisionInfo))
	{
		TriggerEnter(someCollisionInfo.myOtherCollider->GetGameObject());
	}
}

void TriggerVolume::OnStay(const CollisionInfo& someCollisionInfo)
{
	if (IsCollisionAccepted(someCollisionInfo))
	{
		TriggerStay(someCollisionInfo.myOtherCollider->GetGameObject());
	}
}

void TriggerVolume::OnExit(const CollisionInfo& someCollisionInfo)
{
	if (IsCollisionAccepted(someCollisionInfo))
	{
		TriggerExit(someCollisionInfo.myOtherCollider->GetGameObject());
	}
}

bool TriggerVolume::IsCollisionAccepted(const CollisionInfo& someCollisionInfo)
{
	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();

	if (gameObject == nullptr)
		return false;

	if (myFilter.has_value() && myFilter.value() != gameObject->GetTag())
	{
		return false;
	}

	return true;
}
