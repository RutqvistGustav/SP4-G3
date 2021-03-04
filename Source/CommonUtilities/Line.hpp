#pragma once
#include "Vector2.hpp"

namespace CommonUtilities
{
	template<class T>
	class Line
	{
	public:

		// Default constructor: there is no line, the normal is the zero vector.
		Line() = default;

		// Copy constructor.
		Line(const Line <T>& aLine)
		{
			InitWithPointAndDirection(aLine.myPoint, aLine.myDirection);
		}

		// Constructor that takes two points that define the line, the direction is aPoint1 -aPoint0.
		Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
		{
			InitWith2Points(aPoint0, aPoint1);
		}

		// Init theline with two points, the same as the constructor above.
		void InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
		{
			InitWithPointAndDirection(aPoint0, (aPoint1 - aPoint0));
		}

		// Init theline with a point and a direction.
		void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
		{
			myPoint = aPoint;
			myDirection = aDirection.GetNormalized();

			myNormal.x = -myDirection.y;
			myNormal.y = myDirection.x;
		}

		// Returns whether a point is inside the line: it is inside when the point is on the line or on the side the normal is pointing away from.
		bool IsInside(const Vector2<T>& aPosition) const
		{
			return myNormal.Dot(aPosition - myPoint) <= 0;
		}

		// Returns the direction of the line.
		const Vector2<T>& GetDirection() const
		{
			return myDirection;
		}

		// Returns the normal of the line, which is (-direction.y, direction.x).
		const Vector2<T>& GetNormal() const
		{
			return myNormal;
		}

	private:
		Vector2<T> myPoint;
		Vector2<T> myDirection;
		Vector2<T> myNormal;
	};
}