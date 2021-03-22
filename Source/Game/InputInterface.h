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

	bool IsJumping()const;
	bool IsGrappling()const;
	bool IsShooting()const;

	bool IsMovingLeft_Pressed()const;
	bool IsMovingLeft_Down();
	bool IsMovingLeft_Released()const;

	bool IsMovingRight_Pressed()const;
	bool IsMovingRight_Down();
	bool IsMovingRight_Released()const;

	bool Is_G_Pressed()const;

	bool IsPressingUse()const;
	
	bool IsUsingController()const;

	float GetRightStickX();
	float GetRightStickY();

	//Perhaps return an int 1-8 depending on either Mouse to Player Direction or direction of Controller stick.
private:

	bool myIsUsingController;
	CommonUtilities::Input* myInput = nullptr;
	ControllerInput* myControllerInput = nullptr;
};

