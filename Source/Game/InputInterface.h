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

	CommonUtilities::Input* myInput = nullptr;
	ControllerInput* myControllerInput = nullptr;

};

