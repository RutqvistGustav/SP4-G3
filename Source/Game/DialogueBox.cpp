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

#include "SpriteSheetAnimation.h"

#include <fstream>
#include <string>

DialogueBox::DialogueBox(Scene* aScene)
	: Interactable(aScene)
{
	myIndicatorAnimator = std::make_unique<SpriteSheetAnimation>(GetScene()->GetGlobalServiceProvider()->GetJsonManager(), "Animations/BouncingArrow.json");
	myIndicatorAnimator->SetState("idle");
	myIndicatorAnimator->SetIsLooping(true);

	myIndicator = std::make_shared<SpriteWrapper>();
	myIndicator->SetLayer(GameLayer::HUD);
	myIndicatorAnimator->ApplyToSprite(myIndicator);
}

void DialogueBox::Init(std::string anID)
{
	GameObject::Init();

	const JsonData& dialogData = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("Dialog/Main.json");

	std::string dialogString;
	if (dialogData.find(anID) != dialogData.end())
	{
		dialogString = dialogData.at(anID);
	}
	else
	{
		// NOTE: No dialog found, should not happen in production
		dialogString = "This should not happen :/";

		ERROR_PRINT("Could not find dialog with id %s", anID.c_str());
	}

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

void DialogueBox::SetPosition(const CU::Vector2<float> aPosition)
{
	Interactable::SetPosition(aPosition);

	const CU::Vector2<float> offset = CU::Vector2<float>(0.0f, (myIndicator->GetSize().y + GetTriggerSize().y) * -0.5f);
	myIndicator->SetPosition(aPosition + offset);
}

void DialogueBox::TriggerExit(GameObject* aGameObject)
{
	Interactable::TriggerExit(aGameObject);

	myCurrentPage = -1;
}

void DialogueBox::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	Interactable::Update(aDeltaTime, anUpdateContext);

	myIndicatorAnimator->Update(aDeltaTime);
	myIndicatorAnimator->ApplyToSprite(myIndicator);
}

void DialogueBox::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (ShouldShowDialog())
	{
		aRenderQueue->Queue(RenderCommand(mySprite));
		aRenderQueue->Queue(RenderCommand(myText));
	}

	if (InRange())
	{
		aRenderQueue->Queue(RenderCommand(myIndicator));
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
