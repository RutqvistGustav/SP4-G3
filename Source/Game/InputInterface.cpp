#include "stdafx.h"
#include "InputInterface.h"
#include "ControllerInput.h"
#include <Vector2.hpp>
#include <InputManager.h>
#include <WinUser.h>
#include <Xinput.h>

InputInterface::InputInterface(CommonUtilities::Input* aInput, ControllerInput* aControllerInput)
{
	if (myInput == nullptr &&
		aInput != nullptr)
	{
		myInput = aInput;
	}
	if (myControllerInput == nullptr &&
		aControllerInput != nullptr)
	{
		myControllerInput = aControllerInput;
	}
	myIsUsingController = false;
}

bool InputInterface::IsJumping() const
{
	return (myInput->IsKeyPressed(VK_SPACE) || myControllerInput->IsPressed(XINPUT_GAMEPAD_A));
}

bool InputInterface::IsBoosting() const
{
	return (myInput->GetMouseKeyStates().count(CommonUtilities::Input::EMouseKey::RIGHT) > 0 && myInput->GetMouseKeyStates().at(CommonUtilities::Input::EMouseKey::RIGHT).myKeyPressed) || myControllerInput->LeftTriggerPressed();
}

bool InputInterface::IsShooting() const
{
	return (myInput->GetMouseKeyStates().count(CommonUtilities::Input::EMouseKey::LEFT) > 0 && myInput->GetMouseKeyStates().at(CommonUtilities::Input::EMouseKey::LEFT).myKeyPressed) || myControllerInput->RightTriggerPressed();
}

bool InputInterface::IsHoldingMenuAccept() const
{
	return (myInput->GetMouseKeyStates().count(CommonUtilities::Input::EMouseKey::LEFT) > 0 && myInput->GetMouseKeyStates().at(CommonUtilities::Input::EMouseKey::LEFT).myKeyHold) || myControllerInput->GetRightTrigger() > 0.0f;
}

bool InputInterface::IsMovingLeft_Pressed()const
{
	return (myInput->IsKeyPressed(VK_LEFT) || myInput->IsKeyPressed('A') || myControllerInput->GetLeftStickX() < 0.0f);
}

bool InputInterface::IsMovingLeft_Down()
{
	if (myControllerInput->GetLeftStickX() < 0.0f)
	{
		myIsUsingController = true;
		return true;
	}
	else if (myInput->IsKeyDown(VK_LEFT) || myInput->IsKeyDown('A'))
	{
		myIsUsingController = false;
		return true;
	}
	return false;
}

bool InputInterface::IsMovingLeft_Released() const
{
	return (myInput->IsKeyReleased(VK_LEFT) || myInput->IsKeyReleased('A') || myControllerInput->LeftStickReleased());
}

bool InputInterface::IsMovingRight_Pressed() const
{
	return (myInput->IsKeyPressed(VK_RIGHT) || myInput->IsKeyPressed('D') || myControllerInput->GetLeftStickX() > 0.0f);
}

bool InputInterface::IsMovingRight_Down()
{
	if (myControllerInput->GetLeftStickX() > 0.0f)
	{
		myIsUsingController = true;
		return true;
	}
	else if (myInput->IsKeyDown(VK_RIGHT) || myInput->IsKeyDown('D'))
	{
		myIsUsingController = false;
		return true;
	}
	return false;
}

bool InputInterface::IsMovingRight_Released()const
{
	return (myInput->IsKeyReleased(VK_RIGHT) || myInput->IsKeyReleased('D') || myControllerInput->LeftStickReleased());
}

bool InputInterface::Is_G_Pressed() const
{
	return myInput->IsKeyPressed('G');
}

bool InputInterface::Is_C_Pressed() const
{
	return myInput->IsKeyPressed('C');
}

bool InputInterface::IsPressingUse() const
{
	return (myInput->IsKeyPressed('E') || myControllerInput->IsPressed(XINPUT_GAMEPAD_X));
}

bool InputInterface::IsPressingPause() const
{
	return (myInput->IsKeyPressed(VK_ESCAPE) || myControllerInput->IsPressed(XINPUT_GAMEPAD_START));
}

bool InputInterface::IsUsingController() const
{
	return myIsUsingController;
}

float InputInterface::GetRightStickX() const
{
	return myControllerInput->GetRightStickX();
}

float InputInterface::GetRightStickY() const
{
	return myControllerInput->GetRightStickY();
}

