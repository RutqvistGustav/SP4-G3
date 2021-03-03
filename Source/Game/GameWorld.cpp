#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include <InputManager.h>

#include "Player.h"

CGameWorld::CGameWorld()
	: myPlayer(new Player())
{
	myTga2dLogoSprite = nullptr;
}

CGameWorld::~CGameWorld() 
{
	delete myTga2dLogoSprite;
	myTga2dLogoSprite = nullptr;
}

void CGameWorld::Init()  
{
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
}


void CGameWorld::Update(float aDeltaTime, CU::Input* anInput)
{ 	
	myPlayer->Update(aDeltaTime, anInput);
}

void CGameWorld::Render()
{
	myTga2dLogoSprite->Render();
}