#pragma once
#include <iostream>
#include <string>
#include <iomanip>

int max(int a, int b)
{
	return (a > b) ? a : b;
}

struct Node
{
	double value;
	int height;
	Node* left;
	Node* right;

	Node(double value, Node* left, Node* right)
	{
		this->value = value;
		this->left = left;
		this->right = right;
		this->height = 1;
	}
};

class AVLTree
{
private:
	Node* root;

	bool containsRecursive(Node* current, double value)
	{
		if (current == NULL)
		{
			return false;
		}

		if (current->value == value)
		{
			return true;
		}

		if (value < current->value)
		{
			return containsRecursive(current->left, value);
		}
		else
		{
			return containsRecursive(current->right, value);
		}
	}

	void printRecursive(Node* current)
	{
		if (current == NULL)
		{
			return;
		}

		printRecursive(current->left);
		std::cout << current->value << " ";
		printRecursive(current->right);
	}

	int height(Node* N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}

	int getBalance(Node* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}

	Node* rightRotate(Node* y)
	{
		Node* x = y->left;
		Node* T2 = x->right;

		//rotate  
		x->right = y;
		y->left = T2;

		//update heights of nodes
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		return x;
	}

	Node* leftRotate(Node* x)
	{
		Node* y = x->right;
		Node* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		return y;
	}

	Node* minValueNode(Node* node)
	{
		Node* current = node;

		while (current->left != NULL)
		{
			current = current->left;
		}

		return current;
	}

	Node* insertNode(Node* root, double value)
	{
		//just insert in the tree
		if (root == nullptr)
		{
			return new Node{ value,nullptr,nullptr };
		}
		if (value < root->value)
		{
			root->left = insertNode(root->left, value);
		}
		else if (value > root->value)
		{
			root->right = insertNode(root->right, value);
		}

		//update heights of nodes
		root->height = 1 + max(height(root->left), height(root->right));

		//get balance to check if it's unbalanced now
		int balance = getBalance(root);

		//left left case
		if (balance > 1 && value < root->left->value)
		{
			return rightRotate(root);
		}

		//right right case
		if (balance < -1 && value > root->right->value)
		{
			return leftRotate(root);
		}

		//left right case
		if (balance > 1 && value > root->left->value)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		//right left case
		if (balance < -1 && value < root->right->value)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;

	}

	Node* deleteNode(Node* root, double value)
	{
		//just delete node  
		if (root == NULL)
			return root;

		if (value < root->value)
			root->left = deleteNode(root->left, value);

		else if (value > root->value)
			root->right = deleteNode(root->right, value);

		else if (root->value == value)
		{
			if (root->left == nullptr || root->right == nullptr)
			{
				Node* temp = root->left ? root->left : root->right;
				if (temp == nullptr)
				{
					temp = root;
					root = nullptr;
				}
				else
				{
					*root = *temp;
				}
				free(temp);
			}
			else
			{
				Node* temp = minValueNode(root->right);
				root->value = temp->value;
				root->right = deleteNode(root->right, temp->value);
			}
		}

		//if empty now
		if (root == nullptr)
		{
			return root;
		}

		//update heights
		root->height = 1 + max(height(root->left), height(root->right));

		//get balance to check if it's unbalanced 
		int balance = getBalance(root);

		//left left case
		if (balance > 1 && getBalance(root->left) >= 0)
		{
			return rightRotate(root);
		}

		//right right case 
		if (balance < -1 && getBalance(root->right) <= 0)
		{
			return leftRotate(root);
		}

		//left right case  
		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		//right left case
		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}


public:
	AVLTree()
	{
		root = NULL;
	}


	void add(double value)
	{
		if (root == nullptr)
		{
			root = new Node{ value,nullptr,nullptr };
		}

		else if (contains(value) == true)
		{
			std::cout << value << " already added\n";
		}
		else
		{
			root = insertNode(root, value);
		}
	}

	void remove(double value)
	{

		if (root == nullptr)
		{
			std::cout << " tree is empty\n";
		}

		else if (contains(value) == false)
		{
			std::cout << value << " not found to remove\n";
		}
		else
		{
			root = deleteNode(root, value);
		}
	}

	bool contains(double value)
	{
		if (root == NULL)
		{
			return false;
		}

		return containsRecursive(root, value);
	}

	void print()
	{
		if (root == NULL)
		{
			return;
		}

		printRecursive(root);
		std::cout << "\n";
	}
};
