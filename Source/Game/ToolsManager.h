#pragma once
#include "JsonManager.h"

class GlobalServiceProvider;
class Tool;
class GeneralTool;

class ToolsManager
{
public:
	void Init(GlobalServiceProvider* aGlobalServiceProvider);
	void Update();

	static ToolsManager* GetInstance();
	inline GeneralTool* GetGeneralTool() { return myGeneralTool; }

private:
	ToolsManager();
	~ToolsManager();

	static ToolsManager* ourInstance;

	std::vector<Tool*> myTools;

	GeneralTool* myGeneralTool;

	bool myShowNodeEditor;
};