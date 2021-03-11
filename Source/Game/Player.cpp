#include "stdafx.h"
#include "Player.h"
#include "Collider.h"

// Tools
#include <Vector2.hpp>
#include <InputManager.h>
#include <iostream>

// json
#include <json.hpp>
#include <fstream>
#include <string>

Player::Player()
{
	nlohmann::json data;
	std::ifstream file("JSON/Player.json");
	data = nlohmann::json::parse(file);
	file.close();

	mySpeed = data.at("MovementSpeed");

	myOnGround = false;

	myPosition.x = 0.5f;
	myPosition.y = 0.5f;
	myPositionLastFrame = myPosition;

	myIsPlayer = true;//temporary
}

Player::~Player()
{
}

void Player::Update(const float aDeltaTime, CommonUtilities::Input* anInput)
{
	Controller(aDeltaTime, anInput);
	GameObject::Update(aDeltaTime);
}

void Player::Render()
{
}

void Player::Controller(const float aDeltaTime, CommonUtilities::Input* anInput)
{
	myVelocity = GetVel_KeyboardInput(anInput);
	static float gravitation = 0.f;

	//if (myCollider->isColliding())
	//{
	//	myVelocity = CU::Vector2<float>();
	//	//myPosition = myPositionLastFrame + CU::Vector2<float>(0.0f, -0.00001f);
	//	gravitation = 0.0f;
	//}
	//else
	//{
	//}

		gravitation += 0.01f * aDeltaTime;
		myVelocity.y += gravitation;
		myPosition += myVelocity * mySpeed * aDeltaTime;


	MouseInput(anInput);
	myPositionLastFrame = myPosition;
}

void Player::Shoot()
{
	//std::cout << "Bang!" << std::endl;
}

void Player::Grapple()
{
	//std::cout << "Grapple!" << std::endl;
}

void Player::OnCollision(const GameObject* aGameObject)
{
	myOnGround = true;
}

CU::Vector2<float> Player::GetVel_KeyboardInput(CommonUtilities::Input* anInput)
{
	CU::Vector2<float> vel(0.0f, 0.0f);
	for (auto keyState : anInput->GetKeyStates())
	{
		if (keyState.second.myKeyHold == true)
		{
			char keyLetter = static_cast<char>(keyState.first);

			if (keyLetter == 'A') --vel.x;
			if (keyLetter == 'D') ++vel.x;
			if (keyLetter == 'W') --vel.y;
			if (keyLetter == 'S') ++vel.y;


			if (keyLetter == 'L')
			{
				myPosition.x = 0.5;
				myPosition.y = 0.5;
				myVelocity = CU::Vector2<float>(0.0f, 0.0f);
			}
		}
	}
	vel.Normalize();
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
