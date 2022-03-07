#include "stdafx.h"
#include "ToolsManager.h"
#include "GlobalServiceProvider.h"
#include <filesystem>
#include "GameMessenger.h"

//Tools
#include "GeneralTool.h"
#include "PlayerTool.h"
#include "EnemyTool.h"
#include "WeaponTool.h"

#include "NodeEditorManager.h"

ToolsManager* ToolsManager::ourInstance = nullptr;

ToolsManager::ToolsManager() :
	  myGeneralTool(nullptr)
	, myShowNodeEditor(false)
{
}

ToolsManager::~ToolsManager()
{
	for (auto* tool : myTools)
	{
		delete tool;
		tool = nullptr;
	}
}

void ToolsManager::Init(GlobalServiceProvider* aGSP)
{
	myGeneralTool = new GeneralTool(aGSP);

	myTools.push_back(myGeneralTool);
	myTools.push_back(new PlayerTool("JSON/Player.json", aGSP));
	myTools.push_back(new EnemyTool("JSON/EnemyTypes.json", aGSP));
	myTools.push_back(new WeaponTool("JSON/Weapons.json", aGSP));
}

void ToolsManager::Update()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Tools"))
		{
			for (auto& tool : myTools)
			{
				tool->Update();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("NodeEditor"))
		{
			ImGui::Checkbox("Show", &myShowNodeEditor);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if (myShowNodeEditor)
	{
		NodeEditorManager::Get()->Update();
	}
}

ToolsManager* ToolsManager::GetInstance()
{
	if (!ourInstance)
	{
		ourInstance = new ToolsManager();
	}
	return ourInstance;
}
