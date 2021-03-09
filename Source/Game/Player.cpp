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

	// Init base variables
	mySpeed = data.at("MovementSpeed");
	myMaxSpeed = data.at("MaxSpeedCap");
	myReduceMovementSpeed = data.at("BrakeStrength");
	myStopAtVelocity = data.at("StopAtVelocity");
	myGravity = data.at("GravityStrength");

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

void Player::Jump()
{
	//myVel.y += 800.0f;
}

void Player::BrakeMovement(const float aDeltaTime)
{
	if (myIsMoving == false)
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

void Player::Movement(const float aDeltaTime, CU::Input* anInput)
{
	CU::Vector2<float> movement = GetVel_KeyboardInput(anInput);

	if (myIsMoving == true)
	{
		if (myVel.x <= myMaxSpeed && -myMaxSpeed <= myVel.x)
		{
			myVel += movement * mySpeed * aDeltaTime;
		}
	}

	//myVel.y += myGravity * aDeltaTime;
	BrakeMovement(aDeltaTime);

	myPosition += myVel * aDeltaTime;
	mySprite->SetPosition(myPosition);

	//std::cout << "x " << myPosition.x << " y " << myPosition.y << std::endl; // temp
	//std::cout << "Velocity " << myVel.x << std::endl;
}

CU::Vector2<float> Player::GetVel_KeyboardInput(CommonUtilities::Input* anInput)
{
	CU::Vector2<float> vel(0.0f, 0.0f);
	for (auto keyState : anInput->GetKeyStates())
	{
		if (keyState.second.myKeyPressed == true)
		{
			if (keyState.first == 32) Jump();
		}

		char keyLetter = static_cast<char>(keyState.first);
		if (keyState.second.myKeyHold == true)
		{
			if (keyLetter == 'A')
			{
				--vel.x;
				myIsMoving = true;
			}
			if (keyLetter == 'D')
			{
				++vel.x;
				myIsMoving = true;
			}
			//if (keyLetter == 'W') --vel.y;
			//if (keyLetter == 'S') ++vel.y;
		}
		if (keyState.second.myKeyReleased == true)
		{
			if (keyLetter == 'A')
			{
				myIsMoving = false;
			}
			if (keyLetter == 'D')
			{
				myIsMoving = false;
			}
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
