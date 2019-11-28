#pragma once
#include <vector>

class MinHeap
{
public:
	MinHeap();
	MinHeap(int* arr, int sizeArr);
	void push(int value);
	void pop();
	int top()const;

private:
	std::vector<int> data;
	int size;

	int getLeftChild(int index);
	int getRightChild(int index);
	int getParent(int index);
	bool hasLeftChild(int index);
	bool hasRightChild(int index);

	void pullUp(int index);
	void pullUpIterative(int index);
	void heapify(int index);
	void heapifyIterative(int index);

};

inline MinHeap::MinHeap():size(0)
{}

inline MinHeap::MinHeap(int* arr, int sizeArr)
{
	for (int i = 0; i < sizeArr; i++)
	{
		data.push_back(arr[i]);
	}
	size = data.size();
	for (int i = sizeArr/2 -1; i >=0; i--)
	{
		heapify(i);
	}
}

inline void MinHeap::push(int value)
{
	data.push_back(value);
	pullUp(size++);
}

inline void MinHeap::pop()
{
	if (size > 0)
	{
		std::swap(data[0], data[--size]);
		heapify(0);
	}
}

inline int MinHeap::top() const
{
	if (size > 0)
	{
		return data[0];
	}
	return INT_MAX;
}

int MinHeap::getLeftChild(int index)
{
	return index * 2 + 1;
}

inline int MinHeap::getRightChild(int index)
{
	return index * 2 + 2;
}

inline int MinHeap::getParent(int index)
{
	return (index - 1) / 2;
}

inline bool MinHeap::hasLeftChild(int index)
{
	return (index * 2 + 1) < size;
}

inline bool MinHeap::hasRightChild(int index)
{
	return (index * 2 + 2) < size;
}

inline void MinHeap::pullUp(int index)
{
	if (index == 0)
	{
		return;
	}

	if (data[index] < data[getParent(index)])
	{
		std::swap(data[index], data[getParent(index)]);
		pullUp(getParent(index));
	}
}

inline void MinHeap::pullUpIterative(int index)
{
	while (index > 0)
	{
		if (data[index] < data[getParent(index)])
		{
			std::swap(data[index], data[getParent(index)]);
			index = getParent(index);
		}
		else
		{
			break;
		}
	}
}

inline void MinHeap::heapify(int index)
{
	int minChild = getLeftChild(index);
	if (hasRightChild(index) && data[getLeftChild(index)] > data[getRightChild(index)])
	{
		minChild = getRightChild(index);
	}
	if (hasLeftChild(index) && data[minChild] < data[index])
	{
		std::swap(data[minChild], data[index]);
		heapify(minChild);
	}
}

inline void MinHeap::heapifyIterative(int index)
{
	while (index >= 0)
	{
		int minChild = getLeftChild(index);
		if (hasRightChild(index) && data[getLeftChild(index)] > data[getRightChild(index)])
		{
			minChild = getRightChild(index);
		}
		if (hasLeftChild(index) && data[minChild] < data[index])
		{
			std::swap(data[minChild], data[index]);
			index = minChild;
		}
		else
		{
			break;
		}
	}
}
