#include "stdafx.h"
#include "DialogueBox.h"

#include "SpriteWrapper.h"
#include "TextWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Player.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

DialogueBox::DialogueBox(Scene* aScene)
	: Interactable(aScene)
{}

void DialogueBox::Init(std::string anID)
{
	GameObject::Init();

	nlohmann::json data;
	std::ifstream file(anID); // TODO switch to anID.

	data = nlohmann::json::parse(file);
	file.close();

	std::string allSlides = data.at("PlayerTest1");
	FillSlides(allSlides);

	myText = std::make_shared<TextWrapper>("Text/arial.ttf", Tga2D::EFontSize_60, 0);
	myText->SetText(mySlides[myCurrentSlide]);
	myText->SetPanStrengthFactor(0.0f);
	myText->SetPosition({ 800.0f, 500.0f });
	myText->SetLayer(999);
	myText->SetColor({ 1.0f,1.0f,0.0f,1.0f });

	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/HealthBar.dds");
	mySprite->SetPanStrengthFactor(0.0f);
	mySprite->SetPosition({ 500.0f,500.0f });

	SetTriggerRadius(50.0f);
}

void DialogueBox::OnInteract(Player* aPlayer)
{
	if (IsInteracting(aPlayer) && myIsFirstVisit == false)
	{
		++myCurrentSlide;
		if (myCurrentSlide == mySlides.size())
		{
			aPlayer->SetControllerActive(true);
			myIsInteracting = false;
			myIsFirstVisit = true;
			myCurrentSlide = 0;
		}
	}
	else
	{
		aPlayer->SetControllerActive(false);
		myIsInteracting = true; 
		myIsFirstVisit = false;
	}
	myText->SetText(mySlides[myCurrentSlide]);
}

void DialogueBox::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (myIsInteracting)
	{
		aRenderQueue->Queue(RenderCommand(mySprite));
		aRenderQueue->Queue(RenderCommand(myText));
	}
}

void DialogueBox::FillSlides(std::string& anAllSlides)
{
	std::string slide;
	for (int index = 0; index < anAllSlides.size(); ++index)
	{
		if (anAllSlides[index] == '%')
		{
			mySlides.push_back(slide);
			slide = "";
		}
		else
		{
			slide += anAllSlides[index];
		}
	}
	mySlides.push_back(slide);
}
