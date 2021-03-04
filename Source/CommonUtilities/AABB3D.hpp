#pragma once
#include "Vector3.hpp"

namespace CommonUtilities
{
	template<typename T>
	class AABB3D
	{
	public:
		// Default contructor: there is no AABB, both min and max points are the zero vector.
		AABB3D() = default;

		// Copy constructor.
		AABB3D(const AABB3D<T>& aAABB3D)
		{
			myMax = aAABB3D.myMax;
			myMin = aAABB3D.myMin;
		}

		// Contructor taking the positions of the minimum and maximum corners.
		AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax)
		{
			InitWithMinAndMax(aMin, aMax);
		}

		// Init the AABB  with the positions of the minimum and maximum corners, same as the constructor above.
		void InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax)
		{
			myMax = aMax;
			myMin = aMin;
		}

		// Returns whether a point is inside the AABB: it is inside when the point is on any of the AABB's sides or inside of the AABB.
		bool IsInside(const Vector3<T>& aPosition) const
		{
			if (myMin.x <= aPosition.x && aPosition.x <= myMax.x)
			{
				if (myMin.y <= aPosition.y && aPosition.y <= myMax.y)
				{
					if (myMin.z <= aPosition.z && aPosition.z <= myMax.z)
					{
						return true;
					}
				}
			}
			return false;
		}

		const Vector3<T>& GetMax() const
		{
			return myMax;
		}

		const Vector3<T>& GetMin() const
		{
			return myMin;
		}

	private:
		Vector3<T> myMax;
		Vector3<T> myMin;
	};
}