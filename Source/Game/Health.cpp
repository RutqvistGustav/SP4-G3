#include "stdafx.h"
#include "Health.h"

#include "MathHelper.h"

//#include <iostream>

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
		if (myTimerCountdown <= 0.0f)
		{
			myIsInvisible = false;
		}
	}
}

void Health::TakeDamage(const int aDamage)
{
	if (myTimerCountdown <= 0.0f)
	{
		AddHealth(-aDamage);

		myTimerCountdown = myInvincibilityTime;
		myIsInvisible = true;
	}
}

void Health::AddHealth(const int aHealthAmount)
{
	SetHealth(GetHealth() + aHealthAmount);
}

void Health::SetInvincibilityTimer(const float aTimerValue)
{
	myInvincibilityTime = aTimerValue;
}

const bool Health::IsPlayerInvincible()
{
	return myTimerCountdown > 0.0f;
}

void Health::SetFullHealth()
{
	SetHealth(myMaxHealth);
}

void Health::SetHealth(const int anAmount)
{
	//return myIsInvisible;
	myHealth = MathHelper::Clamp(anAmount, 0, myMaxHealth);
	myIsDead = myHealth <= 0;

	Notify(myHealth);
}
