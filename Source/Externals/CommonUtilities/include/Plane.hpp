#pragma once
#include "Vector3.hpp"

namespace CommonUtilities
{
	template<class T>
	class Plane
	{
	public:

		// Default constructor.
		Plane() = default;

		// Constructor taking three points where the normal is (aPoint1 -aPoint0) x (aPoint2 -aPoint0).
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
		{
			InitWith3Points(aPoint0, aPoint1, aPoint2);
		}

		// Constructor taking a point and anormal.
		Plane(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
		{
			InitWithPointAndNormal(aPoint, aNormal);
		}

		// Init the plane with three points, the same as the constructor above.
		void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
		{
			Vector3<T> vec1 = aPoint2 - aPoint0;
			vec1.Normalize();

			Vector3<T> vec2 = aPoint1 - aPoint0;
			vec2.Normalize();

			InitWithPointAndNormal(aPoint0, vec2.Cross(vec1));
		}

		// Init the plane with a point and a normal, the same as the constructor above.
		void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
		{
			myPoint = aPoint;
			myNormal = aNormal;
		}

		// Returns whether a point is inside the plane: it is inside when the point is on the plane or on the side the normal is pointing away from.
		bool IsInside(const Vector3<T>& aPosition) const
		{
			return myNormal.Dot(aPosition - myPoint) <= 0;
		}

		// Returns the normal of the plane.
		const Vector3<T>& GetNormal() const
		{
			return myNormal;
		}

		const Vector3<T>& GetPoint() const
		{
			return myPoint;
		}

	private:
		Vector3<T> myPoint;
		Vector3<T> myNormal;
	};
}
