#include "stdafx.h"
#include "Camera.h"
#include "Metrics.h"

Camera::Camera(const CU::Vector2<float> aPosition) :
    myPosition(aPosition)
{}

void Camera::Update(float aDeltaTime, UpdateContext& /*anUpdateContext*/)
{
    myShakeBehaviour.Update(aDeltaTime);
}

void Camera::SetLevelBounds(const AABB& someBounds)
{
    myLevelBounds = someBounds;
}

const CU::Vector2<float> Camera::GetDeltaMovement()
{
    return myDeltaMovement;
}

const CU::Vector2<float> Camera::GetPositionWithModifiers()
{
    const CU::Vector2<float> centeringOffset = -0.5f * Metrics::GetReferenceSize();
    return centeringOffset + GetPosition() + myShakeBehaviour.GetShakeVector();
}

const CU::Vector2<float> Camera::GetPosition()
{
    return myPosition;
}

void Camera::SetPosition(const CU::Vector2<float> aPosition)
{
    CU::Vector2<float> movementDelta = aPosition - GetPosition();

    AABB cameraBounds = AABB::FromCenterAndSize(aPosition, Metrics::GetReferenceSize());
    
    if (cameraBounds.GetMax().x >= myLevelBounds.GetMax().x)
    {
        movementDelta.x += myLevelBounds.GetMax().x - cameraBounds.GetMax().x;
    }
    else if (cameraBounds.GetMin().x <= myLevelBounds.GetMin().x)
    {
        movementDelta.x += myLevelBounds.GetMin().x - cameraBounds.GetMin().x;
    }

    if (cameraBounds.GetMax().y >= myLevelBounds.GetMax().y)
    {
        movementDelta.y += myLevelBounds.GetMax().y - cameraBounds.GetMax().y;
    }
    else if (cameraBounds.GetMin().y <= myLevelBounds.GetMin().y)
    {
        movementDelta.y += myLevelBounds.GetMin().y - cameraBounds.GetMin().y;
    }

    myDeltaMovement = movementDelta;
    myPosition += movementDelta;
}

void Camera::ActivateScreenShake(float aSpeed, float anAmplitude, float aDuration)
{
    myShakeBehaviour.Configure(aSpeed, anAmplitude, aDuration);
}
