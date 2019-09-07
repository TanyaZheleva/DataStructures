#include <iostream>

int top;
const int size = 100;
student stack[size];

struct student
{
	short age;
	char sex;
	char* name;
	unsigned fn;
};

void init()
{
	top = 0;
}

void push(student a)
{
	if (top >= size)
	{
		std::cout << "No space left!\n";
	}
	else
	{
		stack[top] = a;
		top++;
	}
}

student pop()
{
	if (top == 0)
	{
		std::cout << "Empty stack!\n";
	}
	else
	{
		top--;
		return stack[top+1];
	}
}

bool isEmpty()
{
	if (top == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	student b;
	push(b);
	pop();
	isEmpty();
	return 0;
}