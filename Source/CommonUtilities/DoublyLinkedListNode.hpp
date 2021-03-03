#pragma once

namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedListNode
	{
	public:
		// Copy constructor and assignment operator are removed, so the only way
		// to create a node is by adding a value to a list.
		DoublyLinkedListNode<T>(const DoublyLinkedListNode<T>&) = delete;
		DoublyLinkedListNode<T>& operator=(const DoublyLinkedListNode<T>&) = delete;

		// Returns value from the node
		const T& GetValue() const { return myValue; }
		T& GetValue() { return myValue; }

		// Returns the next node in the list, or nullptr if current node is the last element in the list.
		DoublyLinkedListNode<T>* GetNext() const { return myNext; }

		// Returns the Previous node in the list, or nullptr if current node is the first element in the list.
		DoublyLinkedListNode<T>* GetPrevious() const { return myPrevious; }

	private:
		// Constructor and destructor are private, that way you can't create or remove nodes
		// from outside the class. List class is a friend, so it may create or remove nodes.
		template<class> friend class DoublyLinkedList;
		DoublyLinkedListNode(const T& aValue)
			: myValue(aValue)
			, myNext(nullptr)
			, myPrevious(nullptr) {};

		~DoublyLinkedListNode() = default;

		T myValue;
		DoublyLinkedListNode<T>* myNext;
		DoublyLinkedListNode<T>* myPrevious;
	};
}

namespace CU = CommonUtilities;