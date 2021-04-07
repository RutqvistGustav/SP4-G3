#pragma once

#include "Enemy.h"

class Zombie :
    public Enemy
{
public:

    Zombie(Scene* aScene, EnemyType anEnemyType = EnemyType::Zombie, const std::string& aType = "Zombie");
    ~Zombie();

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    virtual void Movement(const float aDeltaTime);
    virtual void IdleMovement(const float aDeltaTime);

    virtual bool CheckIdle();
    void PlayTriggeredSoundOnce();

private:
    bool myHasSoundPlayOnce = false;
};
