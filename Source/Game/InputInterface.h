#pragma once
namespace CommonUtilities
{
	class Input;
}

class ControllerInput;

class InputInterface
{
public:
	InputInterface(CommonUtilities::Input* aInput, ControllerInput* aControllerInput);
	~InputInterface() {};

	bool IsJumping();
	bool IsGrappling();
	bool IsShooting();
	bool IsMovingLeft();
	bool IsMovingRight();
	bool IsPressingUse();

	//Perhaps return an int 1-8 depending on either Mouse to Player Direction or direction of Controller stick.
	void GetAimDirection();
private:

	CommonUtilities::Input* myInput;
	ControllerInput* myControllerInput = nullptr;

};

