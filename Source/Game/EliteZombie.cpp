#include "stdafx.h"
#include "EliteZombie.h"

#include "SpriteWrapper.h"

EliteZombie::EliteZombie(Scene* aScene)
	: Zombie(aScene, "EliteZombie")
{
	// NOTE: DEBUG: Temp to see difference
	mySprite->SetColor({0.5f, 0.0f, 0.0f, 1.0f});
}
