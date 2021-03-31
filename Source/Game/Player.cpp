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

#include "CollisionInfo.h"

// Tools
#include "SpriteSheetAnimation.h"
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

	nlohmann::json data = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Player.json");
	
	InitVariables(data);

	myAnimator = std::make_unique<SpriteSheetAnimation>(GetScene()->GetGlobalServiceProvider()->GetJsonManager(), data.at("SpritePath"));
	myAnimator->SetState("default");
	myAnimator->SetIsLooping(true);

	// Init Sprite
	mySprite = std::make_shared<SpriteWrapper>();
	myAnimator->ApplyToSprite(mySprite);

	myHUD->Init();
	myWeaponController->Init();

	CU::Vector2<float> colliderSize = mySprite->GetSize();
	if (myColliderWidth > 0.0f) colliderSize.x = myColliderWidth;
	if (myColliderHeight > 0.0f) colliderSize.y = myColliderHeight;

	myCollider->SetBoxSize(colliderSize);
	myPhysicsController.Init(GetScene(), colliderSize);
	myPhysicsController.SetGravity({ 0.0f, myGravity });

	SetPosition(GetPosition());

	// Subscribe to events
	GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointSave, this);
	GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointLoad, this);
}

void Player::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	GameObject::Update(aDeltaTime, anUpdateContext);

	Move(aDeltaTime, anUpdateContext.myInputInterface);

#ifdef _DEBUG

	if (anUpdateContext.myInputInterface->Is_C_Pressed())
	{
		myScene->GetCollisionManager()->myDoRender = !myScene->GetCollisionManager()->myDoRender;
	}

#endif // _DEBUG

	myPhysicsController.Update(aDeltaTime);
	SetPosition(myPhysicsController.GetPosition() - myColliderShift);

#ifdef _DEBUG

	//Movement(aDeltaTime, anUpdateContext.myInputInterface);
	
	ImGui();

#endif

	const CU::Vector2<float> newCameraPosition = MathHelper::MoveTowards(myCamera->GetPosition(), myPosition, myCameraFollowSpeed * aDeltaTime);
	myCamera->SetPosition(newCameraPosition);

	myHealth->Update(aDeltaTime);
	myHUD->Update(myPosition);

	myWeaponController->Update(aDeltaTime, anUpdateContext);

	myAnimator->Update(aDeltaTime);
	myAnimator->ApplyToSprite(mySprite);
}

void Player::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(mySprite));

	myHUD->Render(aRenderQueue, aRenderContext);
	myWeaponController->Render(aRenderQueue, aRenderContext);
}

void Player::ApplyForce(const CU::Vector2<float>& aForce)
{
	myPhysicsController.ApplyForce(aForce);
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

	//Health
	myHealth = std::make_unique<Health>(someData.at("Health"));
	myHealth->SetInvincibilityTimer(someData.at("Invincibility"));

	myColliderWidth = someData.value("ColliderWidth", -1.0f);
	myColliderHeight = someData.value("ColliderHeight", -1.0f);

	myColliderShift = { 40.0f, 50.0f };
}

void Player::StopMovement()
{
	myPhysicsController.SetVelocity({});
}

void Player::OnStay(const CollisionInfo& someCollisionInfo)
{
	/*if (someCollisionInfo.myOtherCollider->IsTrigger() == false)
	{
		SetPosition(myPosition);
	}*/
}

void Player::SetPosition(const CU::Vector2<float> aPosition)
{
	GameObject::SetPosition(aPosition);

	myCollider->SetPosition(aPosition + myColliderShift);
	myPhysicsController.SetPosition(aPosition + myColliderShift);
}

void Player::SetControllerActive(const bool aState)
{
	myIsControllerActive = aState;
	//myVel = CU::Vector2<float>();
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
	ImGui::InputFloat("BrakeStrength", &myReduceMovementSpeed, 0, 1.0);

	ImGui::Text("");

	ImGui::Text("Will stop player entirely when movement slows down and approaches the StopAtVelocity amount.");
	ImGui::DragFloat("StopAtVelocity", &myStopAtVelocity, 0, 10000.0f);

	ImGui::Text("");

	ImGui::SliderFloat("GravityStrength", &myGravity, 0, 100000.0f);

	ImGui::SliderInt("JumpCharges", &myJumpCharges, 0, 100);

	ImGui::SliderFloat("JumpStrength", &myJumpStrength, 0, 100000);

	ImGui::Text("");
	ImGui::Text("Note!");
	ImGui::Text("ImGui will not change values in Player.json.");
	ImGui::Text("You are gonna have to do that yourself :D.");

	ImGui::End();
}

void Player::Move(const float aDeltaTime, InputInterface* anInput)
{
	CU::Vector2<float> velocity = myPhysicsController.GetVelocity();

	const CU::Vector2<float> direction = GetDirection(anInput);
	velocity.x *= std::powf(myReduceMovementSpeed, aDeltaTime);
	velocity.x += direction.x * mySpeed * aDeltaTime;
	velocity.x = MathHelper::Clamp(velocity.x, -myMaxSpeed, myMaxSpeed);

	if (std::fabsf(velocity.x) <= myStopAtVelocity)
	{
		velocity.x = 0.0f;
	}

	if (myPhysicsController.IsGrounded())
	{
		myJumpCharges = myJumpChargeReset;
	}

	if (anInput->IsJumping() && myJumpCharges > 0)
	{
		velocity.y = -myJumpStrength;
		--myJumpCharges;
	}

	myPhysicsController.SetVelocity(velocity);
}

CU::Vector2<float> Player::GetDirection(InputInterface* anInput)
{
	CU::Vector2<float> direction(0.0f, 0.0f);
	if (anInput->IsMovingLeft_Down()) --direction.x;
	if (anInput->IsMovingRight_Down()) ++direction.x;

	return direction;
}
