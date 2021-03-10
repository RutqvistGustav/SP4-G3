#pragma once

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

}