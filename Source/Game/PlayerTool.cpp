#include "stdafx.h"
#include "PlayerTool.h"

PlayerTool::PlayerTool(const char* aConfigPath, GlobalServiceProvider* aGPC) :
	Tool(aConfigPath, aGPC)
{
}

void PlayerTool::Update()
{
	if (ImGui::BeginMenu("Player Tool"))
	{
		if (ImGui::Button("Save"))
		{
			SaveData();
		}

		for (auto item : myData.items())
		{
			ImGui::PushItemWidth(75.f);

			if (item.key() == "SpritePath")	continue;

			float val = item.value();
			ImGui::InputFloat(item.key().c_str(), &val);
			item.value() = val;
		}

		ImGui::EndMenu();
	}
}
