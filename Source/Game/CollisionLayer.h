#pragma once

#include <cstdint>

namespace CollisionLayer
{
	using Layer = std::uint_fast32_t;


	static constexpr Layer Default   = 0;
	static constexpr Layer MapSolid  = 1;
	static constexpr Layer Entity    = 2;
	static constexpr Layer HUD       = 3;
}
