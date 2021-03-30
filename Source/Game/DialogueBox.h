#pragma once
#include "GameObjectTag.h"
#include "nlohmann/json.hpp"
#include <string>
#include <memory>
#include <vector>
#include "Interactable.h"

class Scene;
class Player;
class SpriteWrapper;
class TextWrapper;

class DialogueBox :
    public Interactable
{
public:
    DialogueBox(Scene* aScene);

    void Init(std::string anID);
    virtual void OnInteract(Player* aPlayer) override;
    void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
    void FillSlides(std::string& anAllSlides);

private:
    bool myIsInteracting = false;
    bool myIsFirstVisit = true;
    unsigned int myCurrentSlide{};

    std::shared_ptr<SpriteWrapper> mySprite;
    std::shared_ptr<TextWrapper> myText;
    std::vector<std::string> mySlides;
};

