#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>

CGameWorld::CGameWorld()
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


void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
}

void CGameWorld::Render()
{
	myTga2dLogoSprite->Render();
}