#pragma once

#include "TriggerVolume.h"

class Player;

class Interactable : public TriggerVolume
{
public:

	Interactable(Scene* aScene);

protected:

	virtual void OnInteract(Player* aPlayer) = 0;

	virtual void OnStay(GameObject* aGameObject);
	virtual void OnExit(GameObject* aGameObject);

	virtual bool IsInteracting(Player* aPlayer);

private:

	void SetInRange(bool anInRange);

private:

	bool myInRange{};
	bool myIsInteracting{};

};
