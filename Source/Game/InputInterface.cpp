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
	myUsingController = false;
}

bool InputInterface::IsJumping()
{
	return (myInput->IsKeyPressed(VK_SPACE)/* || Get if A Button is pressed*/);
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
	return (myInput->IsKeyPressed(VK_LEFT) || myInput->IsKeyPressed('A')/* || Get if A Button is pressed*/);
}

bool InputInterface::IsMovingRight()
{
	return (myInput->IsKeyPressed(VK_RIGHT) || myInput->IsKeyPressed('D')/* || Get if A Button is pressed*/);;
}
