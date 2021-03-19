#pragma once

#include <Vector2.hpp>

namespace MathHelper
{

	template <typename T>
	static constexpr T locPi = static_cast<T>(3.14159265358979323846264);

	static constexpr float locPif = locPi<float>;
	static constexpr double locPid = locPi<double>;

	template <typename T>
	static constexpr T radToDeg(T someRad)
	{
		return someRad / locPi<T> * static_cast<T>(180);
	}

	template <typename T>
	static constexpr T degToRad(T someDeg)
	{
		return someDeg / static_cast<T>(180) * locPi<T>;
	}

	static CU::Vector2<float> MoveTowards(CU::Vector2<float> aValue, CU::Vector2<float> aTarget, float aMaxDelta)
	{
		CU::Vector2<float> toTarget = aTarget - aValue;
		float length = toTarget.Length();

		toTarget /= length;

		if (length > aMaxDelta)
		{
			length = aMaxDelta;
		}

		return aValue + toTarget * length;
	}
}