#include "stdafx.h"
#include "TriggerVolume.h"

#include "Collider.h"

#include <cassert>

TriggerVolume::TriggerVolume(Scene* aScene, std::optional<GameObjectTag> aFilter) :
	GameObject(aScene, GameObjectTag::Trigger),
	myFilter(aFilter)
{}

void TriggerVolume::OnCollision(GameObject* aGameObject)
{
	assert(aGameObject != nullptr && "OnCollision called with null GameObject!");

	if (myFilter.has_value() && aGameObject->GetTag() != myFilter.value())
	{
		return;
	}

	GameObject::OnCollision(aGameObject);

	// TODO: Needs updating
	/*switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
		OnEnter(aGameObject);

		break;

	case Collider::eCollisionStage::MiddleFrames:
		OnStay(aGameObject);

		break;

	case Collider::eCollisionStage::LastFrame:
	case Collider::eCollisionStage::NotColliding:
		OnExit(aGameObject);

		break;
	}*/
}

void TriggerVolume::SetTriggerRadius(const float aRadius)
{
	myCollider->SetBoxSize({ aRadius, aRadius });
}

const float TriggerVolume::GetTriggerRadius() const
{
	return myCollider->GetBoxSize().x;
}

void TriggerVolume::OnEnter(GameObject* /*aGameObject*/)
{}

void TriggerVolume::OnStay(GameObject* /*aGameObject*/)
{}

void TriggerVolume::OnExit(GameObject* /*aGameObject*/)
{}
