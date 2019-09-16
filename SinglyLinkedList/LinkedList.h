#pragma once
#include <iostream>

template<class data, class keytype>
class List
{
public:
	List();
	List(const data _info, const keytype _key);
	List(const data _info, const keytype _key, const List<data,keytype>& _next);
	List(const List<data, keytype>& old);
	List& operator= (const List<data, keytype>& rhs);
	~List();

	void InsertBegining(List<data,keytype>*L,const data _info, const keytype _key);

//private:
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
inline List<data, keytype>::List(const data _info, const keytype _key):info(_info),key(_key)
{
	this->next = nullptr;
}

template<class data, class keytype>
inline List<data, keytype>::List(const data _info, const keytype _key, const List<data, keytype>& _next):info(_info),key(_key)
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
inline void List<data, keytype>::InsertBegining(List<data,keytype>*L,const data _info, const keytype _key)
{
	List<data, keytype>* temp = this;
	temp->info = _info;
	temp->key = _key;
	temp->next = L;
	L = temp;
}
