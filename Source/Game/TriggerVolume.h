#pragma once

#include "GameObject.h"
#include "CollisionListener.h"
#include <any>
#include <optional>

class TriggerVolume : public CollisionListener, public GameObject
{
public:

	TriggerVolume(Scene* aScene, std::optional<GameObjectTag> aFilter = std::nullopt);

	virtual void OnCollision(std::any aGameObject) override;

	void SetTriggerRadius(const float aRadius);
	const float GetTriggerRadius() const;

protected:

	virtual void OnEnter(GameObject* aGameObject);
	virtual void OnStay(GameObject* aGameObject);
	virtual void OnExit(GameObject* aGameObject);

private:

	std::optional<GameObjectTag> myFilter;

};
