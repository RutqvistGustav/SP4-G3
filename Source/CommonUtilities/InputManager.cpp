#include "pch.h"

#include <Windows.h>
#include <Windowsx.h>
#include "InputManager.h"

namespace CommonUtilities
{
    Input::Point Input::GetMousePosition() const
    {
        return myMousePosition;
    }

    Input::Point Input::GetMouseDelta() const
    {
        Input::Point mouseDelta = myMousePosition;
        mouseDelta.myMouseX -= myLastMousePosition.myMouseX;
        mouseDelta.myMouseY -= myLastMousePosition.myMouseY;
        return mouseDelta;
    }

    bool Input::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_KEYDOWN:
        {
            myKeys[wParam].myKeyPressed = true;
            myKeys[wParam].myKeyHold = true;
            break;
        }
        case WM_KEYUP:
        {
            myKeys[wParam].myKeyHold = false;
            myKeys[wParam].myKeyReleased = true;
            break;
        }

        case WM_LBUTTONUP:
        {
            myMouseKeys[EMouseKey::LEFT].myKeyReleased = true;
            myMouseKeys[EMouseKey::LEFT].myKeyHold = false;
            break;
        }
        case WM_LBUTTONDOWN:
        {
            myMouseKeys[EMouseKey::LEFT].myKeyPressed = true;
            myMouseKeys[EMouseKey::LEFT].myKeyHold = true;
            break;
        }
        case WM_MBUTTONUP:
        {
            myMouseKeys[EMouseKey::MIDDLE].myKeyReleased = true;
            myMouseKeys[EMouseKey::MIDDLE].myKeyHold = false;
            break;
        }

        case WM_MBUTTONDOWN:
        {
            myMouseKeys[EMouseKey::MIDDLE].myKeyPressed = true;
            myMouseKeys[EMouseKey::MIDDLE].myKeyHold = true;
            break;
        }
        case WM_RBUTTONUP:
        {
            myMouseKeys[EMouseKey::RIGHT].myKeyReleased = true;
            myMouseKeys[EMouseKey::RIGHT].myKeyHold = false;
            break;
        }

        case WM_RBUTTONDOWN:
        {
            myMouseKeys[EMouseKey::RIGHT].myKeyPressed = true;
            myMouseKeys[EMouseKey::RIGHT].myKeyHold = true;
            break;
        }

        case WM_MOUSEMOVE:
        {
            myMousePosition.myMouseX = static_cast<float>(GET_X_LPARAM(lParam));
            myMousePosition.myMouseY = static_cast<float>(GET_Y_LPARAM(lParam));
            break;
        }

        default:
            break;
        }

        return 0;
    }

    void Input::ResetFrame()
    {
        for (auto& keyIndex : myKeys)
        {
            if (keyIndex.second.myKeyHold == true)
            {
                keyIndex.second.myKeyPressed = false;
                keyIndex.second.myKeyReleased = false;
            }
            else
            {
                keyIndex.second.myKeyPressed = false;
                keyIndex.second.myKeyHold = false;
                keyIndex.second.myKeyReleased = false;
            }
        }

        for (auto& keyIndex : myMouseKeys)
        {
            keyIndex.second.myKeyPressed = false;
            keyIndex.second.myKeyReleased = false;
        }
        myLastMousePosition = myMousePosition;
    }

    bool Input::IsKeyPressed(const int aKeyCode) const
    {
        if (myKeys.find(aKeyCode) != myKeys.end() && myKeys.at(aKeyCode).myKeyPressed == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Input::IsKeyDown(const int aKeyCode) const
    {
        if (myKeys.find(aKeyCode) != myKeys.end() && myKeys.at(aKeyCode).myKeyHold == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Input::IsKeyReleased(const int aKeyCode) const
    {
        if (myKeys.find(aKeyCode) != myKeys.end() && myKeys.at(aKeyCode).myKeyReleased == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    const std::unordered_map<int, myKeyStates>& Input::GetKeyStates() const
    {
        return myKeys;
    }

    const std::unordered_map<Input::EMouseKey, myKeyStates>& Input::GetMouseKeyStates() const
    {
        return myMouseKeys;
    }

    void Input::PrintMousePressed(int& aMousebutton)
    {
        switch (aMousebutton)
        {
        case 0:
        {
            std::cout << "Left mouse button is pressed\n";
            break;
        }
        case 1:
        {
            std::cout << "Middle mouse button is pressed\n";
            break;
        }
        case 2:
        {
            std::cout << "Right mouse button is pressed\n";
            break;
        }
        }
    }

    void Input::PrintMouseReleased(int& aMousebutton)
    {
        switch (aMousebutton)
        {
        case 0:
        {
            std::cout << "Left mouse button is released\n";
            break;
        }
        case 1:
        {
            std::cout << "Middle mouse button is released\n";
            break;
        }
        case 2:
        {
            std::cout << "Right mouse button is released\n";
            break;
        }
        }
    }
}
