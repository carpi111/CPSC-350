/* Generic Stack Class */

template <class T>
class GenStack
{
	public:
		GenStack();
		GenStack(int maxSize);
		~GenStack();

		void push(T data);
		T pop();
		T peek();

		int isFull();
		int isEmpty();

		int top;
		int max;
		T *myArray;
};

template <class T>
GenStack<T>::GenStack(){};

template <class T>
GenStack<T>::GenStack(int maxSize)
{
	myArray = new T[maxSize];
	max = maxSize;
	top = -1;
}

template <class T>
GenStack<T>::~GenStack()
{
	delete myArray;
}

template <class T>
void GenStack<T>::push(T data)
{
	// IF FULL, DOUBLE SIZE
	if (top == max - 1)
	{
		T *temp1 = new T[max];

		for (int i = 0; i < max; ++i)
		{
			temp1[i] = myArray[i];
		}

		myArray = new T[max * 2];

		for (int i = 0; i < max; ++i)
		{
			myArray[i] = temp1[i];
		}

		max *= 2;
	}

	myArray[++top] = data;
}

template <class T>
T GenStack<T>::pop()
{
	if (top != -1)
	{
		return myArray[top--];
	}

	else
	{
		return 0;
	}
}

template <class T>
T GenStack<T>::peek()
{
	return myArray[top];
}

template <class T>
int GenStack<T>::isFull()
{
	return (top == max-1);
}

template <class T>
int GenStack<T>::isEmpty()
{
	return (top == -1);
}
