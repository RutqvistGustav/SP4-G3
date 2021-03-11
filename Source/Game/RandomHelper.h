#pragma once

#include "MathHelper.h"

#include <Vector2.hpp>
#include <random>

class RandomHelper
{
public:

	template <typename T>
	static T NextInt(T aMin, T aMax)
	{
		std::uniform_int_distribution<T> source{ aMin, aMax };
		return source(ourRandomEngine);
	}

	template <typename T>
	static T NextReal(T aMin, T aMax)
	{
		std::uniform_real_distribution<T> source{ aMin, aMax };
		return source(ourRandomEngine);
	}

	static CU::Vector2<float> InsideUnitCircle()
	{
		float radius = NextReal<float>(0.0f, 1.0f);
		float angle = NextReal<float>(0.0f, MathHelper::locPif);

		return CU::Vector2<float>(std::cos(angle), std::sin(angle)) * radius;
	}

	static CU::Vector2<float> OnUnitCircle()
	{
		const float angle = NextReal<float>(0.0f, MathHelper::locPif);

		return CU::Vector2<float>(std::cos(angle), std::sin(angle));
	}

private:

	static std::default_random_engine ourRandomEngine;

};