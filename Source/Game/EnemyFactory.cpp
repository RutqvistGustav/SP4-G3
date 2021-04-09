#include "stdafx.h"
#include "EnemyFactory.h"
#include <memory>

#include "Enemy.h"
#include "Zombie.h"
#include "EliteZombie.h"

std::unique_ptr<Enemy> EnemyFactory::CreateEnemy(EnemyType aType, Scene* aScene)
{
	switch (aType)
	{
	default:
		assert(false && "Invalid enemy type!");
	case(EnemyType::Zombie):
		return std::make_unique<Zombie>(aScene);

	case(EnemyType::EliteZombie):
		return std::make_unique<EliteZombie>(aScene);
	}
}
