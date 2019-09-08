#pragma once

class List
{
public:
	List();
	List(int _key,int _info);
	List(int _key, int _info,List& _next);
	List(const List& old);
	List& operator= (const List& other);
	~List();

	void InsertBegin(List& newItem);
	void InsertAfter(List& newItem, List& afterThis);
	void InsertBefore(List& newItem, List& beforeThis);
	void deleteNode(List& deleteThis, int _key);
	List* search(int _key)const;
	void print()const;

//private:
	int info;
	int key;
	List* next;
};