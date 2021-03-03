#pragma once
namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();

		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;

		void Update();

		float GetDeltaTime() const;
		double GetTotalTime() const;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> myStart, myEnd;
		std::chrono::time_point<std::chrono::high_resolution_clock> myDeltaStart, myDeltaEnd;
		float myDeltaTime = 0;
		double myTotalTime = 0;
	};
}

namespace CU = CommonUtilities;