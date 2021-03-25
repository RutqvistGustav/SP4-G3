#pragma once

#include "AABB.h"

class DynamicTexture;
class TiledCollision;
class TiledParser;
class SpriteWrapper;
class RenderQueue;
class GameObject;

class Minimap
{
public:

	enum class MapObjectType
	{
		Player,
		Enemy,

		Collectable,
	};

	struct MapObject
	{
		GameObject* myGameObject;
		MapObjectType myType;
	};

	Minimap(TiledParser* aTiledParser, TiledCollision* aTiledCollision);
	~Minimap();

	void Update(float aDeltaTime);
	void Render(RenderQueue* const aRenderQueue);

	void AddObject(GameObject* aGameObject, MapObjectType aType);
	void RemoveObject(GameObject* aGameObject);

	void SetGameView(const AABB& aGameView);
	void SetUIView(const AABB& aUIView);

private:

	void ConfigureSpriteForObject(SpriteWrapper* aSprite, const MapObject& anObject);

	void UpdateTexture();
	void UpdateView();

private:

	TiledParser* myTiledParser;
	TiledCollision* myTiledCollision;

	std::unique_ptr<DynamicTexture> myMapTexture;
	std::shared_ptr<SpriteWrapper> myMapSprite;

	std::shared_ptr<SpriteWrapper> myObjectSprite;
	std::vector<MapObject> myObjects;

	AABB myGameView;
	AABB myUIView;

};
