#include <iostream>

struct node {

	int data;
	node* left;
	node* right;
	node(int val)
	{
		data = val;
		left = nullptr;
		right = nullptr;
	}
};

struct BST
{
	node* root;
	BST()
	{
		root = nullptr;
	}
};

node* insert(node* head, int value)
{
	if (head == nullptr)
	{
		return new node(value);
	}
	else if (head->data < value)
	{
		head->right = insert(head->right, value);
	}
	else if (head->data > value)
	{
		head->left = insert(head->left, value);
	}
	return head;
}

node* find(node* head, int value)
{
	while (head != nullptr)
	{
		if (head->data == value)
		{
			return head;
		}
		if (head->data < value)
		{
			head = head->right;
		}
		if (head->data > value)
		{
			head = head->left;
		}
	}
	return nullptr;
}

node* min(node* head)
{
	while (head->left != nullptr)
	{
		head = head->left;
	}
	return head;
}

node* max(node* head)
{
	while (head->right != nullptr)
	{
		head = head->right;
	}
	return head;
}

node* lca(node* head, int v1, int v2)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	else if (v1 < v2 && head->data<v1 || v1>v2 && head->data < v2)
	{
		return lca(head->right, v1, v2);
	}
	else if (v1<v2 && head->data>v2 || v1 > v2 && head->data > v1)
	{
		return lca(head->left, v1, v2);
	}
	return head;
}

node* lowerBound(node* head, int value)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	if (head->data == value)
	{
		return head;
	}
	if (head->data < value)
	{
		return lowerBound(head->right, value);
	}
	else
	{
		node* temp = lowerBound(head->left, value);
		if (temp != nullptr)
		{
			return temp;
		}
		else
		{
			return head;
		}
	}

}

node* remove(node* head, int value)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	else if (head->data < value)
	{
		head->right = remove(head->right, value);
	}
	else if (head->data > value)
	{
		head->left = remove(head->left, value);
	}
	else if (head->data == value)
	{
		if (head->left == nullptr)
		{
			node* temp = head->right;
			delete head;
			return temp;
		}
		node* maxInLeft = max(head->left);
		head->data = maxInLeft->data;
		head->left = remove(head->left, head->data);
	}
	return head;
}

int getHeightEdges(node* head)
{
	if (head == nullptr)
	{
		return -1;
	}
	int lh = getHeightEdges(head->left);
	int rh = getHeightEdges(head->right);

	if (lh >= rh)
	{
		return lh + 1;
	}
	else
	{
		return rh + 1;
	}
}

int getHeightLeaves(node* head)
{
	if (head == nullptr)
	{
		return 0;
	}
	int lh = getHeightLeaves(head->left);
	int rh = getHeightLeaves(head->right);

	if (lh >= rh)
	{
		return lh + 1;
	}
	else
	{
		return rh + 1;
	}
}

void print(node* head)
{
	if (head != nullptr)
	{
		std::cout << head->data << " ";
		print(head->left);
		print(head->right);
	}
}

void printSorted(node* head)
{
	if (head != nullptr)
	{
		printSorted(head->left);
		std::cout << head->data << " ";
		printSorted(head->right);
	}
}

void printGivenLevel(node* head, int level)
{
	if (head == nullptr)
	{
		return;
	}
	else if (level == 1)
	{
		std::cout << head->data << " ";
	}
	else if (level > 1)
	{
		printGivenLevel(head->left, level - 1);
		printGivenLevel(head->right, level - 1);
	}
}

void printInLevelOrder(node* head)
{
	int height = getHeightLeaves(head);
	for (int i = 0; i <= height; i++)
	{
		printGivenLevel(head, i);
	}
}
