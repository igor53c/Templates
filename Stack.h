#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T> class Stack
{

public:
	Stack(const int maxStackSize = 256);

	~Stack();

	bool push(const T);							
	bool isFull() const;						
	bool isEmpty() const;						
	T pop();									

private:
	T* stack;									
	int maxSize;								
	int index;		

	void createStack(const int);				
	bool resizeStack(const int);				
};

template<typename T>
inline Stack<T>::Stack(const int maxStackSize)
{
	maxSize = maxStackSize;
	createStack(maxSize);
}

template<typename T>
inline Stack<T>::~Stack()
{
	delete[] stack;
}

template<typename T>
inline bool Stack<T>::push(const T e)
{
	if (isFull())
	{
		if (!resizeStack(static_cast<int>(ceil(maxSize * 1.1))))
			return false;
	}

	stack[index++] = e;
	return true;
}

template<typename T>
inline bool Stack<T>::isFull() const
{
	return (index >= maxSize);
}

template<typename T>
inline bool Stack<T>::isEmpty() const
{
	return (index == 0);
}

template<typename T>
inline T Stack<T>::pop()
{
	if (isEmpty())
	{
		throw out_of_range("Stack<>::pop(): empty Stack");
	}

	return stack[--index];
}

template<typename T>
inline void Stack<T>::createStack(const int size)
{
	stack = new T[size];

	index = 0;
}

template<typename T>
inline bool Stack<T>::resizeStack(const int size)
{
	bool retValue = false;

	if (size > maxSize)
	{
		T* newStack = new T[size];

		copy(stack, stack + maxSize, newStack);

		maxSize = size;

		delete[] stack;

		stack = newStack;

		retValue = true;
	}

	return retValue;
}