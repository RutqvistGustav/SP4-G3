#pragma once
#ifdef _DEBUG
#include <assert.h>
#endif

namespace CommonUtilities
{
	template<class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		//Creates a null-vector
		Vector3<T>()
		{
			x = T();
			y = T();
			z = T();
		}

		//Creates a vector (aX, aY, aZ)
		Vector3<T>(const T& aX, const T& aY, const T& aZ)
		{
			x = aX;
			y = aY;
			z = aZ;
		};

		//Copy constructor (compiler generated)
		Vector3<T>(const Vector3<T>& aVector) = default;

		//Assignment operator (compiler generated)
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;

		//Destructor (compiler generated)
		~Vector3<T>() = default;

		//Returns the squared length of the vector
		T LengthSqr() const
		{
			T magnitude = (x * x) + (y * y) + (z * z);
			return magnitude;
		}

		//Returns the length of the vector
		T Length() const
		{
			T magnitude = sqrt((x * x) + (y * y) + (z * z));
			return magnitude;
		}

		//Returns a normalized copy of this
		Vector3<T> GetNormalized() const
		{
			Vector3<T> normVec; //or normVec(x, y, z) 
			normVec.x = x;
			normVec.y = y;
			normVec.z = z;
			normVec.Normalize();
			return normVec;
		}

		//Normalizes the vector
		void Normalize()
		{
			T magnitude = sqrt(x * x + y * y + z * z);

			if (magnitude != 0)
			{
				x /= magnitude;
				y /= magnitude;
				z /= magnitude;
			}
			else
			{
				x = 0;
				y = 0;
				z = 0;
			}
		}

		//Returns the dot product of this and aVector
		T Dot(const Vector3<T>& aVector) const
		{
			return (x * aVector.x) + (y * aVector.y) + (z * aVector.z);
		}

		//Returns the cross product of this and aVector
		Vector3<T> Cross(const Vector3<T>& aVector) const
		{
			Vector3<T> crossVec;
			crossVec.x = (y * aVector.z - z * aVector.y);
			crossVec.y = (z * aVector.x - x * aVector.z);
			crossVec.z = (x * aVector.y - y * aVector.x);
			return crossVec;
		}
	};
	//Returns the vector sum of aVector0 and aVector1
	template<class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> addVec;
		addVec.x = aVector0.x + aVector1.x;
		addVec.y = aVector0.y + aVector1.y;
		addVec.z = aVector0.z + aVector1.z;
		return addVec;
	}

	//Returns the vector difference of aVector0 and aVector1
	template<class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> subVec;
		subVec.x = aVector0.x - aVector1.x;
		subVec.y = aVector0.y - aVector1.y;
		subVec.z = aVector0.z - aVector1.z;
		return subVec;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template<class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		Vector3<T> multVec;
		multVec.x = aVector.x * aScalar;
		multVec.y = aVector.y * aScalar;
		multVec.z = aVector.z * aScalar;
		return multVec;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template<class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		Vector3<T> multVec;
		multVec.x = aScalar * aVector.x;
		multVec.y = aScalar * aVector.y;
		multVec.z = aScalar * aVector.z;
		return multVec;
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template<class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		Vector3<T> div_Vec;
		div_Vec.x = aVector.x/ aScalar;
		div_Vec.y = aVector.y/ aScalar;
		div_Vec.z = aVector.z/ aScalar;
		return div_Vec;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template<class T> void operator += (Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}

	//Equivalent to setting aVector0 to (aVector0 -aVector1)
	template<class T> void operator -= (Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template<class T> void operator *= (Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template<class T> void operator /= (Vector3<T>&aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
	}
}

namespace CU = CommonUtilities;