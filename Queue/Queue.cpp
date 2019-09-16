#include "Queue.h"
#include <iostream>

Queue::Queue(int _size) :size(_size), front(0), end(0), empty(true)
{
	arr = new student[size];
}

Queue::~Queue()
{
	delete[] arr;
}

Queue::Queue(const Queue& old) :size(old.size), front(old.front), end(old.end), empty(old.empty)
{
	for (int i = front; i < end; i++)
	{
		arr[i] = old.arr[i];
	}
}

Queue& Queue::operator=(const Queue& other)
{
	if (&other != this)
	{
		size = other.size;
		front = other.front;
		end = other.end;
		empty = other.empty;
		for (int i = front; i < end; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

void Queue::put(student a)
{
	if (end >= size && front > 0)
	{
		end = 0;
	}

	if (end>=size && empty == false)
	{
		std::cout << "Queue is full\n";
		return;
	}
	else
	{
		if (front >= size)
		{
			front = end;
		}
		arr[end] = a;
		end++;
		empty = false;
	}
}

student& Queue::get()
{
	if (front < end && front < size && empty == false)
	{
		student temp = arr[front];
		front++;
		if (front >= size && front != end)
		{
			front = 0;
		}
		return temp;
	}
	else
	{
		std::cout << "Nothing there\n";
	}
}

bool Queue::isEmpty()const
{
	if (front == end)
	{
		return true;
	}
	return false;
}