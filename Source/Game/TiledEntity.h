#pragma once

#include <Vector2.hpp>

#include <unordered_map>

class TiledEntity
{
public:

	TiledEntity(const CU::Vector2<float>& aPosition, const std::unordered_map<std::string, std::string>& someProperties);

	bool HasProperty(const std::string& aKey) const;
	const std::string& GetProperty(const std::string& aKey) const;

	inline const CU::Vector2<float>& GetPosition() const { return myPosition; }

	inline const std::string& GetType() const { return GetProperty("Type"); }
	[[deprecated("use GetProperty instead!")]] inline const std::string& GetSubType() const { return GetProperty("SubType"); }

private:

	CU::Vector2<float> myPosition;

	std::unordered_map<std::string, std::string> myProperties;

};
