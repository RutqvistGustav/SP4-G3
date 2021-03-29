#include "stdafx.h"
#include "Background.h"
#include "SpriteWrapper.h"
#include "Metrics.h"
#include "RenderCommand.h";

void Background::Init()
{
	myX = Metrics::GetReferenceSize().x;
	myY = Metrics::GetReferenceSize().y;
}

void Background::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	MoveForeground(aDeltaTime);
}

void Background::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& f : myForegrounds)
	{
		RenderCommand renderCommand = RenderCommand(f);
		aRenderQueue->Queue(renderCommand);
	}
}

void Background::CreateForeground()
{
	myForeground1 = std::make_shared<SpriteWrapper>("");
	myForeground1->SetPosition(CU::Vector2(myX * 0.3f, myY * 1.0f));
	myForegrounds.push_back(myForeground1);

	myForeground2 = std::make_shared<SpriteWrapper>("");
	myForeground2->SetPosition(CU::Vector2(myX * 0.4f, myY * .9f));
	myForegrounds.push_back(myForeground2);

	myForeground3 = std::make_shared<SpriteWrapper>("");
	myForeground3->SetPosition(CU::Vector2(myX * 0.5f, myY * .8f));
	myForegrounds.push_back(myForeground3);

	myForeground4 = std::make_shared<SpriteWrapper>("");
	myForeground4->SetPosition(CU::Vector2(myX * 0.6f, myY * 1.1f));
	myForegrounds.push_back(myForeground4);
}

void Background::MoveForeground(const float aDeltaTime)
{

}
