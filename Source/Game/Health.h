#pragma once

#include "SimpleEventSubject.h"

class Health : public SimpleEventSubject<int>
{
public:

	Health(const int aHealthValue);
	
	void Update(const float aDeltaTime);
	
	void TakeDamage(const int aDamage);
	void AddHealth(const int aHealthAmount);

	void SetInvincibilityTimer(const float aTimerValue);
	const bool IsPlayerInvincible();

	void SetFullHealth();
	inline int GetHealth() const { return myHealth; }

	inline int GetMaxHealth() const { return myMaxHealth; }

	inline bool IsDead() { return myIsDead; }

private:

	void SetHealth(const int anAmount);

private:

	int myMaxHealth;
	int myHealth;
	float myTimerCountdown;
	float myInvincibilityTime;
	bool myIsDead;
	
	bool myIsInvisible = false;
};