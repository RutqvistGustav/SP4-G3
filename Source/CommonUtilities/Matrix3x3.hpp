#pragma once
#include "Matrix4x4.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace CommonUtilities
{
	template<typename T>
	class Matrix3x3
	{
	public:

		// Creates the identity matrix.
		Matrix3x3<T>()
		{
			myMatrix[0][0] = 1;
			myMatrix[1][1] = 1;
			myMatrix[2][2] = 1;
		}

		// Copy Constructor.
		Matrix3x3<T>(const Matrix3x3 <T>& aMatrix)
		{
			*this = aMatrix;
		}

		// Copies the top left 3x3 part of the Matrix4x4.
		Matrix3x3<T>(const Matrix4x4 <T>& aMatrix)
		{
			*this = aMatrix;
		}

		// () operator for accessing element (row, column) for read/write or read, respectively.
		T& operator()(const int aRow, const int aColumn)
		{
			return myMatrix[aRow-1][aColumn-1];
		}

		const T& operator()(const int aRow, const int aColumn) const
		{
			return myMatrix[aRow-1][aColumn-1];
		}

		// Static functions for creating rotation matrices.
		static Matrix3x3<T> CreateRotationAroundX(T anAngleInRadians)
		{
			Matrix3x3<T> rotate_x;

			rotate_x(2, 2) = cos(anAngleInRadians);
			rotate_x(2, 3) = sin(anAngleInRadians);
			rotate_x(3, 2) = -sin(anAngleInRadians);
			rotate_x(3, 3) = cos(anAngleInRadians);

			return rotate_x;
		}

		static Matrix3x3<T> CreateRotationAroundY(T anAngleInRadians)
		{
			Matrix3x3 <T> rotate_y;

			rotate_y(1, 1) = cos(anAngleInRadians);
			rotate_y(1, 3) = -sin(anAngleInRadians);
			rotate_y(3, 1) = sin(anAngleInRadians);
			rotate_y(3, 3) = cos(anAngleInRadians);

			return rotate_y;
		}

		static Matrix3x3<T> CreateRotationAroundZ(T anAngleInRadians)
		{
			Matrix3x3 <T> rotate_z;

			rotate_z(1, 1) = cos(anAngleInRadians);
			rotate_z(1, 2) = sin(anAngleInRadians);
			rotate_z(2, 1) = -sin(anAngleInRadians);
			rotate_z(2, 2) = cos(anAngleInRadians);

			return rotate_z;
		}

		// Static function for creating a transpose of a matrix.
		static Matrix3x3<T> Transpose(const Matrix3x3 <T>& aMatrixToTranspose)
		{
			Matrix3x3 temp;

			for (int row = 1; row <= temp.mySize; ++row)
			{
				for (int column = 1; column <= temp.mySize; ++column)
				{
					temp(column, row) = aMatrixToTranspose(row, column);
				}
			}

			return temp;
		}

		// OPERATORS
		template<class T> void operator=(const Matrix3x3 <T>& aMatrix)
		{
			for (int row = 1; row <= mySize; ++row)
			{
				for (int column = 1; column <= mySize; ++column)
				{
					myMatrix[row - 1][column - 1] = aMatrix(row, column);
				}
			}
		}

		template<class T> void operator=(const Matrix4x4 <T>& aMatrix)
		{
			for (int row = 1; row <= mySize; ++row)
			{
				for (int column = 1; column <= mySize; ++column)
				{
					myMatrix[row - 1][column - 1] = aMatrix(row, column);
				}
			}
		}

		template<class T> void operator+=(const Matrix3x3 <T>& aMatrix)
		{
			for (int row = 1; row <= mySize; ++row)
			{
				for (int column = 1; column <= mySize; ++column)
				{
					myMatrix[row - 1][column - 1] += aMatrix(row, column);
				}
			}
		}

		template<class T> void operator-=(const Matrix3x3 <T>& aMatrix)
		{
			for (int row = 1; row <= mySize; ++row)
			{
				for (int column = 1; column <= mySize; ++column)
				{
					myMatrix[row - 1][column - 1] -= aMatrix(row, column);
				}
			}
		}

		template<class T> void operator*=(const Matrix3x3 <T>& aMatrix)
		{
			Matrix3x3<T> product;
			constexpr int one = 1;

			for (int row = 1; row <= product.mySize; ++row)
			{
				for (int column = 1; column <= product.mySize; ++column)
				{
					product(row, column) = (*this)(row, one) * aMatrix(one, column)
						+ (*this)(row, one + 1) * aMatrix(one + 1, column)
						+ (*this)(row, one + 2) * aMatrix(one + 2, column);
				}
			}

			*this = product;
		}

		static constexpr int mySize = 3;
	private:
		T myMatrix[3][3] = { T() };
	};

	template<class T> Matrix3x3 <T> operator+(const Matrix3x3 <T>& aMatrix0, const Matrix3x3 <T>& aMatrix1)
	{
		Matrix3x3<T> sum;

		for (int row = 1; row <= sum.mySize; ++row)
		{
			for (int column = 1; column <= sum.mySize; ++column)
			{
				sum(row, column) = aMatrix0(row, column) + aMatrix1(row, column);
			}
		}

		return sum;
	}

	template<class T> Matrix3x3 <T> operator-(const Matrix3x3 <T>& aMatrix0, const Matrix3x3 <T>& aMatrix1)
	{
		Matrix3x3<T> sum;

		for (int row = 1; row <= sum.mySize; ++row)
		{
			for (int column = 1; column <= sum.mySize; ++column)
			{
				sum(row, column) = aMatrix0(row, column) - aMatrix1(row, column);
			}
		}

		return sum;
	}

	template<class T> Matrix3x3 <T> operator*(const Matrix3x3 <T>& aMatrix0, const Matrix3x3 <T>& aMatrix1)
	{
		Matrix3x3<T> product;

		constexpr int one = 1;

		for (int row = 1; row <= product.mySize; ++row)
		{
			for (int column = 1; column <= product.mySize; ++column)
			{
				product(row, column) = aMatrix0(row, one) * aMatrix1(one, column)
					+ aMatrix0(row, one + 1) * aMatrix1(one + 1, column)
					+ aMatrix0(row, one + 2) * aMatrix1(one + 2, column);
			}
		}

		return product;
	}

	template<class T> Vector3 <T> operator*(Vector3 <T>& aVector3, const Matrix3x3 <T>& aMatrix)
	{
		// Row Vector multiplication

		Vector3<T> product;

		product.x += aVector3.x * aMatrix(1, 1);
		product.x += aVector3.y * aMatrix(2, 1);
		product.x += aVector3.z * aMatrix(3, 1);

		product.y += aVector3.x * aMatrix(1, 2);
		product.y += aVector3.y * aMatrix(2, 2);
		product.y += aVector3.z * aMatrix(3, 2);

		product.z += aVector3.x * aMatrix(1, 3);
		product.z += aVector3.y * aMatrix(2, 3);
		product.z += aVector3.z * aMatrix(3, 3);

		return product;
	}

	template<class T> const bool operator==(const Matrix3x3 <T>& aMatrix0, const Matrix3x3 <T>& aMatrix1)
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
