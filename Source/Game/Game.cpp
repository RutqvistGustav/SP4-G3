#include "stdafx.h"
#include "Game.h"
#include "GameWorld.h"

#include "Camera.h"

#include <Xinput.h>
#include "ControllerInput.h"
#include "InputInterface.h"

#include "Metrics.h"

#include "AudioManager.h"
#include "RenderManager.h"
#include "SceneManager.h"

#include "JsonManager.h"
#include "WeaponFactory.h"

#include "MainMenu.h"
#include "StartupScene.h"

#include "GlobalServiceProvider.h"
#include "GameMessenger.h"

#include <InputManager.h>
#include <Timer.h>

#include <tga2d/error/error_manager.h>
#include "GameScene.h"

using namespace std::placeholders;

#ifdef _DEBUG
#pragma comment(lib,"TGA2D_Debug.lib")
#pragma comment(lib,"CommonUtilities_Debug.lib")
std::wstring BUILD_NAME = L"Debug";
#endif // DEBUG
#ifdef _RELEASE
#pragma comment(lib,"TGA2D_Release.lib")
#pragma comment(lib,"CommonUtilities_Release.lib")
std::wstring BUILD_NAME = L"Release";
#endif // DEBUG
#ifdef _RETAIL
#pragma comment(lib,"TGA2D_Retail.lib")
#pragma comment(lib,"CommonUtilities_Retail.lib")
std::wstring BUILD_NAME = L"Retail";
#endif // DEBUG
#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "XInput9_1_0.lib")

CGame::CGame()
	: myInput(new CU::Input())
	, myTimer(new CU::Timer())
	, myControllerInput(new ControllerInput())
{}

CGame::~CGame() = default;

LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	lParam;
	wParam;
	hWnd;

	if (myInput->UpdateEvents(message, wParam, lParam))
		return 0;

	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	}

	return 0;
}


bool CGame::Init(const std::wstring& aVersion, HWND /*aHWND*/)
{
	Tga2D::SEngineCreateParameters createParameters;

	createParameters.myInitFunctionToCall = [this] {InitCallBack(); };
	createParameters.myWinProcCallback = [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {return WinProc(hWnd, message, wParam, lParam); };
	createParameters.myUpdateFunctionToCall = [this] {UpdateCallBack(); };
	createParameters.myApplicationName = L"TGA 2D " + BUILD_NAME + L"[" + aVersion + L"] ";

#ifndef _DEBUG

	// NOTE: Fullscreen
	RECT desktopRect;
	HWND desktopWindow = GetDesktopWindow();
	GetWindowRect(desktopWindow, &desktopRect);

	createParameters.myStartInFullScreen = true;
	createParameters.myWindowWidth = static_cast<unsigned short>(desktopRect.right);
	createParameters.myWindowHeight = static_cast<unsigned short>(desktopRect.bottom);
	createParameters.myRenderWidth = createParameters.myWindowWidth;
	createParameters.myRenderHeight = createParameters.myWindowHeight;

#endif
	
	const CommonUtilities::Vector2<float> referenceSize = Metrics::GetReferenceSize();
	createParameters.myTargetWidth = static_cast<unsigned short>(referenceSize.x);
	createParameters.myTargetHeight = static_cast<unsigned short>(referenceSize.y);

	// NOTE: GD Test background color
	// R: 33 => 0.129
	// G: 24 => 0.094
	// B: 25 => 0.098

	// createParameters.myClearColor = Tga2D::CColor(0.129f, 0.094f, 0.098f, 1.0f);
	createParameters.myClearColor = Tga2D::CColor(0.0f, 0.0f, 0.0f, 1.0f);

	//createParameters.myPreferedMultiSamplingQuality = Tga2D::EMultiSamplingQuality_High;
	createParameters.myActivateDebugSystems = Tga2D::eDebugFeature_Fps |
		Tga2D::eDebugFeature_Mem |
		Tga2D::eDebugFeature_Drawcalls |
		Tga2D::eDebugFeature_Cpu |
		Tga2D::eDebugFeature_Filewatcher |
		Tga2D::eDebugFeature_OptimiceWarnings;

	if (!Tga2D::CEngine::Start(createParameters))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return false;
	}

	// End of program
	return true;
}

void CGame::QueueSetResolution(int aWidth, int aHeight)
{
	// NOTE: TODO: If multithreading this need to be changed
	Tga2D::CEngine::GetInstance()->Resize(VECTOR2UI(aWidth, aHeight));
}

void CGame::InitCallBack()
{
	myAudioManager = std::make_unique<AudioManager>();
	myAudioManager->SetMasterVolume(0.5f);
	myAudioManager->SetSfxVolume(1.0f);
	myAudioManager->SetMusicVolume(1.0f);

	myJsonManager = std::make_unique <JsonManager>();
	myWeaponFactory = std::make_unique<WeaponFactory>(myJsonManager.get());
	myGameMessenger = std::make_unique<GameMessenger>();
	myInputInterface = std::make_unique<InputInterface>(myInput.get(), myControllerInput.get());


	myGlobalServiceProvider = std::make_unique<GlobalServiceProvider>(myAudioManager.get(), myJsonManager.get(), myWeaponFactory.get(), myInputInterface.get(), myGameMessenger.get());

	mySceneManager = std::make_unique<SceneManager>(myGlobalServiceProvider.get());

	//myGameWorld->Init();
	myRenderManager = std::make_unique<RenderManager>();


	// NOTE: Fill myUpdateContext & myRenderContext after needs
	myUpdateContext.myInputInterface = myInputInterface.get();
	myUpdateContext.myInput = myInput.get();

	mySceneManager->Transition(std::make_unique<StartupScene>());
}

void CGame::UpdateCallBack()
{
	// NOTE: Ready for multithreading
	RenderQueue* const updateQueue = myRenderManager->GetUpdateQueue();

	float deltaTime = myTimer->GetDeltaTime();
	// NOTE: Cap high delta time values, will result in the game lagging behind when running slower than 30 fps but prevents spikes in delta time
	// that can cause all sorts of problems.
	if (deltaTime > 1.0f / 30.0f)
	{
		deltaTime = 1.0f / 30.0f;
	}

	myTimer->Update();
	myControllerInput->UpdateControllerState(deltaTime);

	mySceneManager->Update(deltaTime, myUpdateContext);
	mySceneManager->Render(updateQueue, myRenderContext);

	// Rendering
	myRenderManager->Render();
	
	myRenderManager->SwapBuffers();
	myRenderManager->SetPan(mySceneManager->GetCamera()->GetPositionWithModifiers() * -1.0f);

	myInput->ResetFrame();
}
