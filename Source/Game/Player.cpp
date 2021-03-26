#include "stdafx.h"
#include "Player.h"
#include "Collider.h"

#include "UpdateContext.h"
#include "RenderContext.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

#include "PlayerWeaponController.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "HUD.h"

#include "CheckpointMessage.h"
#include "CheckpointContext.h"

#include "GameMessenger.h"
#include "Scene.h"

#include "Camera.h"
#include "MathHelper.h"
#include "Health.h"

// Tools
#include "SpriteWrapper.h"
#include <Vector2.hpp>
#include "InputInterface.h"
#include <iostream>
#include <imgui.h>
#include "JsonManager.h"

// json
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>


#ifdef _DEBUG
#include "CollisionManager.h"
#endif // _DEBUG



Player::Player(Scene* aScene)
	: GameObject(aScene, GameObjectTag::Player),
	myCamera(aScene->GetCamera())
{
	// Init weapon controller
	myWeaponController = std::make_unique<PlayerWeaponController>(GetScene(), this);

	// Init HUD
	myHUD = std::make_unique<HUD>(aScene);
}

Player::~Player()
{
	GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::CheckpointLoad, this);
	GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::CheckpointSave, this);
}

void Player::Init()
{
	GameObject::Init();

	// json
	nlohmann::json data;
	std::ifstream file("JSON/Player.json");
	data = nlohmann::json::parse(file);
	file.close();

	InitVariables(data);

	myIsOnGround = false;
	myPosition.x = 0.5f;
	myPosition.y = 0.5f;

	// Init Sprite
	mySprite = std::make_shared<SpriteWrapper>(data.at("SpritePath"));
	CU::Vector2<float> startPosition(950.0f, 540.0f);
	mySprite->SetPosition(startPosition);

	myHUD->Init();
	myWeaponController->Init();
	
	// Subscribe to events
	GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointSave, this);
	GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointLoad, this);
}

void Player::Update(const float aDeltaTime, UpdateContext & anUpdateContext)
{
	GameObject::Update(aDeltaTime, anUpdateContext);
	Movement(aDeltaTime, anUpdateContext.myInputInterface);

	ImGui();

	const CU::Vector2<float> newCameraPosition = MathHelper::MoveTowards(myCamera->GetPosition(), myPosition, myCameraFollowSpeed * aDeltaTime);
	myCamera->SetPosition(newCameraPosition);

	myHealth->Update(aDeltaTime);
	myHUD->Update(myPosition);

	myWeaponController->Update(aDeltaTime, anUpdateContext);

}

void Player::Render(RenderQueue* const aRenderQueue, RenderContext & aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(mySprite));

	myHUD->Render(aRenderQueue, aRenderContext);
	myWeaponController->Render(aRenderQueue, aRenderContext);
}



void Player::BrakeMovement(const float aDeltaTime)
{
	//MouseInput(anInput);
	//myPositionLastFrame = myPosition;
	/*if (myIsMovingLeft == false && myIsMovingRight == false)
	{*/
		if (myVel.x > myStopAtVelocity || myVel.x < -myStopAtVelocity)
		{
			myVel.x *= pow(myReduceMovementSpeed, aDeltaTime);
		}
		else
		{
			myVel.x = 0;
		}
	//}
}

void Player::ApplyForce(const CU::Vector2<float>&aForce)
{
	if (myVel.x + aForce.x <= myMaxSpeed && myVel.x - aForce.x >= -myMaxSpeed)
	{
		myVel += aForce;
	}
}

void Player::PlayerInput(InputInterface * anInput)
{
	myIsMovingLeft = anInput->IsMovingLeft_Down();
	myIsMovingRight = anInput->IsMovingRight_Down();

	if (anInput->IsJumping())
	{
		myIsJumping = true;
		myHasRemovedNegativeVel = false;
		myJumpDuration = myJumpDurationReset;
		--myJumpCharges;
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

#ifdef _DEBUG
	if (anInput->Is_C_Pressed())
	{
		myScene->GetCollisionManager()->myDoRender = !myScene->GetCollisionManager()->myDoRender;
	}
#endif // _DEBUG


}

void Player::InitVariables(nlohmann::json someData)
{
	myCameraFollowSpeed = someData.value("CameraFollowSpeed", 2000.0f);

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

	//Health
	myHealth = std::make_unique<Health>(someData.at("Health"));
	myHealth->SetInvincibilityTimer(someData.at("Invincibility"));
}

void Player::OnCollision(GameObject* aGameObject)
{
	CU::Vector2<float> fromOtherToMe(myPosition - aGameObject->GetPosition());
	float overlap = 0.0f;

	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:

		
		/*if (myCollider->GetIsCube())
		{*/
			//myPosition = myPositionLastFrame + fromOtherToMe.GetNormalized()*0.01f;
			//myPosition.y = aGameObject->GetPosition().y - aGameObject->GetCollider()->GetRadius() - myCollider->GetRadius();
		/*}
		else
		{
			overlap = fromOtherToMe.Length() - myCollider->GetRadius() - aGameObject->GetCollider()->GetRadius();
			myPosition -= overlap * fromOtherToMe.GetNormalized();
		}*/


		/*myVel = CU::Vector2<float>(myVel.x, 0.0f);
		myGravityActive = false;
		myCollider->SetPos(myPosition);*/

		break;
	case Collider::eCollisionStage::NotColliding:
		//myGravityActive = true;


		break;
	default:
		break;
	}
}

void Player::OnCollision(TileType aTileType, CU::Vector2<float> anOffset)
{
	float overlap = 0.0f;

	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:



		/*if (myCollider->GetIsCube())
		{*/
		myPosition = myPositionLastFrame - anOffset * 0.01f;
		//myPosition.y = aGameObject->GetPosition().y - aGameObject->GetCollider()->GetRadius() - myCollider->GetRadius();
	/*}
	else
	{
		overlap = fromOtherToMe.Length() - myCollider->GetRadius() - aGameObject->GetCollider()->GetRadius();
		myPosition -= overlap * fromOtherToMe.GetNormalized();
	}*/

		myJumpCharges = myJumpChargeReset;
		myIsJumping = false;
		myIsOnGround = true;

		myVel = CU::Vector2<float>(myVel.x, 0.0f);
		//myGravityActive = false;
		myCollider->SetPos(myPosition);

		break;
	case Collider::eCollisionStage::NotColliding:

		if (myIsOnGround == true)
		{
			myGravityActive = true;
			myIsOnGround = false;
		}


		break;
	default:
		break;
	}
}

void Player::StopMovement()
{
	myVel = CU::Vector2<float>();
}

void Player::TakeDamage(const int aDamage)
{
	myHealth->TakeDamage(aDamage);
}

void Player::AddHealth(const int aHealthAmount)
{
	myHealth->AddHealth(aHealthAmount);
}

GameMessageAction Player::OnMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData)
{
	switch (aMessage)
	{
	case GameMessage::CheckpointSave:
		// TODO

		break;

	case GameMessage::CheckpointLoad:
		// TODO

		break;

	default:
		assert(false);
		break;
	}

	return GameMessageAction::Keep;
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

void Player::Movement(const float aDeltaTime, InputInterface * anInput)
{
	PlayerInput(anInput);
	CU::Vector2<float> direction = GetDirection(anInput);

	if (myIsMovingLeft == true && -myMaxSpeed <= myVel.x && myVel.y <= myMaxSpeed)
	{
		if (myVel.x > 0)
		{
			BrakeMovement(aDeltaTime);
		}
		else
		{
			myVel.x += direction.x * mySpeed * aDeltaTime;
		}
	}
	if (myIsMovingRight == true && myVel.x <= myMaxSpeed && myVel.y <= myMaxSpeed)
	{
		if (myVel.x < 0)
		{
			BrakeMovement(aDeltaTime);
		}
		else
		{
			myVel.x += direction.x * mySpeed * aDeltaTime;
		}
	}

	Jump(aDeltaTime);
	if (myIsMovingLeft == false && myIsMovingRight == false)
	{
		BrakeMovement(aDeltaTime);
	}

	//if (myVel.LengthSqr() > 4096/*64^2*/)//max speed
	//{
	//	myVel = myVel.GetNormalized() * 64.f;
	//}

	myPosition += myVel * aDeltaTime;
	mySprite->SetPosition(myPosition);
	SetPosition(GetPosition() + myVel * aDeltaTime);

	//std::cout << "x " << myPosition.x << " y " << myPosition.y << std::endl;
	//std::cout << "Velocity " << myVel.x << std::endl;
}

void Player::Jump(const float aDeltaTime)
{
	if (myIsJumping == true && myJumpCharges >= 0)
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
			myGravityActive = true;
			myIsJumping = false;
			myJumpDuration = myJumpDurationReset;
		}
	}
	else if (myGravityActive == true)
	{
		myVel.y += myGravity * aDeltaTime;
	}
}

CU::Vector2<float> Player::GetDirection(InputInterface * anInput)
{
	CU::Vector2<float> direction(0.0f, 0.0f);
	if (anInput->IsMovingLeft_Down()) --direction.x;
	if (anInput->IsMovingRight_Down()) ++direction.x;

	return direction;
}
