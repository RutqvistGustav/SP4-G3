#pragma once
#include <vector>
#ifdef _DEBUG
#include <assert.h>
#endif

namespace CommonUtilities
{
	template <class T>
	class Stack
	{
	public:
		// Creates empty stack.
		Stack() = default;

		// Returns amount of elements in stack.
		int GetSize() const { return myStack.size(); }

		// Returns element at the top of the stack.
		// Crashes with assert if Stack is empty.
		const T& GetTop() const
		{
			assert(myStack.size() > 0);

			return myStack[GetTopIndex()];
		}

		// Returns element at the top of the stack.
		// Crashes with assert if Stack is empty.
		T& GetTop()
		{
			assert(myStack.size() > 0);

			return myStack[GetTopIndex()];
		}

		// Adds new element at the top of the Stack.
		void Push(const T& aValue) { myStack.push_back(aValue); }

		// Removes element at the top of the Stack and removes it.
		// Crashes with assert if Stack is empty.
		T Pop()
		{
			assert(myStack.size() > 0);

			T removedValue = myStack[GetTopIndex()];
			myStack.erase(myStack.begin() + GetTopIndex());

			return removedValue;
		}


	private:
		std::vector<T> myStack;

		int GetTopIndex() const { return myStack.size() - 1; }
	};
}

namespace CU = CommonUtilities;