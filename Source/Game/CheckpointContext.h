#pragma once

#include "CheckpointObjectData.h"

#include <memory>
#include <string>
#include <unordered_map>

struct CheckpointObjectData;

class CheckpointContext
{
public:

	template <typename T>
	T* NewData(const std::string& anObjectKey)
	{
		static_assert(sizeof(T) > 0, "Incomplete type not allowed!");
		static_assert(std::is_base_of_v<CheckpointObjectData, T>, "Must derive from CheckpointObjectData!");

		std::unique_ptr<T> objectData = std::make_unique<T>();
		T* rawObjectData = objectData.get();

		mySavedObjects.insert(std::make_pair(anObjectKey, std::move(objectData)));

		return rawObjectData;
	}

	template <typename T>
	T* GetData(const std::string& anObjectKey)
	{
		static_assert(sizeof(T) > 0, "Incomplete type not allowed!");
		static_assert(std::is_base_of_v<CheckpointObjectData, T>, "Must derive from CheckpointObjectData!");

		auto it = mySavedObjects.find(anObjectKey);
		if (it != mySavedObjects.end())
		{
			return static_cast<T*>(it->second.get());
		}

		return nullptr;
	}

	bool HasData()
	{
		return mySavedObjects.size() > 0;
	}

	void Clear()
	{
		mySavedObjects.clear();
	}

private:

	std::unordered_map<std::string, std::unique_ptr<CheckpointObjectData>> mySavedObjects;

};
