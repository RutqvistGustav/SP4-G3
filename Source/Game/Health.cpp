#include "stdafx.h"
#include "Health.h"

Health::Health(const int aHealthValue) : 
	myMaxHealth(aHealthValue),
	myHealth(myMaxHealth),
	myIsDead(false)
{}

void Health::TakeDamage(const int aDamage)
{
	myHealth -= aDamage;
	if (myHealth <= 0)
	{
		myIsDead = true;
	}
}

void Health::AddHealth(const int aHealthAmount)
{
	if ((myHealth + aHealthAmount) >= myMaxHealth)
	{
		myHealth = myMaxHealth;
		return;
	}
	myHealth += aHealthAmount;
}

const bool Health::IsDead()
{
	return myIsDead;
}
