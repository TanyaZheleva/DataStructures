#pragma once
#pragma once
#include <iostream>

struct node
{
	int data;
	node* next;
	node* previous;

	node(int _data) { data = _data; next = nullptr; previous = nullptr; }
};

class list
{
public:
	list();
	void add(int _data);
	void addAtPosition(int data, int position);
	void addAfter(int _after, int  _key);
	void addBefore(int _beforeKey, int _key);
	void deleteAtPosition(int position);
	void DeleteSpaceOfNodes(int  _first, int _last);
	bool search(int num);
	bool emptry()const;
	void print();
	void reverse();
private:
	bool verifyData(node* head, int data);
	node* head;
	node* tail;
};


inline list::list() { head = nullptr; tail = nullptr; }

inline void list::add(int _data)
{
	node* temp = new node{ _data };
	if (head == nullptr && tail == nullptr)
	{
		head = temp;
		tail = temp;
		temp->next = nullptr;
		temp->previous = nullptr;
	}
	else if (head != nullptr)
	{
		tail->next = temp;
		temp->next = nullptr;
		temp->previous = tail;
		tail = temp;
	}
}

inline void list::addAtPosition(int data, int position)
{
	node* temp = new node{ data };
	node* temphead = head;
	while (position > 0 && temphead != nullptr)
	{
		temphead = temphead->next;
		position--;
	}
	if (temphead != nullptr)
	{
		temp->next = temphead->next;
		temp->previous = temphead->previous;
		temphead->next = temp;

		int p = temp->data;
		temp->data = temphead->data;
		temphead->data = p;
	}
}

inline void list::addAfter(int _after, int  _key)
{
	node* tempHead = head;
	while (tempHead != nullptr && tempHead->data != _after)
	{
		tempHead = tempHead->next;
	}

	if (tempHead != nullptr)
	{
		node* tempNode = new node(_key);
		if (tempHead->next != nullptr)
		{
			tempHead->next->previous = tempNode;
		}
		tempNode->next = tempHead->next;
		tempHead->next = tempNode;
		tempNode->previous = tempHead;
	}
	else
	{
		std::cout << "Doesn't exist a node with such key.\n";
	}
}


inline void list::addBefore(int _before, int _key)
{
	node* tempHead = head;
	while (tempHead != nullptr && tempHead->data != _before)
	{
		tempHead = tempHead->next;
	}
	if (tempHead->data == head->data)
	{
		this->add(_key);
	}
	else if (tempHead != nullptr)
	{
		node* tempNode = new node(_key);
		tempNode->next = tempHead;
		tempNode->previous = tempHead->previous;
		if (tempHead->previous != nullptr)
		{
			tempHead->previous->next = tempNode;
		}
		tempHead->previous = tempNode;
	}
	else if (tempHead == nullptr)
	{
		std::cout << "Node with such key doesn't exist.\n";
	}
}


inline void list::deleteAtPosition(int position)
{
	node* tempHead = head;
	while (tempHead != nullptr && tempHead->data != position)
	{
		tempHead = tempHead->next;
	}
	if (tempHead != nullptr)
	{
		if (tempHead->previous != nullptr)
		{
			tempHead->previous->next = tempHead->next;
		}

		if (tempHead->next != nullptr)
		{
			if (tempHead->previous != nullptr)
			{
				tempHead->next = tempHead->previous;
			}
			else //deleting first element of list
			{
				head = tempHead->next;
				tempHead->next->previous = tempHead->previous;
			}
		}
		if (head == tempHead && tempHead->next == nullptr)
		{
			head = nullptr;
		}
		free(tempHead);
	}
	else
	{
		std::cout << "No such node found.\n";
	}

}

inline void list::DeleteSpaceOfNodes(int _first, int _last)
{
	node* tempNode = head;
	while (tempNode != nullptr && tempNode->data != _first)
	{
		tempNode = tempNode->next;
	}
	if (tempNode == nullptr)
	{
		return;
	}
	if (search(_last) == true)
	{
		while (tempNode != nullptr && tempNode->data != _last)
		{
			node* save = tempNode;
			if (tempNode->previous != nullptr)
			{
				tempNode->previous->next = tempNode->next;
			}

			if (tempNode->next != nullptr)
			{
				if (tempNode->previous != nullptr)
				{
					tempNode->next->previous = tempNode->previous;
				}
				else
				{
					head = tempNode->next;
					tempNode->next->previous = tempNode->previous;
				}
			}
			tempNode = tempNode->next;
			free(save);
		}
		this->deleteAtPosition(_last);
	}
	return;
}

inline bool list::search(int num)
{
	node* temp = head;
	while (temp != nullptr)
	{
		if (temp->data == num)
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}

inline bool list::emptry()const
{
	return head == nullptr ? true : false;
}


inline void list::print()
{
	node* temp = this->head;
	while (temp != nullptr)
	{
		std::cout << temp->data << " ";

		temp = temp->next;
	}
	std::cout << "\n";
}
inline void list::reverse()
{
	list a;
	while (head != nullptr)
	{
		node* temp = new node{ head->data };
		if (a.head == nullptr && a.tail == nullptr)
		{
			a.head = temp; a.tail = temp;
		}
		else
		{
			temp->next = a.head->next;
			a.head->next = temp;
			int t = temp->data;
			temp->data = a.head->data;
			a.head->data = t;
		}
		head = head->next;
	}
	this->head = a.head;
}

inline bool list::verifyData(node* head, int data)
{
	while (head != nullptr)
	{
		if (head->data == data)
		{
			return true;
		}
		head = head->next;
	}
	return false;
}