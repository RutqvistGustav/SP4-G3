#pragma once

class Enemy;
class Scene;

class EnemyFactory
{
public:
	enum class EnemyType
	{
		Flying,
		Hunter,
		JetPack,
		Zombie
	};
	EnemyFactory() = delete;
	static std::unique_ptr<Enemy> CreateEnemy(EnemyType aType, Scene* aScene);
};

