#pragma once
struct student
{
	student() {};
	student(short _age, char _sex, unsigned _fn) :
		age(_age), sex(_sex), fn(_fn) {};

	short age;
	char sex;
	unsigned fn;
};
class Stack
{
public:
	Stack(int _size);
	~Stack();
	Stack(const Stack& old);
	Stack& operator= (const Stack& other);
	void push(student x);
	student& pop();
	bool isEmpty()const;

private:
	student *arr;
	int top;
	int size;
};