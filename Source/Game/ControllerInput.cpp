#include "stdafx.h"
#include "ControllerInput.h"
#include <Xinput.h>
#include <iostream>

ControllerInput::ControllerInput() :
	myXDeadZone(0.15f),
	myYDeadZone(0.15f),
	myControllerId(-1)
{}

ControllerInput::ControllerInput(float aDeadZoneX, float aDeadZoneY) :
	myXDeadZone(aDeadZoneX),
	myYDeadZone(aDeadZoneY),
	myControllerId(-1)
{}

void ControllerInput::UpdateControllerState(float aDeltaTime)
{
	myElapsedTime += aDeltaTime;
	if (myElapsedTime >= myCheckCooldown && myControllerId == -1)
	{
		myControllerId = -1;

		for (DWORD i = 0; i < XUSER_MAX_COUNT && myControllerId == -1; i++)
		{
			ZeroMemory(&myState, sizeof(XINPUT_STATE));

			if (XInputGetState(i, &myState) == ERROR_SUCCESS)
				myControllerId = i;
		}
		myElapsedTime -= myCheckCooldown;
	}
	else
	{
		if (myControllerId != -1)
		{
			myPreviousState = myState;
			ZeroMemory(&myState, sizeof(XINPUT_STATE));
			if (XInputGetState(myControllerId, &myState) != ERROR_SUCCESS)
			{
				myControllerId = -1;
			}
			UpdateNormalizedStickValues();
		}
	}

}

//Normalizes the Stick Values and takes into account a Deadzone on the sticks.
void ControllerInput::UpdateNormalizedStickValues()
{
	//Whyy puu....
	myPreviousLeftStickX = myLeftStickX;

	float normalLeftStickX = fmaxf(-1.0f, (static_cast<float>(myState.Gamepad.sThumbLX) / 32767.0f));
	float normalLeftStickY = fmaxf(-1.0f, (static_cast<float>(myState.Gamepad.sThumbLY) / 32767.0f));

	//Subtracts the Deadzone Limit from the normalized value of the sticks if its above the deadzone
	myLeftStickX = (abs(normalLeftStickX) < myXDeadZone ? 0.0f : (abs(normalLeftStickX) - myXDeadZone) * (normalLeftStickX / abs(normalLeftStickX)));
	myLeftStickY = (abs(normalLeftStickY) < myYDeadZone ? 0.0f : (abs(normalLeftStickY) - myYDeadZone) * (normalLeftStickY / abs(normalLeftStickY)));

	//Scales The Normalized value remaining after subtracting the Deadzone and making it from 0 to 1 again;
	if (myXDeadZone > 0) myLeftStickX *= 1 / (1 - myXDeadZone);
	if (myYDeadZone > 0) myLeftStickY *= 1 / (1 - myYDeadZone);


	float normalRightStickX = fmaxf(-1, (static_cast<float>(myState.Gamepad.sThumbRX) / 32767));
	float normalRightStickY = fmaxf(-1, (static_cast<float>(myState.Gamepad.sThumbRY) / 32767));

	//Subtracts the Deadzone Limit from the normalized value of the sticks if its above the deadzone
	myRightStickX = (abs(normalRightStickX) < myXDeadZone ? 0 : (abs(normalRightStickX) - myXDeadZone) * (normalRightStickX / abs(normalRightStickX)));
	myRightStickY = (abs(normalRightStickY) < myYDeadZone ? 0 : (abs(normalRightStickY) - myYDeadZone) * (normalRightStickY / abs(normalRightStickY)));
	
	//Scales The Normalized value remaining after subtracting the Deadzone and making it from 0 to 1 again;
	if (myXDeadZone > 0) myRightStickX *= 1 / (1 - myXDeadZone);
	if (myYDeadZone > 0) myRightStickY *= 1 / (1 - myYDeadZone);

	//Normalizes the triggers return values
	myLeftTrigger = static_cast<float>(myState.Gamepad.bLeftTrigger / 255.0f);
	myRightTrigger = static_cast<float>(myState.Gamepad.bRightTrigger / 255.0f);
}

float ControllerInput::GetLeftStickX()
{
	return myLeftStickX;
}

float ControllerInput::GetLeftStickY()
{
	return myLeftStickY;
}

float ControllerInput::GetRightStickX()
{
	return myRightStickX;
}

float ControllerInput::GetRightStickY()
{
	return myRightStickY;
}

float ControllerInput::GetLeftTrigger()
{
	return myLeftTrigger;
}

float ControllerInput::GetRightTrigger()
{
	return myRightTrigger;
}

bool ControllerInput::IsPressed(WORD button)
{
	if (myControllerId != -1 && (myPreviousState.Gamepad.wButtons & button) == 0)
	{
		return (myState.Gamepad.wButtons & button) != 0;
	}
	return false;
}

bool ControllerInput::isReleased(WORD button)
{
	if (myControllerId != -1 && (myPreviousState.Gamepad.wButtons & button) != 0)
	{
		return (myState.Gamepad.wButtons & button) == 0;
	}
	return false;
}

bool ControllerInput::LeftStickReleased()
{
	return(myPreviousLeftStickX != 0 && myLeftStickX == 0);
}

