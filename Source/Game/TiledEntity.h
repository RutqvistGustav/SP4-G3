#pragma once

#include <Vector2.hpp>

#include <unordered_map>

class TiledEntity
{
public:

	TiledEntity(const CU::Vector2<float>& aPosition, const CU::Vector2<float>& aSize, const std::unordered_map<std::string, std::string>& someProperties);

	bool HasProperty(const std::string& aKey) const;
	const std::string& GetProperty(const std::string& aKey) const;

	inline const CU::Vector2<float>& GetPosition() const { return myPosition; }
	inline const CU::Vector2<float>& GetSize() const { return mySize; }

	inline const std::string& GetType() const { return GetProperty("Type"); }
	inline const std::string& GetSubType() const { return GetProperty("SubType"); }

private:

	CU::Vector2<float> myPosition;
	CU::Vector2<float> mySize;

	std::unordered_map<std::string, std::string> myProperties;

};
