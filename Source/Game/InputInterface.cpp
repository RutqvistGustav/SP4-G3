#include "stdafx.h"
#include "InputInterface.h"
#include "ControllerInput.h"
#include <WinUser.h>

InputInterface::InputInterface(CU::Input* aInput, ControllerInput* aControllerInput)
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
	return (myInput->IsKeyPressed(VK_SPACE) || myControllerInput->IsPressed(VK_GAMEPAD_A));
}

bool InputInterface::IsGrappling()
{
	return (myInput->GetMouseKeyStates().at(CU::Input::EMouseKey::RIGHT).myKeyPressed/* ||  Get if Corresponding Gamepad button is pressed*/);
}

bool InputInterface::IsShooting()
{
	return (myInput->GetMouseKeyStates().at(CU::Input::EMouseKey::LEFT).myKeyPressed/* ||  Get if Corresponding Gamepad button is pressed*/);
}

bool InputInterface::IsMovingLeft()
{
	return (myInput->IsKeyPressed(VK_LEFT) || myInput->IsKeyPressed('A')/* ||  Get if Analog Stick is pushed left*/);
}

bool InputInterface::IsMovingRight()
{
	return (myInput->IsKeyPressed(VK_RIGHT) || myInput->IsKeyPressed('D')/* ||  Get if Analog Stick is pushed right*/);;
}

bool InputInterface::IsPressingUse()
{
	return (myInput->IsKeyPressed('E') || myControllerInput->IsPressed(VK_GAMEPAD_X));
}
