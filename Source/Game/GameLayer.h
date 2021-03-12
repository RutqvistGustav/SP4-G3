#pragma once

#include <cstdint>

namespace GameLayer
{
	using Layer = std::int_fast32_t;

	static constexpr Layer Background = 0;
	static constexpr Layer Solid = 5;
	static constexpr Layer Foreground = 10;
}
