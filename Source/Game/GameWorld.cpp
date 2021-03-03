#include "stdafx.h"
#include "GameWorld.h"

#include "Player.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include "SpriteWrapper.h"

#include <tga2d/sprite/sprite.h>
#include <InputManager.h>

CGameWorld::CGameWorld()
	: myPlayer(new Player())
{ }

CGameWorld::~CGameWorld() = default;

void CGameWorld::Init()  
{
	myTga2dLogoSprite = std::make_shared<SpriteWrapper>("Sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPosition(Metrics::GetReferenceSize() * 0.5f);
}

void CGameWorld::Update(float aDeltaTime, CU::Input* anInput)
{ 	
	myPlayer->Update(aDeltaTime, anInput);
}

void CGameWorld::Render(RenderQueue* aRenderQueue)
{
	aRenderQueue->Queue(RenderCommand(myTga2dLogoSprite));
}
