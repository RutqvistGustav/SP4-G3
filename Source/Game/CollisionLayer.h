#pragma once

#include <cstdint>

namespace CollisionLayer
{
	using Layer = std::uint_fast32_t;


	static constexpr Layer Default   = 0;
	static constexpr Layer MapSolid  = 1;
	static constexpr Layer Player    = 2;
	static constexpr Layer Entity    = 3;
	static constexpr Layer HUD       = 4;
}
