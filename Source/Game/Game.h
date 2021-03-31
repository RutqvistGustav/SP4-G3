#pragma once

#include "UpdateContext.h"
#include "RenderContext.h"

#include <fstream>
#include <memory>

#define WM_MESSAGE_TOGGLE_FULLSCREEN WM_USER + 1
#define WM_MESSAGE_SET_RESOLUTION WM_USER + 2

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
	void QueueSetFullscreen(bool aFullscreen);
	void QueueSetResolution(unsigned int aWidth, unsigned int aHeight);

	static CGame* GetInstance() { return ourInstance; }

private:

	void InitCallBack();
	void UpdateCallBack();

	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	// NOTE: Order is important
	static CGame* ourInstance;

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
