#include "stdafx.h"
#include "ShakeBehaviour.h"

#include "MathHelper.h"
#include "RandomHelper.h"

void ShakeBehaviour::Update(float aDeltaTime)
{
	if (myTime < 0.0f)
	{
		return;
	}

	myTime += aDeltaTime;

	if (myTime < myDuration)
	{
		myShakeVector = MathHelper::MoveTowards(myShakeVector, myShakeTarget, mySpeed * aDeltaTime);
		
		if ((myShakeTarget - myShakeVector).LengthSqr() < ShakeBehaviour::ourTargetThreshold)
		{
			RandomizeTarget();
		}
	}
	else
	{
		Stop();
	}
}

void ShakeBehaviour::Configure(float aSpeed, float anAmplitude, float aDuration)
{
	mySpeed = aSpeed;
	myAmplitude = anAmplitude;
	myDuration = aDuration;
	myTime = 0.0f;

	RandomizeTarget();
}

void ShakeBehaviour::Stop()
{
	myShakeVector = {};
	myTime = -1.0f;
}

const CU::Vector2<float>& ShakeBehaviour::GetShakeVector() const
{
	return myShakeVector;
}

void ShakeBehaviour::RandomizeTarget()
{
	myShakeTarget = RandomHelper::OnUnitCircle() * myAmplitude;
}
