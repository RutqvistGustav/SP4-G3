#pragma once

class InputKeyMap
{
public:
	static InputKeyMap* Get();

	void Init();

	const int GetKey(const std::string& aKey)
	{
		for (auto& key : keyMap)
		{
			if (key.first == aKey) return key.second;
		}

		return -1;
	}

private:
	static InputKeyMap* ourInstance;

	std::vector<std::pair<std::string, int>> keyMap;
};
