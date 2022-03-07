#include "stdafx.h"
#include "EnemyTool.h"

EnemyTool::EnemyTool(const char* aConfigPath, GlobalServiceProvider* aGPC) :
	Tool(aConfigPath, aGPC)
{
}

void EnemyTool::Update()
{
	if (ImGui::BeginMenu("Enemy Tool"))
	{
		if (ImGui::Button("Save"))
		{
			SaveData();
		}
		
		for (auto item : myData.items())
		{
			if (ImGui::BeginMenu(item.key().c_str()))
			{
				for (auto i : item.value().items())
				{
					ImGui::PushItemWidth(75.f);
					float val = i.value();
					ImGui::InputFloat(i.key().c_str(), &val);
					i.value() = val;
				}
				ImGui::EndMenu();
			}
		}
		ImGui::EndMenu();
	}
}
