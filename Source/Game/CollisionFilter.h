#pragma once

#include "CollisionLayer.h"

#include <set>

class CollisionFilterKey
{
public:

	CollisionFilterKey(CollisionLayer::Layer aLayerA, CollisionLayer::Layer aLayerB)
	{
		if (aLayerA <= aLayerB)
		{
			myLayerA = aLayerA;
			myLayerB = aLayerB;
		}
		else
		{
			myLayerA = aLayerB;
			myLayerB = aLayerA;
		}
	}

	friend inline bool operator<(const CollisionFilterKey& aFilterA, const CollisionFilterKey& aFilterB)
	{
		if (aFilterA.myLayerA < aFilterB.myLayerA)
		{
			return true;
		}

		return aFilterA.myLayerA == aFilterB.myLayerA && aFilterA.myLayerB < aFilterB.myLayerB;
	}

private:

	CollisionLayer::Layer myLayerA;
	CollisionLayer::Layer myLayerB;
};

class CollisionFilter
{
public:

	CollisionFilter();

	void AddFilter(const CollisionFilterKey& aFilterKey);

	bool IsIgnored(const CollisionFilterKey& aFilterKey);

private:

	std::set<CollisionFilterKey> myIgnoredCollisions;

};
