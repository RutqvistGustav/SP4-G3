#pragma once

//#include "GameWorld.h"

#include <fstream>
#include <memory>

class CGameWorld;

namespace CommonUtilities
{
	class Input;
}


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

	CGameWorld* myGameWorld;

	std::unique_ptr<CommonUtilities::Input> myInput;
};
