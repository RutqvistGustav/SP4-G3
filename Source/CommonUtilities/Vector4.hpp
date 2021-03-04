#pragma once
#ifdef _DEBUG
#include <assert.h>
#endif

#include <math.h>

namespace CommonUtilities
{
	template<class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;
		//Creates a null-vector
		Vector4<T>()
		{
			x = T();
			y = T();
			z = T();
			w = T();
		}

		//Creates a vector (aX, aY, aZ)
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW)
		{
			x = aX;
			y = aY;
			z = aZ;
			w = aW;
		};

		//Copy constructor (compiler generated)
		Vector4<T>(const Vector4<T>& aVector) = default;

		//Assignment operator (compiler generated)
		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;

		//Destructor (compiler generated)
		~Vector4<T>() = default;

		//Returns the squared length of the vector
		T LengthSqr() const
		{
			T magnitude = (x * x) + (y * y) + (z * z) + (w * w);
			return magnitude;
		}

		//Returns the length of the vector
		T Length() const
		{
			T magnitude = sqrt((x * x) + (y * y) + (z * z) + (w * w));
			return magnitude;
		}

		//Returns a normalized copy of this
		Vector4<T> GetNormalized() const
		{
			Vector4<T> normVec; //or normVec(x, y, z, w) 
			normVec.x = x;
			normVec.y = y;
			normVec.z = z;
			normVec.w = w;
			normVec.Normalize();
			return normVec;
		}

		T GetNominater()
		{
			T magnitude = sqrt(x * x + y * y + z * z + w * w);
			return magnitude;
		}

		//Normalizes the vector
		void Normalize()
		{
			T magnitude = sqrt(x * x + y * y + z * z + w * w);

			if (magnitude != 0)
			{
				x /= magnitude;
				y /= magnitude;
				z /= magnitude;
				w /= magnitude;
			}
			else
			{
				x = 0;
				y = 0;
				z = 0;
				w = 0;
			}
		}

		//Returns the dot product of this and aVector
		T Dot(const Vector4<T>& aVector) const
		{
			return (x * aVector.x) + (y * aVector.y) + (z * aVector.z) + (w * aVector.w);
		}
	};
	//Returns the vector sum of aVector0 and aVector1
	template<class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> addVec;
		addVec.x = aVector0.x + aVector1.x;
		addVec.y = aVector0.y + aVector1.y;
		addVec.z = aVector0.z + aVector1.z;
		addVec.w = aVector0.w + aVector1.w;
		return addVec;
	}

	//Returns the vector difference of aVector0 and aVector1
	template<class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> subVec;
		subVec.x = aVector0.x - aVector1.x;
		subVec.y = aVector0.y - aVector1.y;
		subVec.z = aVector0.z - aVector1.z;
		subVec.w = aVector0.w - aVector1.w;
		return subVec;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template<class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> multVec;
		multVec.x = aVector.x * aScalar;
		multVec.y = aVector.y * aScalar;
		multVec.z = aVector.z * aScalar;
		multVec.w = aVector.w * aScalar;
		return multVec;
	}

	//Returns the vector aVector multiplied by the scalar aScalar
	template<class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		Vector4<T> multVec;
		multVec.x = aScalar * aVector.x;
		multVec.y = aScalar * aVector.y;
		multVec.z = aScalar * aVector.z;
		multVec.w = aScalar * aVector.w;
		return multVec;
	}

	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template<class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		Vector4<T> div_Vec;
		div_Vec.x = aVector.x / aScalar;
		div_Vec.y = aVector.y / aScalar;
		div_Vec.z = aVector.z / aScalar;
		div_Vec.w = aVector.w / aScalar;
		return div_Vec;
	}

	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template<class T> void operator += (Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}

	//Equivalent to setting aVector0 to (aVector0 -aVector1)
	template<class T> void operator -= (Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}

	//Equivalent to setting aVector to (aVector * aScalar)
	template<class T> void operator *= (Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}

	//Equivalent to setting aVector to (aVector / aScalar)
	template<class T> void operator /= (Vector4<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
		aVector.w /= aScalar;
	}
}
