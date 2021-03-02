#pragma once
#include <Windows.h>
#include <iostream>
#include <unordered_map>

namespace CommonUtilities
{
    struct myKeyStates
    {
        bool myKeyPressed;
        bool myKeyHold;
        bool myKeyReleased;
    };

	class Input
	{
	public:
		enum class EMouseKey
		{
			LEFT,
			MIDDLE,
			RIGHT
		};

		struct Point
		{
			float myMouseX = 0;
			float myMouseY = 0;
		};
		Point GetMousePosition() const;
		Point GetMouseDelta() const;
		

		bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);

		void ResetFrame();

		bool IsKeyPressed(const int aKeyCode) const;
		bool IsKeyDown(const int aKeyCode) const;
		bool IsKeyReleased(const int aKeyCode) const;

		void PrintMousePressed(int& aMousebutton);
		void PrintMouseReleased(int& aMousebutton);

		const std::unordered_map<int, myKeyStates>& GetKeyStates() const;
		const std::unordered_map<EMouseKey, myKeyStates>& GetMouseKeyStates() const;

    private:
		std::unordered_map<int, myKeyStates> myKeys;
		std::unordered_map<EMouseKey, myKeyStates> myMouseKeys;
		Point myMousePosition;
		Point myLastMousePosition;
    };
}
