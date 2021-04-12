#pragma once

#include "AABB.h"

class GameObject;

struct CollisionItem
{
	enum class Type
	{
		Tile,
		Collider,
		HalfTile,
	};

	Type myType;
	AABB myAABB;

	// NOTE: Only set & valid if myType == Type::Collider
	GameObject* myGameObject{};
};
