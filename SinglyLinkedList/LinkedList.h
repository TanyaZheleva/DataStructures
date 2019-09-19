#pragma once
#include <iostream>
#include <iomanip>

template<class data, class keytype>
class List
{
public:
	List();
	List(const data _info, const keytype _key);
	List(const data _info, const keytype _key, const List<data, keytype>& _next);
	List(const List<data, keytype>& old);
	List& operator= (const List<data, keytype>& rhs);
	~List();

	void InsertBegining(List<data, keytype>** head, const data _info, const keytype _key);
	void InsertAfter(List<data, keytype>** head, const keytype _after, const data _info, const keytype _key);
	void InsertBefore(List<data, keytype>** head, const keytype _before, const data _info, keytype _key);
	void DeleteNode(List<data, keytype>** head, const keytype _delete);

	List* search(List<data, keytype>* head, const keytype _find);
	void printList(List<data, keytype>* head);

private:
	data info;
	keytype key;
	List* next;
};

template<class data, class keytype>
inline List<data, keytype>::List()
{
	this->next = nullptr;
}

template<class data, class keytype>
inline List<data, keytype>::List(const data _info, const keytype _key) :info(_info), key(_key)
{
	this->next = nullptr;
}

template<class data, class keytype>
inline List<data, keytype>::List(const data _info, const keytype _key, const List<data, keytype>& _next) :info(_info), key(_key)
{
	this->next = new List<data, keytype>(_next);
}

template<class data, class keytype>
inline List<data, keytype>::List(const List<data, keytype>& old)
{
	this->info = old.info;
	this->key = old.key;
	this->next = nullptr;
}

template<class data, class keytype>
inline List<data, keytype>& List<data, keytype>::operator=(const List<data, keytype>& rhs)
{
	if (this != &rhs)
	{
		this->info = rhs.info;
		this->key = rhs.key;
		this->next = nullptr;
	}
	return *this;
}

template<class data, class keytype>
inline List<data, keytype>::~List()
{
	delete this->next;
}

template<class data, class keytype>
inline void List<data, keytype>::InsertBegining(List<data, keytype>** head, const data _info, const keytype _key)
{
	List <data, keytype>* temp = new List<data, keytype>(*this);
	temp->key = _key;
	temp->info = _info;
	temp->next = *head;
	*head = temp;
}

template<class data, class keytype>
inline void List<data, keytype>::InsertAfter(List<data, keytype>** head, const keytype _after, const data _info, const keytype _key)
{
	List<data, keytype>* tempHead = search(*head, _after);
	if (tempHead != nullptr)
	{
		List<data, keytype>* temp = new List<data, keytype>(*this);
		temp->key = _key;
		temp->info = _info;
		temp->next = tempHead->next;
		tempHead->next = temp;
	}
	else
	{
		std::cout << "Node with such key does not exist.\n";
	}

}

template<class data, class keytype>
inline void List<data, keytype>::InsertBefore(List<data, keytype>** head, const keytype _before, const data _info, keytype _key)
{
	List<data, keytype>* tempHead = search(*head, _before);
	if (tempHead != nullptr)
	{
		if (tempHead->key == (*head)->key)
		{
			this->InsertBegining(head, _info, _key);
		}
		else
		{
			List<data, keytype>* tempNode = new List<data, keytype>(*this);
			tempNode->info = _info;
			tempNode->key = _key;
			tempNode->next = tempHead->next;
			tempHead->next = tempNode;

			data switchData = tempHead->info;
			tempHead->info = tempNode->info;
			tempNode->info = switchData;

			keytype switchKey = tempHead->key;
			tempHead->key = tempNode->key;
			tempNode->key = switchKey;
		}
	}
	else
	{
		std::cout << "No node with such key found.\n";
	}
}

template<class data, class keytype>
inline void List<data, keytype>::DeleteNode(List<data, keytype>** head, const keytype _delete)
{
	if ((*head)->key == _delete)
	{
		List<data, keytype>* save = *head;
		*head=(*head)->next;
		free(save);
	}
	else
	{
		List<data, keytype>* toDelete = *head;
		while (toDelete->next != nullptr && toDelete->next->key != _delete)
		{
			toDelete = toDelete->next;
		}
		List<data, keytype>* save = toDelete->next;
		toDelete->next = toDelete->next->next;
		free(save);
	}
}

template<class data, class keytype>
inline List<data, keytype>* List<data, keytype>::search(List<data, keytype>* head, const keytype _find)
{
	while (head != nullptr)
	{
		if (head->key == _find)
		{
			return head;
		}
		head = head->next;
	}
	return NULL;
}

template<class data, class keytype>
inline void List<data, keytype>::printList(List<data, keytype>* head)
{
	while (head != nullptr)
	{
		std::cout << "data: " << head->info << " " << "key: " << head->key << "\n";
		head = head->next;
	}
}
