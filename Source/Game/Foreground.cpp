#include "stdafx.h"
#include "Foreground.h"
#include "SpriteWrapper.h"
#include "Metrics.h"
#include "RenderCommand.h";
#include "ForegroundImage.h";

void Foreground::Init()
{
	myX = Metrics::GetReferenceSize().x;
	myY = Metrics::GetReferenceSize().y;

	CreateForeground();
}

void Foreground::Update(const float aDeltaTime, CU::Vector2<float> aPlayerPos, const float aSpeed)
{
	myPlayerPos = CU::Vector2<int>(static_cast<int>(aPlayerPos.x), static_cast<int>(aPlayerPos.y));
	
	MoveForeground(aDeltaTime, aSpeed);

	myLastPlayerPos = CU::Vector2<int>(static_cast<int>(aPlayerPos.x), static_cast<int>(aPlayerPos.y));
}

void Foreground::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& f : myForegrounds)
	{
		f->Render(aRenderQueue, aRenderContext);
	}
}

void Foreground::CreateForeground()
{
	myForeground1 = std::make_shared<ForegroundImage>(20, CU::Vector2(myX * 0.5f, myY * .5f), 
		"Sprites/parallax/dust_bot.dds", true, true);
	myForegrounds.push_back(myForeground1);

	//myForeground2 = std::make_shared<ForegroundImage>(30, CU::Vector2(myX * 0.5f, myY * .5f), "sprites/parallax/dust_mid.dds");
	//myForegrounds.push_back(myForeground2);

	//myForeground3 = std::make_shared<ForegroundImage>(10, CU::Vector2(myX * 0.5f, myY * .5f), "Sprites/parallax/dust_mid02.dds");
	//myForegrounds.push_back(myForeground3);

	myForeground4 = std::make_shared<ForegroundImage>(40, CU::Vector2(myX * 0.5f, myY * .5f),
		"Sprites/parallax/dust_top.dds", false, false);
	myForegrounds.push_back(myForeground4);
}

void Foreground::MoveForeground(const float aDeltaTime, const float aSpeed)
{
	for (auto& f : myForegrounds)
	{
		FollowPlayer(f, aDeltaTime, aSpeed);
		//MoveX(f, aDeltaTime);
		//MoveY(f, aDeltaTime);	
	}
}

void Foreground::MoveX(std::shared_ptr<ForegroundImage> aImage, float aDeltaTime)
{
	const float leftBoundry = myX * 0.4f;
	const float rightBoundry = myX * 0.6f;
	float newX = aImage->GetPosition().x;
	float speed = aImage->GetSpeed() * aDeltaTime;

	if (aImage->GetMoveLeft())
	{
		newX -= speed;

		if (newX <= leftBoundry)
		{
			aImage->SetMoveLeft(false);
		}
	}
	else
	{
		newX += speed;

		if (newX >= rightBoundry)
		{
			aImage->SetMoveLeft(true);
		}
	}

	aImage->SetPosition(CU::Vector2(newX, aImage->GetPosition().y));
}

void Foreground::MoveY(std::shared_ptr<ForegroundImage> aImage, float aDeltaTime)
{
	const float topBoundry = myY * 0.44;
	const float botBoundry = myY * 0.56;
	float newY = aImage->GetPosition().y;
	float speed = aImage->GetSpeed() * aDeltaTime;

	if (aImage->GetMoveUp())
	{
		newY -= speed;

		if (newY <= topBoundry)
		{
			aImage->SetMoveUp(false);
		}
	}
	else
	{
		newY += speed;

		if (newY >= botBoundry)
		{
			aImage->SetMoveUp(true);
		}
	}

	aImage->SetPosition(CU::Vector2(aImage->GetPosition().x, newY));
}

void Foreground::FollowPlayer(std::shared_ptr<ForegroundImage> aImage, const float aDeltaTime, const float aSpeed)
{
	CU::Vector2<float> newPos = aImage->GetPosition();
	float foregroundSpeed = aSpeed * 0.2;

	if (myPlayerPos.y < myLastPlayerPos.y)
	{
	    newPos.y += foregroundSpeed * aDeltaTime;
	}
	if (myPlayerPos.y > myLastPlayerPos.y)
	{
		newPos.y -= aImage->GetPosition().y - foregroundSpeed * aDeltaTime;
	}

	if (myPlayerPos.x < myLastPlayerPos.x)
	{
		newPos.x += aImage->GetPosition().x + foregroundSpeed * aDeltaTime;
	}
	if (myPlayerPos.x > myLastPlayerPos.x)
	{
		newPos.x -= aImage->GetPosition().x - foregroundSpeed * aDeltaTime;
	}

	CU::Vector2<float> pos = CU::Vector2<float>(static_cast<float>(newPos.x), static_cast<float>(newPos.y));
	aImage->SetPosition(pos);
}
