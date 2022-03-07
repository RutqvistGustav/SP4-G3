#include "stdafx.h"
#include "WeaponTool.h"

WeaponTool::WeaponTool(const char* aConfigPath, GlobalServiceProvider* aGPC) :
	Tool(aConfigPath, aGPC)
{
}

void WeaponTool::Update()
{
	if (ImGui::BeginMenu("Weapon Tool"))
	{
		if (ImGui::Button("Save"))
		{
			SaveData();
		}
		
		for (auto item : myData.items())
		{
			for (auto i : item.value().items())
			{
				ImGui::PushItemWidth(75.f);
		
				if (i.key() == "type") continue;
		
				if (i.key() == "Berserk" || i.key() == "SniperShot")
				{
					if (ImGui::BeginMenu(i.key().c_str()))
					{
						for (auto j : i.value().items())
						{
							ImGui::PushItemWidth(75.f);
							float val = j.value();
							ImGui::InputFloat(j.key().c_str(), &val);
							j.value() = val;
						}
						ImGui::EndMenu();
					}
					continue;
				}
		
				float val = i.value();
				ImGui::InputFloat(i.key().c_str(), &val);
				i.value() = val;
			}
		}
		
		ImGui::EndMenu();
	}
}
