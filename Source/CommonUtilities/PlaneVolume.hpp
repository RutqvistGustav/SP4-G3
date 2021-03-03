#pragma once
#include <vector>
#include "Plane.hpp"
#include "Vector3.hpp"

namespace CommonUtilities
{
	template<class T>
	class PlaneVolume
	{
	public:

		// Default constructor: empty PlaneVolume.
		PlaneVolume() = default;

		// Constructor taking a list of Plane that makes up the PlaneVolume.
		PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
		{
			myPlaneList = aPlaneList;
		}

		// Add a Plane to the PlaneVolume.
		void AddPlane(const Plane<T>& aPlane)
		{
			myPlaneList.push_back(aPlane);
		}

		// Returns whether a point is inside the PlaneVolume: it is inside when the point is on the
		// plane or on the side the normal is pointing away from for all the planes in the PlaneVolume.
		bool IsInside(const Vector3<T>& aPosition)
		{
			for (int index = 0; index < myPlaneList.size(); ++index)
			{
				if (myPlaneList[index].IsInside(aPosition) == false)
				{
					return false;
				}
			}
			return true;
		}

	private:
		std::vector<Plane<T>> myPlaneList;
	};
}

namespace CU = CommonUtilities;