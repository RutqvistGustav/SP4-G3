#include "stdafx.h"
#include "TiledEntity.h"

TiledEntity::TiledEntity(const CU::Vector2<float>& aPosition, const std::unordered_map<std::string, std::string>& someProperties) :
	myPosition(aPosition),
	myProperties(someProperties)
{}

bool TiledEntity::HasProperty(const std::string & aKey) const
{
	return myProperties.find(aKey) != myProperties.end();
}

const std::string& TiledEntity::GetProperty(const std::string& aKey) const
{
	assert(HasProperty(aKey) && "Trying to fetch non-existant property!");

	return myProperties.at(aKey);
}
