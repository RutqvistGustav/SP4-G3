#include "stdafx.h"
#include "Camera.h"

Camera::Camera(const CU::Vector2<float> aPosition) :
    myPosition(aPosition),
    myCameraBounds({0.0f, 0.0f}),
    myDeltaMovement({ 0.0f, 0.0f })
{}

void Camera::Update(const CU::Vector2<float> aPosition)
{
    CU::Vector2<float> previousPosition = myPosition;

    //Temporary calculations for Camerabounds until we have some Macros or global variables for current resolution.
    if (myPosition.x + 960.0f < myCameraBounds.x &&
        myPosition.y + 540.0f < myCameraBounds.x &&
        myPosition.x - 960.0f > 0.0f && 
        myPosition.y - 540.0f > 0.0f)
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
