#include "stdafx.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "Zombie.h"
#include <memory>

std::unique_ptr<Enemy> EnemyFactory::CreateEnemy(EnemyType aType, Scene* aScene)
{
	switch (aType)
	{
	case(EnemyType::Flying):
	{
		return nullptr;
		break;
	}
	case(EnemyType::Hunter):
	{
		return nullptr;
		break;
	}
	case(EnemyType::JetPack):
	{
		return nullptr;
		break;
	}
	case(EnemyType::Zombie):
	{
		return std::make_unique<Zombie>(aScene);
		break;
	}
		
	}
}
