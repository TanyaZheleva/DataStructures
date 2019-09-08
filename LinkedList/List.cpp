#include  "List.h"
#include <iostream>


List* L = nullptr;//points at beggining of list

List::List()
{
	next = nullptr;
}

List::List(int _key, int _info):key(_key),info(_info),next(nullptr)
{
}

List::List(int _key, int _info, List& _next):key(_key), info(_info)
{
	this->next = new List(_next);
}

List::~List()
{
	delete this->next;
}

List::List(const List& old):key(old.key), info(old.info)
{
	next =nullptr;
}

List& List::operator=(const List& other)
{
	if (&other != this)
	{
		info = other.info;
		key = other.key;
		next = new List (*(other.next));
	}
	return *this;
}

void List::InsertBegin(List& newItem)
{
	newItem.next = L;
	L = &newItem;
	L->key = key;
	L->info = info;
}


void List::print() const
{

	while (L != nullptr)
	{
		std::cout << L->info << "\n";
		L = L->next;
	}
}

