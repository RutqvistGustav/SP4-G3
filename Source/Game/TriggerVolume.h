#pragma once

#include "GameObject.h"
#include "CollisionListener.h"
#include <any>
#include <optional>

class TriggerVolume :
	public CollisionListener, public GameObject
{
public:

	TriggerVolume(Scene* aScene, std::optional<GameObjectTag> aFilter = std::nullopt);

	void SetTriggerSize(const CU::Vector2<float>& aSize);
	const CU::Vector2<float>& GetTriggerSize() const;

protected:

	virtual void TriggerEnter(GameObject* aGameObject);
	virtual void TriggerStay(GameObject* aGameObject);
	virtual void TriggerExit(GameObject* aGameObject);

	virtual void OnEnter(const CollisionInfo& someCollisionInfo) final;
	virtual void OnStay(const CollisionInfo& someCollisionInfo) final;
	virtual void OnExit(const CollisionInfo& someCollisionInfo) final;

private:

	bool IsCollisionAccepted(const CollisionInfo& someCollisionInfo);

private:

	std::optional<GameObjectTag> myFilter;

};
