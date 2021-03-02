#pragma once
#ifdef _DEBUG
#include <assert.h>
#endif

namespace CommonUtilities
{
	template<typename Type, int size,
		typename CountType =unsigned short, bool UseSafeModeFlag=true>
	class VectorOnStack
	{
	public:
		VectorOnStack(){}

		VectorOnStack(const VectorOnStack& aVectorOnStack)
		{
			myCountType = aVectorOnStack.Size();

			if (myUseSafeModeFlag == true)
			{
				for (int index = 0; index < size; index++)
				{
					myArray[index] = aVectorOnStack.myArray[index];
				}
			}
			else
			{
				memcpy(myArray, aVectorOnStack.myArray, size * sizeof(Type));
			}
		}

		~VectorOnStack()
		{
			Clear();
		}

		VectorOnStack& operator=(const VectorOnStack& aVectorOnStack)
		{
			assert(aVectorOnStack.Size() <= size);
		
			myCountType = aVectorOnStack.Size();
			if (UseSafeModeFlag == true)
			{
				for (int i = 0; i < Size(); i++)
				{
					myArray[i] = aVectorOnStack[i];
				}
			}
			else
			{
				memcpy(myArray, aVectorOnStack.myArray, size * sizeof(Type));
			}
			return *this;
		}

		inline const Type& operator[](const CountType aIndex) const
		{
			assert(aIndex >= 0 && aIndex < size); //  "Index out of bounds\n"
			return myArray[aIndex];
		}

		inline Type& operator[](const CountType aIndex)
		{
			assert(aIndex >= 0 && aIndex < size); //  "Index out of bounds\n"
			return myArray[aIndex];
		}

		inline void Add(const Type& aObject)
		{
			assert(myCountType < size); // "Array full, unable to add element\n"
			myArray[myCountType] = aObject;
			++myCountType;
		}

		inline void Insert(const CountType aIndex, const Type& aObject)
		{
			assert(aIndex >= 0 && aIndex < size); //  "Index out of bounds\n"
			if (myArray[aIndex] == CountType()) 
			{
				++myCountType;
			}
			myArray[aIndex] = aObject; 
		}

		inline void RemoveCyclic(const Type& aObject)
		{
			for (int index = 0; index < size; index++)
			{
				if (myArray[index] == aObject)
				{
					myArray[index] = myArray[myCountType - 1];
					//myArray[myCountType - 1] = CountType();
					--myCountType;
				}
			}
		}
		inline void RemoveCyclicAtIndex(const CountType aItemNumber)
		{
			assert(aItemNumber < myCountType && aItemNumber >= 0);
			myArray[aItemNumber] = myArray[myCountType - 1]; 
			//myArray[myCountType - 1] = CountType();
			--myCountType;
		}

		inline void Clear()
		{
			for (int index = 0; index < size; index++)
			{
				myArray[index] = Type();
			}
			myCountType = CountType();
		}

		__forceinline CountType Size() const
		{
			return myCountType;
		}

	private:
		CountType	myCountType = 0;
		bool		myUseSafeModeFlag = true;
		Type		myArray[size] = { Type() };
	};
}