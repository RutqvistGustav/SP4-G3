#pragma once

#include "EnemyType.h"

class Enemy;
class Scene;

class EnemyFactory
{
public:

	EnemyFactory() = delete;
	static std::unique_ptr<Enemy> CreateEnemy(EnemyType aType, Scene* aScene);

};

