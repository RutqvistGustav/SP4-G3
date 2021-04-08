#include "stdafx.h"
#include "DialogueBox.h"

#include "GlobalServiceProvider.h"
#include "JsonManager.h"
#include "SpriteWrapper.h"
#include "TextWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Player.h"

#include "Metrics.h"

#include <fstream>
#include <string>

DialogueBox::DialogueBox(Scene* aScene)
	: Interactable(aScene)
{}

void DialogueBox::Init(std::string anID)
{
	GameObject::Init();

	const JsonData& dialogData = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("Dialog/Main.json");

	assert(dialogData.count(anID) > 0 && "Could not find dialog with ID!");

	const std::string dialogString = dialogData.at(anID);

	FillSlides(dialogString);

	myText = std::make_shared<TextWrapper>("Text/arial.ttf", Tga2D::EFontSize_30, 0);
	myText->SetPanStrengthFactor(0.0f);
	myText->SetPivot({ 0.5f, 0.5f });
	myText->SetPosition({ Metrics::GetReferenceSize().x * 0.5f, 1000.0f });
	myText->SetLayer(GameLayer::HUD + 1);

	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/HealthBar.dds");
	mySprite->SetPanStrengthFactor(0.0f);
	mySprite->SetPosition({ Metrics::GetReferenceSize().x * 0.5f, 1000.0f });
	mySprite->SetLayer(GameLayer::HUD);
}

void DialogueBox::OnInteract(Player* aPlayer)
{
	++myCurrentPage;

	if (myCurrentPage < static_cast<int>(myPages.size()))
	{
		myText->SetText(myPages[myCurrentPage]);
		aPlayer->SetControllerActive(false);
	}
	else
	{
		myCurrentPage = -1;
		aPlayer->SetControllerActive(true);
	}
}

void DialogueBox::TriggerExit(GameObject* aGameObject)
{
	Interactable::TriggerExit(aGameObject);

	myCurrentPage = -1;
}

void DialogueBox::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (ShouldShowDialog())
	{
		aRenderQueue->Queue(RenderCommand(mySprite));
		aRenderQueue->Queue(RenderCommand(myText));
	}
}

void DialogueBox::FillSlides(const std::string& aDialogText)
{
	myPages.clear();

	const std::string delimiter = "%b";
	std::size_t lastIndex = 0;
	std::size_t foundIndex = 0;
	
	do {
		foundIndex = aDialogText.find(delimiter, lastIndex);

		myPages.push_back(aDialogText.substr(lastIndex, foundIndex != std::string::npos ? foundIndex - lastIndex : foundIndex));
		lastIndex = foundIndex + delimiter.length();
	} while (foundIndex != std::string::npos);
}
