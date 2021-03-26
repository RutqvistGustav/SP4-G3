#pragma once

class Enemy;
class Scene;

class EnemyFactory
{
public:
	enum class EnemyType
	{
		Zombie,
		EliteZombie
	};
	EnemyFactory() = delete;
	static std::unique_ptr<Enemy> CreateEnemy(EnemyType aType, Scene* aScene);
};

