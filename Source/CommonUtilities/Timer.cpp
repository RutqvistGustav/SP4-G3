#include "pch.h"

//#ifdef _WIN32
//#include <Windows.h>
//#else
//#include <unistd.h>
//#endif

//#include <iostream>
#include <chrono>
#include <thread>
#include "Timer.h"

namespace CommonUtilities
{
	Timer::Timer()
	{
		myStart = std::chrono::high_resolution_clock::now();
		myDeltaEnd = std::chrono::high_resolution_clock::now();
	}

	void Timer::Update()
	{
		myEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> fl_Duration = myEnd - myStart;
		myTotalTime = fl_Duration.count();

		myDeltaStart = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> db_Duration = myDeltaStart - myDeltaEnd;
		myDeltaTime = db_Duration.count();
		myDeltaEnd = myDeltaStart;
	}

	float Timer::GetDeltaTime() const
	{
		return myDeltaTime;
	}

	double Timer::GetTotalTime() const
	{
		return myTotalTime;
	}
}


//int main()
//{
//
//	CommonUtilities::Timer timer;
//	while (true)
//	{
//		timer.Update();
//		std::cout << "Deltatime: " << timer.GetDeltaTime() << "s		Total Time: " << timer.GetTotalTime() << "s \n";
//		Sleep(100);
//	}
//}
