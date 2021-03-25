#pragma once

class TiledParser;
class GameMessenger;
class Scene;

class TiledEntities
{
public:
	TiledEntities(const TiledParser* aParser, Scene* aScene);

	void SpawnEntities();

private:

	const TiledParser* myParser;
	Scene* myScene;
	
};

