#include "stdafx.h"
#include "DialogueBox.h"

#include "TextWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "RenderContext.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

DialogueBox::DialogueBox(Scene* aScene)
	: Interactable(aScene)
{
}

void DialogueBox::Init(std::string anID)
{
	myText = std::make_shared<TextWrapper>("Text/arial.txt", Tga2D::EFontSize_18, 0);

	nlohmann::json data;
	std::ifstream file("Dialog/Main.json"); // TODO switch to anID.

	data = nlohmann::json::parse(file);
	file.close();

	myText->SetText(data.at("PlayerTest1"));
	for ()
	{

	}
}

void DialogueBox::OnInteract(Player* aPlayer)
{
	myIsInteracting = true;
	
	if (IsInteracting(aPlayer))
	{
		// go to next slide or exit if last slide
	}
	
}

void DialogueBox::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (myIsInteracting)
	{
		//aRenderQueue->Queue(RenderCommand(myText));
	}
}
