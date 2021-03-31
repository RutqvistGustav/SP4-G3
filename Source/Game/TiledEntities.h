#pragma once

class TiledEntity;
class TiledParser;
class GameMessenger;
class Scene;

class TiledEntities
{
public:
	TiledEntities(const TiledParser* aParser, Scene* aScene);

	const TiledEntity* FindEntityWithType(const std::string& aType);
	void SpawnEntities();

private:

	const TiledParser* myParser;
	Scene* myScene;
	
};

