#pragma once

#include "TriggerVolume.h"

class Player;

class Interactable : public TriggerVolume
{
public:

	Interactable(Scene* aScene);

protected:

	virtual void OnInteract(Player* aPlayer) = 0;

	virtual void TriggerStay(GameObject* aGameObject) override;
	virtual void TriggerExit(GameObject* aGameObject) override;

	virtual bool IsInteracting(Player* aPlayer);

	inline bool InRange() const { return myInRange; }
	inline bool IsInteracting() const { return myIsInteracting; }

private:

	void SetInRange(bool anInRange);

private:

	bool myInRange{};
	bool myIsInteracting{};

};
