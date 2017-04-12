#include "ListNode.h"

template <class T>
class Queue
{
	public:
		ListNode<T> *front;
		ListNode<T> *back;
		unsigned int size;

		Queue()
		{
			size = 0;
			front = NULL;
			back = NULL;
		}

		~Queue(){};

		void enqueue(T d)
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

		T dequeue()
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

		T getFront()
		{
			return front->data;
		}

		T getBack()
		{
			return back->data;
		}

		void printQueue()
		{
			ListNode<T> *current = front;

			while (true)
			{
				if (current == NULL)
				{
					break;
				}

				cout << current->data << endl;
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
};
