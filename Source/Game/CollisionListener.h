#pragma once
#include "CollisionManager.h"
#include "TileType.h"
#include <any>

class Scene;
class GameObject;

class CollisionListener
{
public:
	CollisionListener(Scene* aScene);
	~CollisionListener();


	virtual void Init(Scene* aScene);
	virtual void OnCollision(std::any aGameObject);
	virtual void OnCollision(TileType aTileType, CU::Vector2<float> anOffset);

protected:

	std::shared_ptr<Collider> myColliderL;
	Scene* myLScene;

};