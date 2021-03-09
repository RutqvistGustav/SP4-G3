#include "stdafx.h"
#include "InputInterface.h"
#include <WinUser.h>

InputInterface::InputInterface(CU::Input* aInput)
{
	if (myInput == nullptr &&
		aInput != nullptr)
	{
		myInput = aInput;
	}
	

	//TODO: add Controller states if Controller is plugged in!
}

bool InputInterface::IsJumping()
{
	return (myInput->IsKeyPressed(VK_SPACE)/* || Get if A Button is pressed*/);
}

bool InputInterface::IsGrappling()
{
	return myInput->GetMouseKeyStates().count(CU::Input::EMouseKey::RIGHT) > 0 && (myInput->GetMouseKeyStates().at(CU::Input::EMouseKey::RIGHT).myKeyPressed/* ||  Get if Corresponding Gamepad button is pressed*/);
}

bool InputInterface::IsShooting()
{
	return myInput->GetMouseKeyStates().count(CU::Input::EMouseKey::LEFT) > 0 && (myInput->GetMouseKeyStates().at(CU::Input::EMouseKey::LEFT).myKeyPressed/* ||  Get if Corresponding Gamepad button is pressed*/);
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
	return (myInput->IsKeyPressed('E')/* || Get if X Button is pressed*/);
}
