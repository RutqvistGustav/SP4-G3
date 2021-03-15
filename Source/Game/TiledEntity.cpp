#include "stdafx.h"
#include "TiledEntity.h"

TiledEntity::TiledEntity(const CU::Vector2<float>& aPosition, const std::string& aType, const std::string& aSubType) :
	myPosition(aPosition),
	myType(aType),
	mySubType(aSubType)
{}
