#include "stdafx.h"
#include "Player.h"

#include "UpdateContext.h"
#include "RenderContext.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

#include "PlayerWeaponController.h"
#include "Scene.h"
#include "HUD.h"

// Tools
#include "SpriteWrapper.h"
#include <Vector2.hpp>
#include "InputInterface.h"
#include <iostream>
#include <imgui.h>

// json
#include <json.hpp>
#include <fstream>
#include <string>

Player::Player(Scene* aScene)
	: GameObject(aScene)
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

	// Init weapon controller
	myWeaponController = std::make_unique<PlayerWeaponController>(GetScene()->GetWeaponFactory(), this);

	// Init HUD
	myHUD = std::make_unique<HUD>(aScene);
}

Player::~Player() = default;

void Player::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	Controller(aDeltaTime, anUpdateContext.myInputInterface);

	//ImGui();
	
	myHUD->Update(myPosition);
	myWeaponController->Update(aDeltaTime, anUpdateContext);
}

void Player::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(mySprite));

	myHUD->Render(aRenderQueue, aRenderContext);
	myWeaponController->Render(aRenderQueue, aRenderContext);
}

void Player::Controller(const float aDeltaTime, InputInterface* anInput)
{
	Movement(aDeltaTime, anInput);
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

void Player::ApplyForce(const CU::Vector2<float>& aForce)
{
	myVel += aForce;
}

void Player::PlayerInput(InputInterface* anInput)
{
	if (anInput->IsMovingLeft_Pressed())
	{
		myIsMovingLeft = true;
		//std::cout << "Left Pressed" << std::endl;
	}
	if (anInput->IsMovingRight_Pressed())
	{
		myIsMovingRight = true;
		//std::cout << "Right Pressed" << std::endl;
	}
	if (anInput->IsMovingLeft_Released())
	{
		myIsMovingLeft = false;
		//std::cout << "Left Released" << std::endl;
	}
	if (anInput->IsMovingRight_Released())
	{
		myIsMovingRight = false;
		//std::cout << "Right Released" << std::endl;
	}

	if (anInput->IsJumping())
	{
		myIsJumping = true;
		myHasRemovedNegativeVel = false;
	}

	if (anInput->Is_G_Pressed())
	{
		if (myGravityActive == false)
		{
			myGravityActive = true;
		}
		else
		{
			myVel.y = 0;
			myGravityActive = false;
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

void Player::ImGui()
{
	ImGui::Begin("Player movement");

	ImGui::Text("");
	ImGui::SliderFloat("MovementSpeed", &mySpeed, 0, 100000);
	ImGui::SliderFloat("MaxSpeedCap", &myMaxSpeed, 0, 100000);

	ImGui::Text("");

	ImGui::Text("To make BrakeStrength stronger then use more zeroes after decimal. Ex. 0.0000001.");
	ImGui::Text("To make BrakeStrength weaker then use less zeroes after decimal. Ex. 0.0001.");
	ImGui::InputDouble("BrakeStrength", &myReduceMovementSpeed, 0, 1.0);

	ImGui::Text("");

	ImGui::Text("Will stop player entirely when movement slows down and approaches the StopAtVelocity amount.");
	ImGui::DragFloat("StopAtVelocity", &myStopAtVelocity, 0, 10000.0f);

	ImGui::Text("");

	ImGui::SliderFloat("GravityStrength", &myGravity, 0, 100000.0f);

	ImGui::SliderInt("JumpCharges", &myJumpCharges, 0, 100);
	myJumpChargeReset = myJumpCharges;

	ImGui::SliderFloat("JumpStrength", &myJumpStrength, 0, 100000);

	ImGui::Text("");

	ImGui::Text("JumpDuration resets only to the value given in Player.json");
	ImGui::Text("So if you want the JumpDuration to reset at a different value");
	ImGui::Text("then change the value in Player.json first.");
	ImGui::SliderFloat("JumpDuration", &myJumpDuration, 0, 5.0f);

	ImGui::Text("");
	ImGui::Text("Note!");
	ImGui::Text("ImGui will not change values in Player.json.");
	ImGui::Text("You are gonna have to do that yourself :D.");

	ImGui::End();
}

void Player::Movement(const float aDeltaTime, InputInterface* anInput)
{
	PlayerInput(anInput);
	CU::Vector2<float> movement = GetDirection(anInput);

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

	//std::cout << "x " << myPosition.x << " y " << myPosition.y << std::endl;
	//std::cout << "Velocity " << myVel.x << std::endl;
}

void Player::Jump(const float aDeltaTime)
{
	if (myIsJumping == true /*&& myJumpCharges > 0*/)
	{
		myJumpDuration -= aDeltaTime;
		if (myJumpDuration > 0)
		{
			if (myHasRemovedNegativeVel == false)
			{
				myVel.y = 0;
				myHasRemovedNegativeVel = true;
			}

			myVel.y -= myJumpStrength * aDeltaTime;
		}
		else
		{
			myIsJumping = false;
			myJumpDuration = myJumpDurationReset;
			//--myJumpCharges;
		}
		// if landed set myVel.y = 0
		// Reset myJumpCharges
	}
	else
	{
		if (myGravityActive == true)
		{
			myVel.y += myGravity * aDeltaTime;
		}
	}
}

CU::Vector2<float> Player::GetDirection(InputInterface* anInput)
{
	CU::Vector2<float> direction(0.0f, 0.0f);
	if (anInput->IsMovingLeft_Down() && myIsMovingRight == false)
	{
		--direction.x;
		//std::cout << "Left" << std::endl;
	}
	if (anInput->IsMovingRight_Down() && myIsMovingLeft == false)
	{
		++direction.x;
		//std::cout << "Right direction" << direction.x << std::endl;
	}

	return direction;
}
