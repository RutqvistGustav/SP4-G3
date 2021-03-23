#pragma once
class Health
{
public:
	Health(const int aHealthValue);
	
	void TakeDamage(const int aDamage);
	void AddHealth(const int aHealthAmount);
	const bool IsDead();

private:
	int myHealth;
	int myMaxHealth;
	bool myIsDead;
};

