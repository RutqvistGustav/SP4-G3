#pragma once
#include <vector>
#include "Vector2.hpp"
#include "Line.hpp"

namespace CommonUtilities
{
	template<class T>
	class LineVolume
	{
	public:

		// Default constructor: empty LineVolume.
		LineVolume() = default;

		// Constructor taking a list of Linethat makesup the LineVolume.
		LineVolume(const std::vector<Line<T>>& aLineList)
		{
			myLineList = aLineList;
		}

		// Add a Line to the LineVolume.
		void AddLine(const Line<T>& aLine)
		{
			myLineList.push_back(aLine);
		}

		// Returns whether a point is inside the LineVolume: it is inside when the point is
		// on the line or on the side the normal is pointingaway from for all the lines in
		// the LineVolume.
		bool IsInside(const Vector2<T>& aPosition)
		{
			for (int index = 0; index < myLineList.size(); ++index)
			{
				if (myLineList[index].IsInside(aPosition) == false)
				{
					return false;
				}
			}
			return true;
		}

	private:
		std::vector<Line<T>> myLineList;
	};
}

namespace CU = CommonUtilities;