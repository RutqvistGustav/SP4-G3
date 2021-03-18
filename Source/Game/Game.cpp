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
#include "GameScene.h"

#include <InputManager.h>
#include <Timer.h>

#include <tga2d/error/error_manager.h>

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
{

}


CGame::~CGame()
{

}

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
	
	const CommonUtilities::Vector2<float> referenceSize = Metrics::GetReferenceSize();
	createParameters.myTargetWidth = static_cast<unsigned short>(referenceSize.x);
	createParameters.myTargetHeight = static_cast<unsigned short>(referenceSize.y);

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

void CGame::InitCallBack()
{
	myAudioManager = std::make_unique<AudioManager>();
	myAudioManager->SetMasterVolume(0.2f); // TODO: DEBUG: Set low master volume
	myRenderManager = std::make_unique<RenderManager>();

	myInputInterface = std::make_unique<InputInterface>(myInput.get(), myControllerInput.get());
	myJsonManager = std::make_unique <JsonManager>();
	myWeaponFactory = std::make_unique<WeaponFactory>(myJsonManager.get());
	mySceneManager = std::make_unique<SceneManager>(myJsonManager.get(), myWeaponFactory.get());

	// NOTE: Fill myUpdateContext & myRenderContext after needs
	myUpdateContext.myAudioManager = myAudioManager.get();

	myUpdateContext.myInputInterface = myInputInterface.get();
	// TODO: Remove when interface works
	myUpdateContext.myInput = myInput.get();

	// TODO: DEBUG: Load default game scene
	mySceneManager->Transition(std::make_unique<MainMenu>());
}

void CGame::UpdateCallBack()
{
	// NOTE: Ready for multithreading
	RenderQueue* const updateQueue = myRenderManager->GetUpdateQueue();

	myTimer->Update();
	myControllerInput->UpdateControllerState(myTimer->GetDeltaTime());

	mySceneManager->Update(myTimer->GetDeltaTime(), myUpdateContext);
	mySceneManager->Render(updateQueue, myRenderContext);

	// Rendering
	myRenderManager->Render();
	
	myRenderManager->SwapBuffers();
	myRenderManager->SetPan(mySceneManager->GetCamera()->GetPositionWithModifiers());

	myInput->ResetFrame();
}
