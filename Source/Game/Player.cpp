#include "stdafx.h"
#include "Player.h"

#include "UpdateContext.h"
#include "RenderContext.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

// Tools
#include "SpriteWrapper.h"
#include <Vector2.hpp>
#include <InputManager.h>
#include <iostream>

// json
#include <json.hpp>
#include <fstream>
#include <string>

Player::Player()
{
	// json
	nlohmann::json data;
	std::ifstream file("JSON/Player.json");
	data = nlohmann::json::parse(file);
	file.close();

	InitVariables(data);

	// Init Sprite
	mySprite = std::make_shared<SpriteWrapper>("Sprites/Grump.dds");
	CU::Vector2<float> startPosition(950.0f, 540.0f);
	mySprite->SetPosition(startPosition);
}

Player::~Player()
{
}

void Player::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	Controller(aDeltaTime, anUpdateContext.myInput);
}

void Player::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	aRenderQueue->Queue(RenderCommand(mySprite));
}

void Player::Controller(const float aDeltaTime, CommonUtilities::Input* anInput)
{
	Movement(aDeltaTime, anInput);

	//MouseInput(anInput);
}

void Player::Shoot()
{
	//std::cout << "Bang!" << std::endl;
}

void Player::Grapple()
{
	//std::cout << "Grapple!" << std::endl;
}



void Player::BrakeMovement(const float aDeltaTime)
{
	if (myIsMovingLeft == false && myIsMovingRight == false)
	{
		if (myVel.x > myStopAtVelocity || myVel.x < -myStopAtVelocity)
		{
			myVel.x *= pow(myReduceMovementSpeed, aDeltaTime);
		}
		else
		{
			myVel.x = 0;
		}
	}
}

void Player::InitVariables(nlohmann::json someData)
{
	// Movement
	mySpeed = someData.at("MovementSpeed");
	myMaxSpeed = someData.at("MaxSpeedCap");
	myReduceMovementSpeed = someData.at("BrakeStrength");
	myStopAtVelocity = someData.at("StopAtVelocity");
	myGravity = someData.at("GravityStrength");

	// Jump
	myJumpCharges = someData.at("JumpCharges");
	myJumpChargeReset = myJumpCharges;
	myJumpStrength = someData.at("JumpStrength");
	myJumpDuration = someData.at("JumpDuration");
	myJumpDurationReset = myJumpDuration;
}

void Player::Movement(const float aDeltaTime, CU::Input* anInput)
{
	CU::Vector2<float> movement = GetVel_KeyboardInput(anInput);

	if (myIsMovingLeft == true || myIsMovingRight == true)
	{
		if (myVel.x <= myMaxSpeed && -myMaxSpeed <= myVel.x)
		{
			myVel += movement * mySpeed * aDeltaTime;
		}
	}
	BrakeMovement(aDeltaTime);

	Jump(aDeltaTime);

	myPosition += myVel * aDeltaTime;
	mySprite->SetPosition(myPosition);

	//std::cout << "x " << myPosition.x << " y " << myPosition.y << std::endl; // temp
	//std::cout << "Velocity " << myVel.x << std::endl;
}

void Player::Jump(const float aDeltaTime)
{
	if (myIsJumping == true)
	{
		myJumpDuration -= aDeltaTime;
		if (myJumpDuration > 0)
		{
			if (myHasRemovedNegativeVel == false)
			{
				if (myVel.y >= 0)
				{
					myVel.y = 0;
				}
				myHasRemovedNegativeVel = true;
			}

			myVel.y -= myJumpStrength * aDeltaTime;
		}
		else
		{
			myIsJumping = false;
			myJumpDuration = myJumpDurationReset;
		}
		// remove 1 jump charge
	}
	else
	{
		if (myGravityActive == true)
		{
			myVel.y += myGravity * aDeltaTime;
		}
	}

	//std::cout << "Velocity.y " << myVel.y << std::endl;
}

CU::Vector2<float> Player::GetVel_KeyboardInput(CommonUtilities::Input* anInput)
{
	CU::Vector2<float> vel(0.0f, 0.0f);
	for (auto keyState : anInput->GetKeyStates())
	{
		char keyLetter = static_cast<char>(keyState.first);

		if (keyState.second.myKeyPressed == true)
		{
			if (keyState.first == 32) // 32 is spacebar
			{
				myIsJumping = true;
				myHasRemovedNegativeVel = false;
			}
			if (keyLetter == 'A') myIsMovingLeft = true;
			if (keyLetter == 'D') myIsMovingRight = true;
			if (keyLetter == 'G') // temp 
			{
				if (myGravityActive == false)
				{
					myGravityActive = true;
				}
				else
				{
					myGravityActive = false;
				}
			}
		}
		
		if (keyState.second.myKeyHold == true)
		{
			if (keyLetter == 'A') --vel.x;
			if (keyLetter == 'D') ++vel.x;
		}
		if (keyState.second.myKeyReleased == true)
		{
			if (keyLetter == 'A') myIsMovingLeft = false;
			if (keyLetter == 'D') myIsMovingRight = false;
		}
	}
	return vel;
}

void Player::MouseInput(CommonUtilities::Input* anInput)
{
	for (auto keyState : anInput->GetMouseKeyStates())
	{
		if (keyState.second.myKeyPressed == true)
		{
			int keyNum = static_cast<char>(keyState.first);
			if (keyNum == 0) Shoot();
			if (keyNum == 2) Grapple();
		}
	}
}
