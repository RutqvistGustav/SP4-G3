#include "stdafx.h"
#include "GeneralTool.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"

GeneralTool::GeneralTool(GlobalServiceProvider* aGSP) :
	myShowColliders(false), myGSP(aGSP)
{
}

void GeneralTool::Update()
{
	if (ImGui::BeginMenu("General Tool"))
	{
		if (ImGui::Checkbox("Show Colliders", &myShowColliders))
		{
			myGSP->GetGameMessenger()->Send(GameMessage::ShowColliders, &myShowColliders);
		}
		ImGui::EndMenu();
	}
}
