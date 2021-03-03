#include "stdafx.h"
#include "Player.h"

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
}

Player::~Player()
{
}

void Player::Update(const float aDeltaTime, CommonUtilities::Input* anInput)
{
	Controller(aDeltaTime, anInput);
}

void Player::Render()
{
}

void Player::Controller(const float aDeltaTime, CommonUtilities::Input* anInput)
{
	CU::Vector2<float> vel = GetVel_KeyboardInput(anInput);
	myPosition += vel * mySpeed * aDeltaTime;

	//std::cout << "x " << myPosition.x << " y " << myPosition.y << std::endl; // temp

	MouseInput(anInput);
}

void Player::Shoot()
{
	//std::cout << "Bang!" << std::endl;
}

void Player::Grapple()
{
	//std::cout << "Grapple!" << std::endl;
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
