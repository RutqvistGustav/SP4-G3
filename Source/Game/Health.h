#pragma once
class Health
{
public:
	Health(const int aHealthValue);
	
	void Update(const int aDeltaTime);
	
	void TakeDamage(const int aDamage);
	void AddHealth(const int aHealthAmount);
	const bool IsDead();

	void SetInvincibilityTimer(const float aTimerValue);

private:
	int myHealth;
	int myMaxHealth;
	float myTimerCountdown;
	float myInvincibilityTime;
	bool myIsDead;
};

