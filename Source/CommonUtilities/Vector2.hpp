#pragma once
#ifdef _DEBUG
#include <assert.h>
#endif

namespace CommonUtilities
{
	template<class T>
	class Vector2
	{
	public:
		T x;
		T y;
		//Creates a null-vector
		Vector2<T>()
		{
			x = T();
			y = T();
		}

		//Creates a vector (aX, aY)
		Vector2<T>(const T& aX, const T& aY)
		{
			x = aX;
			y = aY;
		};

		//Copy constructor (compiler generated)
		Vector2<T>(const Vector2<T>& aVector) = default;

		//Assignment operator (compiler generated)
		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;

		//Destructor (compiler generated)
		~Vector2<T>() = default;

		//Returns the squared length of the vector
		T LengthSqr() const
		{
			T magnitude = (x * x) + (y * y);
			return magnitude;
		}

		//Returns the length of the vector
		T Length() const
		{
			T magnitude = sqrt((x * x) + (y * y));
			return magnitude;
		}

		T GetNominater()
		{
			T magnitude = sqrt(x * x + y * y);
			return magnitude;
		}

		//Returns a normalized copy of this
		Vector2<T> GetNormalized() const
		{
			Vector2<T> normVec; //or normVec(x, y) 
			normVec.x = x;
			normVec.y = y;
			normVec.Normalize();
			return normVec;
		}

		//Normalizes the vector
		void Normalize()
		{
			T magnitude = sqrt(x * x + y * y);

			if (magnitude != 0)
			{
				x /= magnitude;
				y /= magnitude;
			}
			else
			{
				x = 0;
				y = 0;
			}
		}

		//Returns the dot product of this and aVector
		T Dot(const Vector2<T>& aVector) const
		{
			return (x * aVector.x) + (y * aVector.y);
		}
	};
	//Returns the vector sum of aVector0 and aVector1
	template<class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> addVec;
		addVec.x = aVector0.x + aVector1.x;
		addVec.y = aVector0.y + aVector1.y;
		return addVec;
	}

	//Returns the vector difference of aVector0 and aVector1
	template<class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> subVec;
		subVec.x = aVector0.x - aVector1.x;
		subVec.y = aVector0.y - aVector1.y;
		return subVec;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template<class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> multVec;
		multVec.x = aVector.x * aScalar;
		multVec.y = aVector.y * aScalar;
		return multVec;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template<class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		Vector2<T> multVec;
		multVec.x = aScalar * aVector.x;
		multVec.y = aScalar * aVector.y;
		return multVec;
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template<class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		Vector2<T> div_Vec;
		div_Vec.x = aVector.x / aScalar;
		div_Vec.y = aVector.y / aScalar;
		return div_Vec;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template<class T> void operator += (Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}

	//Equivalent to setting aVector0 to (aVector0 -aVector1)
	template<class T> void operator -= (Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template<class T> void operator *= (Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template<class T> void operator /= (Vector2<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		aVector.x /= aScalar;
		aVector.y /= aScalar;
	}
}

namespace CU = CommonUtilities;