#include "stdafx.h"
#include "CollisionFilter.h"

CollisionFilter::CollisionFilter() = default;

void CollisionFilter::AddFilter(const CollisionFilterKey& aFilterKey)
{
	myIgnoredCollisions.insert(aFilterKey);
}

bool CollisionFilter::IsIgnored(const CollisionFilterKey& aFilterKey)
{
	return myIgnoredCollisions.find(aFilterKey) != myIgnoredCollisions.end();
}
