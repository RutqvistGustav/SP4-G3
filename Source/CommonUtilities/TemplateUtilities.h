#pragma once
#ifdef _DEBUG
#include <assert.h>
#endif

namespace CommonUtilities
{
	template<typename T>
	T Max(T& aVal1, T& aVal2)
	{
		if (aVal1 < aVal2)
		{
			return aVal2;
		}
		else
		{
			return aVal1;
		}
	}

	template<typename T>
	T Min(T& aVal1, T& aVal2)
	{
		if (aVal1 < aVal2)
		{
			return aVal1;
		}
		else
		{
			return aVal2;
		}
	}

	template<typename T>
	T Abs(T& aType)
	{
		if (aType < 0)
		{
			return aType *= -1;
		}
		else
		{
			return aType;
		}
	}

	template<typename T>
	T Clamp(T& aMin, T& aMax, T& aValue)
	{
		assert(aMax > aMin);
		if (aValue < aMin)
		{
			return aMin;
		}
		else if (aValue > aMax)
		{
			return aMax;
		}
		else
		{
			return aValue;
		}
	}

	template<typename T>
	T Lerp(T& aA, T& aB, float& aC)
	{
		return aA + aC(aB - aA);
	}

	template<typename T>
	void Swap(T& aType1, T& aType2)
	{
		T& temp = aType1;
		aType1 = aType2;
		aType2 = temp;
	}
}

namespace CU = CommonUtilities;