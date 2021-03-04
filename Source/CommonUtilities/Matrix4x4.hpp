#pragma once
#include "Vector4.hpp"

namespace CommonUtilities
{
	template<typename T>
	class Matrix4x4
	{
	public:

		// Creates the identity matrix.
		Matrix4x4<T>()
		{
			myMatrix[0][0] = 1;
			myMatrix[1][1] = 1;
			myMatrix[2][2] = 1;
			myMatrix[3][3] = 1;
		}

		// Copy Constructor.
		Matrix4x4<T>(const Matrix4x4 <T>& aMatrix)
		{
			*this = aMatrix;
		}

		// () operator for accessing element (row, column) for read/write or read, respectively.
		T& operator()(const int aRow, const int aColumn)
		{
			return myMatrix[aRow - 1][aColumn - 1];
		}

		const T& operator()(const int aRow, const int aColumn) const
		{
			return myMatrix[aRow - 1][aColumn - 1];
		}

		// Static functions for creating rotation matrices.
		static Matrix4x4<T> CreateRotationAroundX(T anAngleInRadians)
		{
			Matrix4x4<T> rotate_x;

			rotate_x(2, 2) = cos(anAngleInRadians);
			rotate_x(2, 3) = sin(anAngleInRadians);
			rotate_x(3, 2) = -sin(anAngleInRadians);
			rotate_x(3, 3) = cos(anAngleInRadians);

			return rotate_x;
		}

		static Matrix4x4<T> CreateRotationAroundY(T anAngleInRadians)
		{
			Matrix4x4 <T> rotate_y;

			rotate_y(1, 1) = cos(anAngleInRadians);
			rotate_y(1, 3) = -sin(anAngleInRadians);
			rotate_y(3, 1) = sin(anAngleInRadians);
			rotate_y(3, 3) = cos(anAngleInRadians);

			return rotate_y;
		}

		static Matrix4x4<T> CreateRotationAroundZ(T anAngleInRadians)
		{
			Matrix4x4 <T> rotate_z;

			rotate_z(1, 1) = cos(anAngleInRadians);
			rotate_z(1, 2) = sin(anAngleInRadians);
			rotate_z(2, 1) = -sin(anAngleInRadians);
			rotate_z(2, 2) = cos(anAngleInRadians);

			return rotate_z;
		}

		// Static function for creating a transpose of a matrix.
		static Matrix4x4<T> Transpose(const Matrix4x4 <T>& aMatrixToTranspose)
		{
			Matrix4x4 temp;

			for (int row = 1; row <= temp.mySize; ++row)
			{
				for (int column = 1; column <= temp.mySize; ++column)
				{
					temp(column, row) = aMatrixToTranspose(row, column);
				}
			}

			return temp;
		}

		// Assumes aTransform is made up of nothing but rotations and translations.
		// Returns inverse. 
		static Matrix4x4<T> GetFastInverse(const Matrix4x4 <T>& aTransform)
		{
			Matrix4x4<T> inverse;
			inverse = inverse.Transpose(aTransform);

			Vector4<T> tempVec;
			tempVec.x = aTransform(4, 1);
			tempVec.y = aTransform(4, 2);
			tempVec.z = aTransform(4, 3);

			Vector4<T> copy;
			inverse(1, 4) = 0;
			inverse(2, 4) = 0;
			inverse(3, 4) = 0;

			copy -= tempVec;
			copy = copy * inverse;

			inverse(4, 1) = copy.x;
			inverse(4, 2) = copy.y;
			inverse(4, 3) = copy.z;

			return inverse;
		}

		// OPERATORS
		template<class T> void operator=(const Matrix4x4 <T>& aMatrix)
		{
			for (int row = 1; row <= mySize; ++row)
			{
				for (int column = 1; column <= mySize; ++column)
				{
					myMatrix[row][column] = aMatrix(row, column);
				}
			}
		}

		template<class T> Matrix4x4 <T>& operator+=(const Matrix4x4 <T>& aMatrix)
		{
			for (int row = 1; row <= mySize; ++row)
			{
				for (int column = 1; column <= mySize; ++column)
				{
					myMatrix[row - 1][column - 1] += aMatrix(row, column);
				}
			}
			return *this;
		}

		template<class T> Matrix4x4 <T>& operator-=(const Matrix4x4 <T>& aMatrix)
		{
			for (int row = 1; row <= mySize; ++row)
			{
				for (int column = 1; column <= mySize; ++column)
				{
					myMatrix[row - 1][column - 1] -= aMatrix(row, column);
				}
			}
			return *this;
		}

		template<class T> void operator*=(const Matrix4x4 <T>& aMatrix)
		{
			Matrix4x4<T> product;
			constexpr int one = 1;

			for (int row = 1; row <= product.mySize; ++row)
			{
				for (int column = 1; column <= product.mySize; ++column)
				{
					product(row, column) = (*this)(row, one) * aMatrix(one, column)
						+ (*this)(row, one + 1) * aMatrix(one + 1, column)
						+ (*this)(row, one + 2) * aMatrix(one + 2, column)
						+ (*this)(row, one + 3) * aMatrix(one + 3, column);
				}
			}

			*this = product;
		}

		static const int mySize = 4;

	private:
		T myMatrix[4][4] = { T() };

	};

	template<class T> Matrix4x4 <T> operator+(const Matrix4x4 <T>& aMatrix0, const Matrix4x4 <T>& aMatrix1)
	{
		Matrix4x4<T> sum;

		for (int row = 1; row <= sum.mySize; ++row)
		{
			for (int column = 1; column <= sum.mySize; ++column)
			{
				sum(row, column) = aMatrix0(row, column) + aMatrix1(row, column);
			}
		}

		return sum;
	}

	template<class T> Matrix4x4 <T> operator-(const Matrix4x4 <T>& aMatrix0, const Matrix4x4 <T>& aMatrix1)
	{
		Matrix4x4<T> sum;

		for (int row = 1; row <= sum.mySize; ++row)
		{
			for (int column = 1; column <= sum.mySize; ++column)
			{
				sum(row, column) = aMatrix0(row, column) - aMatrix1(row, column);
			}
		}

		return sum;
	}

	template<class T> Matrix4x4 <T> operator*(const Matrix4x4 <T>& aMatrix0, const Matrix4x4 <T>& aMatrix1)
	{
		Matrix4x4<T> product;

		int one = 1;

		for (int row = 1; row <= product.mySize; ++row)
		{
			for (int column = 1; column <= product.mySize; ++column)
			{
				product(row, column) = aMatrix0(row, one) * aMatrix1(one, column)
					+ aMatrix0(row, one + 1) * aMatrix1(one + 1, column)
					+ aMatrix0(row, one + 2) * aMatrix1(one + 2, column)
					+ aMatrix0(row, one + 3) * aMatrix1(one + 3, column);
			}
		}

		return product;
	}

	template<class T> Vector4 <T> operator*(const Vector4 <T>& aVector4, const Matrix4x4 <T>& aMatrix)
	{
		Vector4<T> product;

		product.x += aVector4.x * aMatrix(1, 1);
		product.x += aVector4.y * aMatrix(2, 1);
		product.x += aVector4.z * aMatrix(3, 1);
		product.x += aVector4.w * aMatrix(4, 1);
							
		product.y += aVector4.x * aMatrix(1, 2);
		product.y += aVector4.y * aMatrix(2, 2);
		product.y += aVector4.z * aMatrix(3, 2);
		product.y += aVector4.w * aMatrix(4, 2);
							
		product.z += aVector4.x * aMatrix(1, 3);
		product.z += aVector4.y * aMatrix(2, 3);
		product.z += aVector4.z * aMatrix(3, 3);
		product.z += aVector4.w * aMatrix(4, 3);
							
		product.w += aVector4.x * aMatrix(1, 4);
		product.w += aVector4.y * aMatrix(2, 4);
		product.w += aVector4.z * aMatrix(3, 4);
		product.w += aVector4.w * aMatrix(4, 4);

		return product;
	}

	template<class T> const bool operator==(const Matrix4x4 <T>& aMatrix0, const Matrix4x4 <T>& aMatrix1)
	{
		for (int row = 1; row <= aMatrix0.mySize; ++row)
		{
			for (int column = 1; column <= aMatrix0.mySize; ++column)
			{
				if (aMatrix0(row, column) != aMatrix1(row, column))
				{
					return false;
				}
			}
		}
		return true;
	}
}