#include "Stack.h"
#include <iostream>

Stack::Stack(int size)
{
	arr = new student[size];
}

Stack::~Stack()
{
	delete[] arr;
}

Stack::Stack(const Stack& old):size(old.size),top(old.top)
{
	for (int i = 0; i < top; i++)
	{
		arr[i] = old.arr[i];
	}
}

Stack& Stack::operator=(const Stack& other)
{
	if (&other != this)
	{
		size = other.size;
		top = other.top;
		for (int i = 0; i < top; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

void Stack::push(student x)
{
	if (top >= size)
	{
		std::cout << "Stack is already full.\n";
	}
	else
	{
		arr[top] = x;
		top++;
	}
}

student& Stack::pop()
{
	if (top == 0)
	{
		std::cout << "Empty stack.\n";
	}
	else
	{
		return arr[--top];
	}
}

bool Stack::isEmpty()const
{
	if (top == 0)
	{
		return true;
	}
	return false;
}