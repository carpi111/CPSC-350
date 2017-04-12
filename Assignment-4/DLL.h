#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DLL
{
	public:
		DLL()
		{
			size = 0;
			front = NULL;
			back = NULL;
		}

		~DLL(){};

		void insertBack(T d)
		{
			ListNode<T> *node = new ListNode<T>(d);

			// IF LIST IS EMPTY
			if (size == 0)
			{
				front = node;
			}

			else
			{
				back->next = node;
				node->prev = back;
			}

			back = node;
			++size;
		}

		T removeFront()
		{
		    if (!isEmpty())
		    {
				ListNode<T> *oldFront = front;

			    T oldData = oldFront->data;

			    // IF THERE IS ONLY ONE ELEMENT
				if (front->next == NULL)
				{
			        front = NULL;
			        back = NULL;
				}

			    // MORE THAN ONE ELEMENT
				else
				{
					front->next->prev = NULL;

			        front = front->next;
				}

				delete oldFront;

				size--;

				return oldData;
		    }

			else
			{
				return T();
			}
		}

		void removeAt(int pos)
		{
			int index = 0;
			ListNode *current = front;
			ListNode *previous = front;

			while (index != pos)
			{
				previous = current;
				current = current->next;
				++index;
			}

			// WE FOUND WHAT NEEDS TO BE DELETED

			previous->next = current->next;
			current->next->previous = previous;
			current->next = NULL;
			current->previous = NULL;
			current->data = NULL;

			size--;
			delete current;
		}

		T getFront()
		{
			return front->data;
		}

		void printList()
		{
			ListNode<T> *current = front;

			while (true)
			{
				if (current->next == NULL)
				{
					break;
				}

				cout << current->data << ", ";
				current = current->next;
			}
		}

		unsigned int getSize()
		{
			return size;
		}

        bool isEmpty()
		{
		    return (size == 0);
		}

		ListNode<T> *front;
		ListNode<T> *back;
		unsigned int size;
};
