#pragma once

struct student
{
	short age;
	char sex;
	unsigned fn;
};

class Queue
{
public:
	Queue(int size);
	~Queue();
	Queue(const Queue& old);
	Queue& operator=(const Queue& other);
	void put(student element);
	student& get();
	bool isEmpty() const;

private:
	int size;
	int front;
	int end;
	bool empty;
	student* arr;
};