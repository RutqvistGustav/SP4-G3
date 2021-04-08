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

    void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    virtual void OnInteract(Player* aPlayer) override;

protected:

    virtual void TriggerExit(GameObject* aGameObject) override;

private:

    void FillSlides(const std::string& aDialogText);

    inline bool ShouldShowDialog() const { return myCurrentPage >= 0; }

private:

    int myCurrentPage{ -1 };

    std::shared_ptr<TextWrapper> myText;
    std::vector<std::string> myPages;

};
