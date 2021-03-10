#pragma once
#include "InputManager.h"

namespace CommonUtilities
{
	class Input;
}

class InputInterface
{
public:
	InputInterface(CU::Input* aInput);
	~InputInterface() {};

	bool IsJumping();
	bool IsGrappling();
	bool IsShooting();

	bool IsMovingLeft_Pressed();
	bool IsMovingLeft_Down();
	bool IsMovingLeft_Released();

	bool IsMovingRight_Pressed();
	bool IsMovingRight_Down();
	bool IsMovingRight_Released();

	bool Is_G_Pressed();

	bool IsPressingUse();


	//Perhaps return an int 1-8 depending on either Mouse to Player Direction or direction of Controller stick.
	void GetAimDirection();
private:

	CU::Input* myInput = nullptr;

};

