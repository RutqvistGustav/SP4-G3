#pragma once

#include <Vector2.hpp>

class TiledEntity
{
public:

	TiledEntity(const CU::Vector2<float>& aPosition, const std::string& aType, const std::string& aSubType);

	inline const CU::Vector2<float>& GetPosition() const { return myPosition; }

	inline const std::string& GetType() const { return myType; }
	inline const std::string& GetSubType() const { return mySubType; }

private:

	CU::Vector2<float> myPosition;

	std::string myType;
	std::string mySubType;

};
