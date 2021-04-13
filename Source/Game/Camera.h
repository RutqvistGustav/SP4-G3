#pragma once

#include "AABB.h"
#include "ShakeBehaviour.h"

#include "SimpleEventSubject.h"

#include <Vector2.hpp>

struct UpdateContext;

class Camera :
	public SimpleEventSubject<CU::Vector2<float>>
{
public:

	Camera(const CU::Vector2<float> aPosition);
	~Camera() {};

	//Update Camera center position.
	void Update(float aDeltaTime, UpdateContext& anUpdateContext);

	//Method to set Current Level bounds.
	void SetLevelBounds(const AABB& someBounds);

	AABB GetViewBounds() const;

	//Get the total movement of the Camera this frame.
	const CU::Vector2<float> GetDeltaMovement() const;
	const CU::Vector2<float> GetPositionWithModifiers() const;
	const CU::Vector2<float> GetPosition() const;
	void SetPosition(const CU::Vector2<float> aPosition);

	void ActivateScreenShake(float aSpeed, float anAmplitude, float aDuration);

private:
	
	CU::Vector2<float> myDeltaMovement;

	CU::Vector2<float> myPosition;

	AABB myLevelBounds;

	ShakeBehaviour myShakeBehaviour;

};
