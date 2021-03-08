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
	bool IsMovingLeft();
	bool IsMovingRight();

	//Perhaps return an int 1-8 depending on either Mouse to Player Direction or direction of Controller stick.
	void GetAimDirection();
private:

	CU::Input* myInput = nullptr;

};

