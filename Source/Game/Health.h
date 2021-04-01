#pragma once
class Health
{
public:
	Health(const int aHealthValue);
	
	void Update(const float aDeltaTime);
	
	void TakeDamage(const int aDamage);
	void AddHealth(const int aHealthAmount);
	const bool IsDead();

	void SetInvincibilityTimer(const float aTimerValue);
	const bool IsPlayerInvinsible();

private:
	int myMaxHealth;
	int myHealth;
	float myTimerCountdown;
	float myInvincibilityTime;
	bool myIsDead;
};

