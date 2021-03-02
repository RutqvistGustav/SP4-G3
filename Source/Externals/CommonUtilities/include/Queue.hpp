#pragma once
#ifdef _DEBUG
#include <assert.h>
#endif

#include <vector>

namespace CommonUtilities
{
	template <class T>
	class Queue
	{
	public:
		// Creates empty Queue.
		Queue() = default;

		// Return amount of elements in Queue.
		int GetSize() const { return myQueue.size(); }

		// Return first element in Queue.
		// Crash with assert if Queue is empty.
		const T& GetFront() const
		{
			assert(myQueue.size() > 0);
			return myQueue[0];
		}

		// Return first element in Queue.
		// Crash with assert if Queue is empty.
		T& GetFront()
		{
			assert(myQueue.size() > 0);
			return myQueue[0];
		}

		// Adds new element at the back of the Queue.
		void Enqueue(const T aValue)
		{
			myQueue.push_back(aValue);
		}

		// Return first element in Queue then removes it.
		// Crash with assert if Queue is empty.
		T Dequeue()
		{
			assert(myQueue.size() > 0);

			T removedValue = myQueue[0];
			myQueue.erase(myQueue.begin());
			return removedValue;
		}

	private:
		std::vector<T> myQueue;
	};
}