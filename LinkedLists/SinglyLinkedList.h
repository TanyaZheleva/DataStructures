#include <iostream>

struct node
{
	int data;
	node* next;

	node(int _data) { data = _data; next = nullptr; }
};

class list
{
public:
	list();
	void add(int _data);
	void addAtPosition(int data, int position);
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
	}
	else if (head != nullptr)
	{
		tail->next = temp;
		tail = temp;
		temp->next = nullptr;
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
		temphead->next = temp;

		int p = temp->data;
		temp->data = temphead->data;
		temphead->data = p;
	}
}

inline void list::deleteAtPosition(int position)
{
	if (position == 0)
	{
		node* save = head;
		head = head->next;
		free(save);
	}

	else
	{
		node* temp = head;
		while (position - 1 > 0)
		{
			temp = temp->next;
			position--;
		}
		node* save = temp->next;
		temp->next = temp->next->next;
		free(save);
	}
}

inline void list::DeleteSpaceOfNodes(int _first, int _last)
{
	while (head != nullptr && head->data != _first)
	{
		head = head->next;
	}
	if (head == nullptr)
	{
		return;
	}
	if (search(_last) == true)
	{
		if (head->data == _first)
		{
			while (head->data != _last)
			{
				node* save = head;
				head = head->next;
				free(save);
			}
		}

		else
		{
			node* toDelete = head;
			while (toDelete->next != nullptr && toDelete->next->data != _first)
			{
				toDelete = toDelete->next;
			}

			if (toDelete->next != nullptr && verifyData(toDelete->next, _last) == true)
			{
				while (toDelete->next != nullptr && toDelete->next->data != _last)
				{
					node* save = toDelete->next;
					toDelete->next = toDelete->next->next;
					free(save);
				}
			}
			else
			{
				std::cout << "One or more invalid keys.\n";
				return;
			}
		}
		deleteAtPosition(_last);
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