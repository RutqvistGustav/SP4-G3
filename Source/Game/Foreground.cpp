#include "stdafx.h"
#include "Foreground.h"
#include "SpriteWrapper.h"
#include "Metrics.h"
#include "RenderCommand.h";

void Foreground::Init()
{
	myX = Metrics::GetReferenceSize().x;
	myY = Metrics::GetReferenceSize().y;

	myMoveLeft = true;
	myMoveUp = true;

	CreateForeground();
}

void Foreground::Update(const float aDeltaTime)
{
	MoveForeground(aDeltaTime);
}

void Foreground::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& f : myForegrounds)
	{
		RenderCommand renderCommand = RenderCommand(f);
		aRenderQueue->Queue(renderCommand);
	}
}

void Foreground::CreateForeground()
{
	myForeground1 = std::make_shared<SpriteWrapper>("Sprites/parallax/dust_bot.dds");
	myForeground1->SetPosition(CU::Vector2(myX * 0.5f, myY * .5f));
	myForegrounds.push_back(myForeground1);

	myForeground2 = std::make_shared<SpriteWrapper>("sprites/parallax/dust_bot.dds");
	myForeground2->SetPosition(CU::Vector2(myX * 0.5f, myY * .5f));
	myForegrounds.push_back(myForeground2);

	//myForeground3 = std::make_shared<SpriteWrapper>("Sprites/parallax/dust_mid02.dds");
	//myForeground3->SetPosition(CU::Vector2(myX * 0.5f, myY * .6f));
	//myForegrounds.push_back(myForeground3);

	myForeground4 = std::make_shared<SpriteWrapper>("Sprites/parallax/dust_top.dds");
	myForeground4->SetPosition(CU::Vector2(myX * 0.5f, myY * .5f));
	myForegrounds.push_back(myForeground4);
}

void Foreground::MoveForeground(const float aDeltaTime)
{
	for (auto& f : myForegrounds)
	{
		CU::Vector2<float> newPos = f->GetPosition();

		MoveX(newPos.x, aDeltaTime);
		MoveY(newPos.y, aDeltaTime);	

		f->SetPosition(newPos);
	}
}

void Foreground::MoveX(float& aPosX, const float aDeltaTime)
{
	const float leftBoundry = myX * 0.4f;
	const float rightBoundry = myX * 0.6f;
	const float speed = 20.f;

	if (myMoveLeft)
	{
		aPosX -= speed * aDeltaTime;

		if (aPosX <= leftBoundry)
		{
			myMoveLeft = false;
		}
	}
	else
	{
		aPosX += speed * aDeltaTime;

		if (aPosX >= rightBoundry)
		{
			myMoveLeft = true;
		}
	}
}

void Foreground::MoveY(float& aPosY, const float aDeltaTime)
{
	const float topBoundry = myY * 0.44;
	const float botBoundry = myY * 0.56;
	const float speed = 20.f;

	if (myMoveUp)
	{
		aPosY -= speed * aDeltaTime;

		if (aPosY <= topBoundry)
		{
			myMoveUp = false;
		}
	}
	else
	{
		aPosY += speed * aDeltaTime;

		if (aPosY >= botBoundry)
		{
			myMoveUp = true;
		}
	}
}
