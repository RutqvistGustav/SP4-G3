#pragma once
#include "DoublyLinkedListNode.hpp"
#ifdef _DEBUG
#include <assert.h>
#endif

namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedList
	{
	public:
		// Creates an empty list
		DoublyLinkedList()
			: mySize(0)
			, myHead(nullptr)
			, myTail(nullptr)
		{}

		// Frees all allocated memory
		~DoublyLinkedList()
		{
			for (int element = 0; element < mySize; ++ element)
			{
				Remove(myHead);
			}
		}

		// Return the number of elements in the list
		int GetSize() const { return mySize; }

		// Returns the first node in the list, or nullptr if list is empty
		DoublyLinkedListNode<T>* GetFirst()
		{
			if (mySize > 0)
			{
				return myHead;
			}
			else
			{
				return nullptr;
			}
		}

		// Returns the last node in the list, or nullptr if list is empty
		DoublyLinkedListNode<T>* GetLast()
		{
			if (mySize > 0)
			{
				return myTail;
			}
			else
			{
				return nullptr;
			}
		}

		// Adds new element at the beginning of the list
		void InsertFirst(const T& aValue)
		{
			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
			if (mySize > 0)
			{
				myHead->myPrevious = node;
				node->myNext = myHead;
			}
			else
			{
				myTail = node;
			}
			myHead = node;
			++mySize;
		}

		// Adds new element at the end of the list
		void InsertLast(const T& aValue)
		{
			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
			if (mySize > 0)
			{
				myTail->myNext = node;
				node->myPrevious = myTail;
			}
			else
			{
				myHead = node;
			}
			myTail = node;
			++mySize;
		}

		// Adds new element before aNode
		void InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue)
		{
			assert(mySize > 0 || aNode == nullptr);
			if (aNode == myHead)
			{
				InsertFirst(aValue);
			}

			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
			node->myPrevious = aNode->myPrevious;
			node->myNext = aNode;

			aNode->myPrevious->myNext = node;
			aNode->myPrevious = node;
			++mySize;
		}

		// Adds new element after aNode
		void InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue)
		{
			assert(mySize > 0 || aNode == nullptr);
			if (aNode == myTail)
			{
				InsertLast(aValue);
			}

			DoublyLinkedListNode<T>* node = new DoublyLinkedListNode<T>(aValue);
			node->myNext = aNode->myNext;
			node->myPrevious = aNode;

			aNode->myNext->myPrevious = node;
			aNode->myNext = node;
			++mySize;
		}

		// Removes node from list and frees memory.
		// It's okay to assume aNode to be a node in the list, and not from a different list.
		void Remove(DoublyLinkedListNode<T>* aNode)
		{
			assert(aNode != nullptr);

			DoublyLinkedListNode<T>* prev = aNode->myPrevious;
			DoublyLinkedListNode<T>* next = aNode->myNext;

			if (prev != nullptr)
			{
				prev->myNext = next;
				if (aNode == myTail)
				{
					myTail = prev;
				}
			}

			if(next != nullptr)
			{
				next->myPrevious = prev;
				if (aNode == myHead)
				{
					myHead = next;
				}
			}

			delete aNode;
			aNode = nullptr;
			--mySize;
		}

		// Looks for a value starting from the beginning of the list.
		// Compares using operator==. If no element is found return nullptr.
		DoublyLinkedListNode<T>* FindFirst(const T& aValue)
		{
			assert(mySize > 0);
			
			DoublyLinkedListNode<T>* node = myHead;
			for (int element = 0; element < mySize; ++element)
			{
				if (node->GetValue() == aValue)
				{
					return node;
				}
				else if(node->GetNext() != nullptr)
				{
					node = node->GetNext();
				}
			}
			
			return nullptr;
		}

		// Looks for a value starting from the end of the list.
		// Compares using operator==. If no element is found return nullptr.
		DoublyLinkedListNode<T>* FindLast(const T& aValue)
		{
			if (mySize > 0)
			{
				DoublyLinkedListNode<T>* node = myTail;
				for (int element = 0; element < mySize; ++element)
				{
					if (node->GetValue() == aValue)
					{
						return node;
					}
					else if (node->GetPrevious() != nullptr)
					{
						node = node->GetPrevious();
					}
				}
			}
			return nullptr;
		}

		// Looks for a value and removes it. Search starts from the beginning of the list.
		// Compares values using operator==. If no element was found, do nothing.
		// Returns true if an element was removed, else false.
		bool RemoveFirst(const T& aValue)
		{
			DoublyLinkedListNode<T>* node = myHead;
			for (int index = 0; index < mySize; ++index)
			{
				if (node->GetValue() == aValue)
				{
					Remove(node);
					return true;
				}
				else
				{
					if (node->GetNext() != nullptr)
					{
						node = node->GetNext();
					}
				}
			}
			return false;
		}

		// Looks for a value and removes it. Search starts from the beginning of the list.
		// Compares values using operator==. If no element was found, do nothing.
		// Returns true if an element was removed, else false.
		bool RemoveLast(const T& aValue)
		{

			DoublyLinkedListNode<T>* node = myTail;
			for (int index = 0; index < mySize; ++index)
			{
				if (node->GetValue() == aValue)
				{
					Remove(node);
					return true;
				}
				else
				{
					if (node->GetPrevious() != nullptr)
					{
						node = node->GetPrevious();
					}
				}
			}
			return false;
		}

	private:
		DoublyLinkedListNode<T>* myHead;
		DoublyLinkedListNode<T>* myTail;
		int mySize;
	};
}
