#pragma once

#include "CollisionManager.h"

struct CollisionInfo;

class CollisionListener
{
public:

	virtual void OnEnter(const CollisionInfo& someCollisionInfo);
	virtual void OnStay(const CollisionInfo& someCollisionInfo);
	virtual void OnExit(const CollisionInfo& someCollisionInfo);

};
