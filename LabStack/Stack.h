#pragma once

#include <exception>

class StackOverflowException : public std::exception 
{
public:
	StackOverflowException(const char* msg, int top) : exception(msg), max(top) {}
private:
	int max;
};

class PopEmptyStackException : public std::exception 
{
public:
	PopEmptyStackException(const char* msg) : exception(msg) {}
};


template<class T>
class Stack
{

public:
	Stack() = delete;
	Stack(int size);
	Stack(const Stack<T>& stack);
	~Stack();

	void push(T value);
	T pop();
	T peek() const;

	bool isEmpty();
	bool isFull();


private:
	T* data;
	int top;
	int max;

};


template <class T>
Stack<T>::Stack(int size)
{
	if (size < 0)
		throw "Size can't be less then 0";
	max = size;
	top = 0;
	data = new T[size];
}

template<class T>
inline Stack<T>::Stack(const Stack<T>& stack)
{
	max = stack.max;
	top = stack.top;
	data = new T[max];
	for (int i = 0; i < top; i++)
		data[i] = stack.data[i];
}

template <class T>
Stack<T>::~Stack()
{
	delete[] data;
}

template <class T>
void Stack<T>::push(T value)
{
	if (top == max)
		throw StackOverflowException("Push in full stack", top);
	data[top++] = value;
}

template <class T>
T Stack<T>::pop()
{
	if (!top)
		throw PopEmptyStackException("Pop from empty stack");
	return data[--top];
}

template<class T>
inline T Stack<T>::peek() const
{
	int index = top - 1;
	return data[index];
}

template <class T>
bool Stack<T>::isEmpty()
{
	return !top;
}

template <class T>
bool Stack<T>::isFull()
{
	return top == max;
}
