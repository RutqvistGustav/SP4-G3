#include "stdafx.h"
#include "TriggerVolume.h"

#include "Collider.h"

#include <cassert>

TriggerVolume::TriggerVolume(Scene* aScene, std::optional<GameObjectTag> aFilter) :
	GameObject(aScene, GameObjectTag::Trigger),
	myFilter(aFilter)
	, CollisionListener(aScene)
{}

void TriggerVolume::OnCollision(std::any aGameObject)
{
	assert(std::any_cast<GameObject*>(aGameObject) != nullptr && "OnCollision called with null GameObject!");

	if (myFilter.has_value() && std::any_cast<GameObject*>(aGameObject)->GetTag() != myFilter.value())
	{
		return;
	}

	//GameObject::OnCollision(aGameObject);

	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
		OnEnter(std::any_cast<GameObject*>(aGameObject));

		break;

	case Collider::eCollisionStage::MiddleFrames:
		OnStay(std::any_cast<GameObject*>(aGameObject));

		break;

	case Collider::eCollisionStage::LastFrame:
	case Collider::eCollisionStage::NotColliding:
		OnExit(std::any_cast<GameObject*>(aGameObject));

		break;
	}
}

void TriggerVolume::SetTriggerRadius(const float aRadius)
{
	//myCollider->SetRadius(aRadius);
}

const float TriggerVolume::GetTriggerRadius() const
{
	return 0.0f;
	//return myCollider->GetRadius();
}

void TriggerVolume::OnEnter(GameObject* /*aGameObject*/)
{}

void TriggerVolume::OnStay(GameObject* /*aGameObject*/)
{}

void TriggerVolume::OnExit(GameObject* /*aGameObject*/)
{}
