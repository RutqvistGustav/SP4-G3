#include "stdafx.h"
#include "Health.h"
#include <iostream>

Health::Health(const int aHealthValue) :
	myMaxHealth(aHealthValue),
	myHealth(myMaxHealth),
	myIsDead(false),
	myInvincibilityTime(0.0f),
	myTimerCountdown(0.0f)
{}

void Health::Update(const float aDeltaTime)
{
	if (myTimerCountdown > 0.0f)
	{
		myTimerCountdown -= aDeltaTime;
	}
}

void Health::TakeDamage(const int aDamage)
{
	if (IsPlayerInvinsible())
	{
		myHealth -= aDamage;
		if (myHealth <= 0)
		{
			myIsDead = true;
		}
		myTimerCountdown = myInvincibilityTime;
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

void Health::SetInvincibilityTimer(const float aTimerValue)
{
	myInvincibilityTime = aTimerValue;
}

const bool Health::IsPlayerInvinsible()
{
	return (myTimerCountdown <= 0.0f);
}
