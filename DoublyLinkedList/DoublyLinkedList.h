#pragma once
#include <iostream>

template<class data, class keytype>
class List
{
public:
	List();
	List(data _info, keytype _key);
	List(data _info, keytype _key, List<data, keytype>& _next);
	List(data _info, keytype _key, List<data, keytype>& _next, List<data, keytype>& _previous);
	List(const List<data, keytype>& old);
	List& operator=(const List<data, keytype>& rhs);
	~List();

	void InsertBegining(List<data, keytype>** head, data _info, keytype _key);
	void InsertAfter(List<data, keytype>** head,keytype _after, data _info, keytype _key);
	void InsertBefore(List<data, keytype>** head, keytype _beforeKey, data _info, keytype _key);
	void DeleteNode(List<data, keytype>** head, keytype _toDelete);
	List<data, keytype>* search(List<data, keytype>* head, keytype _findKey);
	void printList(List<data, keytype>* head);
private:
	data info;
	keytype key;
	List* previous;
	List* next;
};

template<class data, class keytype>
inline List<data, keytype>::List()
{
	this->previous = nullptr;
	this->next = nullptr;
}

template<class data, class keytype>
inline List<data, keytype>::List(data _info, keytype _key) :info(_info), key(_key)
{
	this->previous = nullptr;
	this->next = nullptr;
}

template<class data, class keytype>
inline List<data, keytype>::List(data _info, keytype _key, List<data, keytype>& _next) :info(_info), key(_key)
{
	this->previous = nullptr;
	this->next = new List<data, keytype>(_next);
}

template<class data, class keytype>
inline List<data, keytype>::List(data _info, keytype _key, List<data, keytype>& _next, List<data, keytype>& _previous)
{
	this->info = _info;
	this->key = _key;
	this->next = new List<data, keytype>(_next);
	this->previous = new List<data, keytype>(_previous);
}

template<class data, class keytype>
inline List<data, keytype>::List(const List<data, keytype>& old)
{
	this->info = old.info;
	this->key = old.key;
	this->next = nullptr;
	this->previous = nullptr;
}

template<class data, class keytype>
inline List<data, keytype>& List<data, keytype>::operator=(const List<data, keytype>& rhs)
{
	if (this != &rhs)
	{
		this->info = rhs.info;
		this->key = rhs.key;
		this->next = new List<data, keytype>(*rhs.next);
		this->previous = new List<data, keytype>(*rhs.previous);
	}
	return *this;
}

template<class data, class keytype>
inline List<data, keytype>::~List()
{
	delete previous;
	delete next;
}

template<class data, class keytype>
inline void List<data, keytype>::InsertBegining(List<data, keytype>** head, data _info, keytype _key)
{
	List<data, keytype>* temp = new List<data, keytype>(*this);
	temp->info = _info;
	temp->key = _key;
	temp->previous = nullptr;
	temp->next = *head;
	if (*head != nullptr)
	{
		(*head)->previous = temp;
	}
	*head = temp;
}

template<class data, class keytype>
inline void List<data, keytype>::InsertAfter(List<data, keytype>** head, keytype _after, data _info, keytype _key)
{
	List<data, keytype>* tempHead = this->search(*head, _after);
	if (tempHead != nullptr)
	{
		List<data, keytype>* tempNode = new List<data, keytype>(*this);
		tempNode->info = _info;
		tempNode->key = _key;
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

template<class data, class keytype>
inline void List<data, keytype>::InsertBefore(List<data, keytype>** head, keytype _beforeKey, data _info, keytype _key)
{
	List<data, keytype>* tempHead = search(*head, _beforeKey);
	if (tempHead->key == (*head)->key)
	{
		this->InsertBegining(head, _info, _key);
	}
	else if (tempHead != nullptr)
	{
		List<data, keytype>* tempNode = new List<data, keytype>(*this);
		tempNode->info = _info;
		tempNode->key = _key;
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

template<class data, class keytype>
inline void List<data, keytype>::DeleteNode(List<data, keytype>** head, keytype _toDelete)
{
	List<data, keytype>* tempNode = search(*head, _toDelete);
	if (tempNode != nullptr)
	{
		if (tempNode->previous != nullptr)
		{
			tempNode->previous->next = tempNode->next;
		}

		if (tempNode->next != nullptr)
		{
			if (tempNode->previous != nullptr)
			{
				tempNode->next = tempNode->previous;
			}
			else //deleting first element of list
			{
				*head = tempNode->next;
				tempNode->next->previous = tempNode->previous;
			}
		}
		free(tempNode);
	}
	else
	{
		std::cout << "No such node found.\n";
	}
}

template<class data, class keytype>
inline List<data, keytype>* List<data, keytype>::search(List<data, keytype>* head, keytype _findKey)
{
	while (head != nullptr && head->key != _findKey)
	{
		if (head->key == _findKey)
		{
			return head;
		}
		head = head->next;
	}
	if (head != nullptr && head->key == _findKey)
	{
		return head;
	}
	return NULL;
}

template<class data, class keytype>
inline void List<data, keytype>::printList(List<data, keytype>* head)
{
	while (head != nullptr)
	{
		std::cout << "info: " << head->info << " key: " << head->key << "\n";
		head = head->next;
	}
}


