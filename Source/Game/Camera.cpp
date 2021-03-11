#include "stdafx.h"
#include "Camera.h"
#include "Metrics.h"

Camera::Camera(const CU::Vector2<float> aPosition) :
    myPosition(aPosition),
    myCameraBounds({0.0f, 0.0f}),
    myDeltaMovement({ 0.0f, 0.0f })
{}

void Camera::Update(const CU::Vector2<float> aPosition)
{
    CU::Vector2<float> previousPosition = myPosition;

    //Temporary calculations for Camerabounds until we have some Macros or global variables for current resolution.
    if (myPosition.x + Metrics::GetReferenceSize().x / 2 < myCameraBounds.x &&
        myPosition.y + Metrics::GetReferenceSize().y / 2 < myCameraBounds.x &&
        myPosition.x - Metrics::GetReferenceSize().x / 2 > 0.0f &&
        myPosition.y - Metrics::GetReferenceSize().y / 2 > 0.0f)
    {
        myPosition = aPosition;
    }

    myDeltaMovement = aPosition - previousPosition;
}

void Camera::SetCameraBounds(const CU::Vector2<float> someCameraBounds)
{
    myCameraBounds = someCameraBounds;
}

const CU::Vector2<float> Camera::GetCameraDeltaMovement()
{
    return myDeltaMovement;
}

const CU::Vector2<float> Camera::GetCameraPosition()
{
    return myPosition;
}

void Camera::ActivateScreenShake()
{
    //TODO
}
