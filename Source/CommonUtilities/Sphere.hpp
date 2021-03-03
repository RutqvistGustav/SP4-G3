#pragma once
#include "Vector3.hpp"

namespace CommonUtilities
{
	template<typename T>
	class Sphere
	{
	public:
		// Default contructor: there is no sphere, the radius is zero and the position is the zero vector.
		Sphere() = default;

		// Copy constructor.
		Sphere(const Sphere<T>& aSphere)
		{
			myCenter = aSphere.myCenter;
			myRadius = aSphere.myRadius;
		}

		// Constructor that takes the center posiiotn and radius of the sphere.
		Sphere(const Vector3<T>& aCenter, T aRadius)
		{
			InitWithCenterAndRadius(aCenter, aRadius);
		}

		// Init the sphere with a center and a radius, the same as the constructor above.
		void InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius)
		{
			myCenter = aCenter;
			myRadius = aRadius;
		}

		// Returns whether a point is inside the sphere: it is inside when the point is on the sphere surface or inside of the sphere.
		bool IsInside(const Vector3<T>& aPosition) const
		{
			Vector3<T> distanceFromCenter = aPosition;
			distanceFromCenter -= myCenter;
			if (distanceFromCenter.Length() <= myRadius)
			{
				return true;
			}

			return false;
		}

		const Vector3<T>& GetCenter() const
		{
			return myCenter;
		}

		const T& GetRadius() const
		{
			return myRadius;
		}

	private:
		Vector3<T> myCenter;
		T myRadius;
	};
}

namespace CU = CommonUtilities;