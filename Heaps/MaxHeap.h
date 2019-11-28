#include <iostream>
#include <vector>

class MaxHeap
{
public:
	MaxHeap();
	MaxHeap(int* arr, int sizeArr);
	void push(int value);
	void pop();
	int top() const;
private:
	std::vector<int> data;
	long long int size;

	int getParent(int index);
	int getRightChild(int index);
	int getLeftChild
	(int index);
	bool hasRightChild(int index);
	bool hasLeftChild(int index);

	void pullUp(int index);
	void pullUpIterative(int index);
	void heapify(int index);
	void heapifyIterative(int index);

};

MaxHeap::MaxHeap() :size(0)
{}

MaxHeap::MaxHeap(int* arr, int sizeArr)
{
	for (int i = 0; i < sizeArr; i++)
	{
		data.push_back(arr[i]);
	}
	size = data.size();
	for (int i = sizeArr / 2 - 1; i >= 0; i--)
	{
		heapify(i);
	}
}

void MaxHeap::push(int value)
{
	data.push_back(value);
	pullUp(size++);
}

void MaxHeap::pop()
{
	if (size > 0)
	{
		std::swap(data[0], data[--size]);
		heapify(0);
	}
}

int MaxHeap::top() const
{
	if (size > 0)
	{
		return data[0];
	}
	return INT_MAX;
}

int MaxHeap::getParent(int index)
{
	return (index - 1) / 2;
}

int MaxHeap::getRightChild(int index)
{
	return index * 2 + 2;
}

int MaxHeap::getLeftChild(int index)
{
	return index * 2 + 1;
}

bool MaxHeap::hasRightChild(int index)
{
	return (index * 2 + 2) < size;
}

bool MaxHeap::hasLeftChild(int index)
{
	return (index * 2 + 1) < size;
}

void MaxHeap::pullUp(int index)
{
	if (index == 0)
	{
		return;
	}

	if (data[index] > data[getParent(index)])
	{
		std::swap(data[index], data[getParent(index)]);
		pullUp(getParent(index));
	}
}

void MaxHeap::pullUpIterative(int index)
{
	while (index > 0)
	{
		if (data[index] > data[getParent(index)])
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

void MaxHeap::heapify(int index)
{
	int maxValue = getLeftChild(index);
	if (hasRightChild(index) && data[getLeftChild(index)] < data[getRightChild(index)])
	{
		maxValue = getRightChild(index);
	}

	if (hasLeftChild(index) && data[maxValue] > data[index])
	{
		std::swap(data[maxValue], data[index]);
		heapify(maxValue);
	}
}

void MaxHeap::heapifyIterative(int index)
{
	while (index >= 0)
	{
		int maxChild = getLeftChild(index);
		if (hasRightChild(index) && data[getLeftChild(index)] < data[getRightChild(index)])
		{
			maxChild = getRightChild(index);
		}
		if (hasLeftChild(index) && data[maxChild] > data[index])
		{
			std::swap(data[maxChild], data[index]);
			index = maxChild;
		}
		else
		{
			break;
		}
	}
}
