#pragma once

#include "UpdateContext.h"
#include "RenderContext.h"

#include <fstream>
#include <memory>

class CGameWorld;

namespace CommonUtilities
{
	class Input;
	class Timer;
}

class AudioManager;
class JsonManager;
class RenderManager;
class SceneManager;
class WeaponFactory;
class InputInterface;
class ControllerInput;
class GameMessenger;
class GlobalServiceProvider;

class CGame
{
public:

	CGame();
	~CGame();

	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);

	static void QueueSetResolution(int aWidth, int aHeight);

private:

	void InitCallBack();
	void UpdateCallBack();

	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:

	// NOTE: Order is important

	std::unique_ptr<GlobalServiceProvider> myGlobalServiceProvider;

	std::unique_ptr<GameMessenger> myGameMessenger;
	std::unique_ptr<WeaponFactory> myWeaponFactory;
	std::unique_ptr<JsonManager> myJsonManager;
	std::unique_ptr<AudioManager> myAudioManager;

	std::unique_ptr<RenderManager> myRenderManager;

	std::unique_ptr<InputInterface> myInputInterface;
	std::unique_ptr<ControllerInput> myControllerInput;
	std::unique_ptr<CommonUtilities::Input> myInput;

	std::unique_ptr<CommonUtilities::Timer> myTimer;

	UpdateContext myUpdateContext;
	RenderContext myRenderContext;

	std::unique_ptr<SceneManager> mySceneManager;
};
