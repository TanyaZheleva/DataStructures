#pragma once
#include <iostream>

template<class datatype, class keytype>
class BST
{
public:
	BST();
	BST(keytype);
	BST(keytype, datatype);
	BST(keytype, datatype, BST*) = delete;
	BST(keytype, datatype, BST*, BST*) = delete;
	BST(const BST&);
	BST& operator=(const BST&) = delete;
	~BST();

	void addNode(BST<datatype, keytype>** head, keytype _key, datatype _data);
	void removeNode(BST<datatype, keytype>** head, keytype _key);
	datatype search(BST<datatype, keytype>** head, keytype _key);
	void printTree(BST<datatype, keytype>** head);
	BST<datatype, keytype>* findMin(BST<datatype, keytype>* head);
//private:
	keytype key;
	datatype data;
	BST* left;
	BST* right;
};

template<class datatype, class keytype>
inline BST<datatype, keytype>::BST() :key(0), data(0)
{
	this->left = nullptr;
	this->right = nullptr;
}

template<class datatype, class keytype>
inline BST<datatype, keytype>::BST(keytype _key) :key(_key), data(0)
{
	this->left = nullptr;
	this->right = nullptr;
}

template<class datatype, class keytype>
inline BST<datatype, keytype>::BST(keytype _key, datatype _data) :key(_key), data(_data)
{
	this->left = nullptr;
	this->right = nullptr;
}

template<class datatype, class keytype>
inline BST<datatype, keytype>::BST(const BST& old)
{
	this->key = old.key;
	this->data = old.data;
	this->left = nullptr;
	this->right = nullptr;
}

template<class datatype, class keytype>
inline BST<datatype, keytype>::~BST()
{
	delete this->left;
	delete this->right;
}

template<class datatype, class keytype>
inline void BST<datatype, keytype>::addNode(BST<datatype, keytype>** head, keytype _key, datatype _data)
{
	if (*head == nullptr)
	{
		*head = new BST<datatype, keytype>(*this);
		(*head)->key = _key;
		(*head)->data = _data;
		(*head)->left = nullptr;
		(*head)->right = nullptr;
	}
	else if ((*head)->key > _key)
	{
		addNode(&((*head)->left), _key, _data);
	}
	else if ((*head)->key < _key)
	{
		addNode(&((*head)->right), _key, _data);
	}
}

template<class datatype, class keytype>
inline void BST<datatype, keytype>::removeNode(BST<datatype, keytype>** head, keytype _key)
{
	if (*head == nullptr)
	{
		std::cout << "Node with such key does not exist.\n";
	}
	else
	{
		if ((*head)->key > _key)
		{
			removeNode(&((*head)->left), _key);
		}
		if ((*head)->key < _key)
		{
			removeNode(&((*head)->right), _key);
		}
		if ((*head)->key == _key)
		{
			if ((*head)->left != nullptr && (*head)->right != nullptr)
			{
				BST<datatype, keytype>* temp = this->findMin((*head)->right);
				(*head)->key = temp->key;
				(*head)->data = temp->data;
				removeNode(&((*head)->right), temp->key);
			}
			else
			{
				BST<datatype, keytype>* save = *head;
				if ((*head)->left != nullptr)
				{
					*head = (*head)->left;
				}
				else 
				{
					*head = (*head)->right;
				}
				free(save);
			}
		}
	}
}

template<class datatype, class keytype>
inline datatype BST<datatype, keytype>::search(BST<datatype, keytype>** head, keytype _key)
{
	if (*head == nullptr)
	{
		std::cout << "Node with such key does not exist\n";
		return NULL;
	}

	if ((*head)->key == _key)
	{
		return (*head)->data;
	}
	else if ((*head)->key > _key)
	{
		search(&((*head)->left), _key);
	}
	else if ((*head)->key < _key)
	{
		search(&((*head)->right), _key);
	}
	
}

template<class datatype, class keytype>
inline void BST<datatype, keytype>::printTree(BST<datatype, keytype>** head)
{
		if(*head==nullptr)
		{
			return;
		}
		std::cout << (*head)->key << '\n';
		printTree(&(*head)->left);
		printTree(&(*head)->right);
}

template<class datatype, class keytype>
inline BST<datatype, keytype>* BST<datatype, keytype>::findMin(BST<datatype, keytype>* head)
{
	while (head->left != nullptr)
	{
		head = head->left;
	}
	return head;
}
