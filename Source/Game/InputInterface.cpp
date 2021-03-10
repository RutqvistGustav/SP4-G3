#include "stdafx.h"
#include "InputInterface.h"
#include "ControllerInput.h"
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
}

bool InputInterface::IsJumping()
{
	return (myInput->IsKeyPressed(VK_SPACE) || myControllerInput->IsPressed(XINPUT_GAMEPAD_A));
}

bool InputInterface::IsGrappling()
{
	return myInput->GetMouseKeyStates().count(CommonUtilities::Input::EMouseKey::RIGHT) > 0 && (myInput->GetMouseKeyStates().at(CommonUtilities::Input::EMouseKey::RIGHT).myKeyPressed ||  myControllerInput->GetLeftTrigger() > 0.0f);
}

bool InputInterface::IsShooting()
{
	return myInput->GetMouseKeyStates().count(CommonUtilities::Input::EMouseKey::LEFT) > 0 && (myInput->GetMouseKeyStates().at(CommonUtilities::Input::EMouseKey::LEFT).myKeyPressed || myControllerInput->GetRightTrigger() > 0.0f);
}

bool InputInterface::IsMovingLeft_Pressed()
{
	return (myInput->IsKeyPressed(VK_LEFT) || myInput->IsKeyPressed('A')/* ||  Get if Analog Stick is pushed left*/);
}

bool InputInterface::IsMovingLeft_Down()
{
	return (myInput->IsKeyDown(VK_LEFT) || myInput->IsKeyDown('A')/* ||  Get if Analog Stick is pushed left*/);
}

bool InputInterface::IsMovingLeft_Released()
{
	return (myInput->IsKeyReleased(VK_LEFT) || myInput->IsKeyReleased('A'));
}

bool InputInterface::IsMovingRight_Pressed()
{
	return (myInput->IsKeyPressed(VK_RIGHT) || myInput->IsKeyPressed('D'));
}

bool InputInterface::IsMovingRight_Down()
{
	return (myInput->IsKeyDown(VK_RIGHT) || myInput->IsKeyDown('D')/* ||  Get if Analog Stick is pushed right*/);
}

bool InputInterface::IsMovingRight_Released()
{
	return (myInput->IsKeyReleased(VK_RIGHT) || myInput->IsKeyReleased('D'));
}

bool InputInterface::Is_G_Pressed()
{
	return myInput->IsKeyPressed('G');
}

bool InputInterface::IsPressingUse()
{
	return (myInput->IsKeyPressed('E') || myControllerInput->IsPressed(XINPUT_GAMEPAD_X));
}
