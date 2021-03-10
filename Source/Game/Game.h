#pragma once

#include "UpdateContext.h"
#include "RenderContext.h"

#include <fstream>
#include <memory>

namespace CommonUtilities
{
	class Input;
	class Timer;
}

class JsonManager;
class RenderManager;
class SceneManager;
class WeaponFactory;
class InputInterface;
class ControllerInput;

class CGame
{
public:

	CGame();
	~CGame();

	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);

private:

	void InitCallBack();
	void UpdateCallBack();

	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	std::unique_ptr<RenderManager> myRenderManager;
	std::unique_ptr<JsonManager> myJsonManager;
	std::unique_ptr<WeaponFactory> myWeaponFactory;
	std::unique_ptr<SceneManager> mySceneManager;

	UpdateContext myUpdateContext;
	RenderContext myRenderContext;

	std::unique_ptr<InputInterface> myInputInterface;
	std::unique_ptr<ControllerInput> myControllerInput;
	std::unique_ptr<CommonUtilities::Input> myInput;

	std::unique_ptr<CommonUtilities::Timer> myTimer;
};
