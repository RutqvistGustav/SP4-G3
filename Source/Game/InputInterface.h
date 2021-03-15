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
	bool IsMovingLeft_Down()const;
	bool IsMovingLeft_Released()const;

	bool IsMovingRight_Pressed()const;
	bool IsMovingRight_Down()const;
	bool IsMovingRight_Released()const;

	bool Is_G_Pressed()const;

	bool IsPressingUse()const;


	//Perhaps return an int 1-8 depending on either Mouse to Player Direction or direction of Controller stick.
	void GetAimDirection();
private:

	CommonUtilities::Input* myInput = nullptr;
	ControllerInput* myControllerInput = nullptr;

};

