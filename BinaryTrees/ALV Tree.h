#pragma once
#include <iostream>

int max(int a, int b)
{
	return (a > b) ? a : b;
}

struct node
{
	int data;
	int height;
	node* left;
	node* right;

	node(int a, node* l, node* r)
	{
		data = a;
		height = 1;
		left = l;
		right = r;
	}
};

class AVLTree {
public:
	AVLTree();
	void add(int value);
	void remove(int value);
	bool contains(int value);
	void inorder();
	void preorder();
	void postorder();
	void BFS();
private:
	node* root;

	int height(node* n);
	int getBalance(node* n);
	node* rightRotate(node* n);
	node* leftRotate(node* n);
	node* minNode(node* n);
	node* insertNode(node* n, int value);
	node* deleteNode(node* n, int value);
	bool containsRecursive(node* n, int value);
	void inorderRecursive(node* n);
	void preorderRecursive(node* n);
	void postorderRecursive(node* n);
	void givenLevel(node* n, int level);
	void levelOrderTraversal(node* n);
};

inline AVLTree::AVLTree()
{
	root = nullptr;
}

inline void AVLTree::add(int value)
{
	if (contains(value) == true)
	{
		std::cout << "This value already exists in the tree.\n";
	}
	else
	{
		root = insertNode(root, value);
	}
}

inline void AVLTree::remove(int value)
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty.\n";
	}
	else if (contains(value) == false)
	{
		std::cout << "Node does not exist in the tree.\n";
	}
	else
	{
		root = deleteNode(root, value);
	}
}

inline bool AVLTree::contains(int value)
{
	if (root == nullptr)
	{
		return false;
	}
	return containsRecursive(root, value);
}

inline void AVLTree::inorder()
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty.\n";
		return;
	}
	inorderRecursive(root);
}

inline void AVLTree::preorder()
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty.\n";
		return;
	}
	preorderRecursive(root);
}

inline void AVLTree::postorder()
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty.\n";
		return;
	}
	postorderRecursive(root);
}

inline void AVLTree::BFS()
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty.\n";
		return;
	}
	levelOrderTraversal(root);
}

inline int AVLTree::height(node* n)
{
	if (n == nullptr)
	{
		return 0;
	}
	return n->height;
}

inline int AVLTree::getBalance(node* n)
{
	return (height(n->left) - height(n->right));
}

inline node* AVLTree::rightRotate(node* n)
{
	node* x = n->left;
	node* y = x->right;

	x->right = n;
	n->left = y;

	n->height = max(height(n->left), height(n->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

inline node* AVLTree::leftRotate(node* n)
{
	node* x = n->right;
	node* y = x->left;

	x->left = n;
	n->right = y;

	n->height = max(height(n->left), height(n->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

inline node* AVLTree::minNode(node* n)
{
	if (n == nullptr)
	{
		return nullptr;
	}

	node* temp = n;
	while (temp->left != nullptr)
	{
		temp = temp->left;
	}
	return temp;
}

inline node* AVLTree::insertNode(node* n, int value)
{
	if (n == nullptr)
	{
		return new node(value, nullptr, nullptr);
	}
	if (value < n->data)
	{
		n->left = insertNode(n->left, value);
	}
	if (value > n->data)
	{
		n->right = insertNode(n->right, value);
	}

	n->height = max(height(n->left), height(n->right)) + 1;
	int balance = getBalance(n);

	//left left
	if (balance > 1 && value < n->left->data)
	{
		return rightRotate(n);
	}
	//right right
	if (balance<-1 && value>n->right->data)
	{
		return leftRotate(n);
	}
	//left right
	if (balance > 1 && value > n->left->data)
	{
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}
	//right lefft
	if (balance < -1 && value < n->right->data)
	{
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	return n;
}

inline node* AVLTree::deleteNode(node* n, int value)
{
	if (n == nullptr)
	{
		return n;
	}
	if (value < n->data)
	{
		n->left = deleteNode(n->left, value);
	}
	else if (value > n->data)
	{
		n->right = deleteNode(n->right, value);
	}
	else if (value == n->data)
	{
		if (n->left == nullptr || n->right == nullptr)
		{
			node* temp = n->left ? n->left : n->right;
			if (temp == nullptr)
			{
				temp = n;
				n = nullptr;
			}
			else
			{
				*n = *temp;
			}
			free(temp);
		}
		else
		{
			node* temp = minNode(n->right);
			n->data = temp->data;
			n->right = deleteNode(n->right, temp->data);
		}
	}

	if (n == nullptr)
	{
		return n;
	}

	n->height = max(height(n->left), height(n->right)) + 1;
	int balance = getBalance(n);

	//left left
	if (balance > 1 && getBalance(n->left) >= 0)
	{
		return rightRotate(n);
	}
	//right right
	if (balance < -1 && getBalance(n->right) <= 0)
	{
		return leftRotate(n);
	}
	//left right
	if (balance > 1 && getBalance(n->left) < 0)
	{
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}
	//right left
	if (balance < -1 && getBalance(n->right) > 0)
	{
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}
	return n;
}

inline bool AVLTree::containsRecursive(node* n, int value)
{
	if (n == nullptr)
	{
		return false;
	}
	if (value == n->data)
	{
		return true;
	}
	if (value < n->data)
	{
		containsRecursive(n->left, value);
	}
	if (value > n->data)
	{
		containsRecursive(n->right, value);
	}
}

inline void AVLTree::inorderRecursive(node* n)
{
	if (n == nullptr)
	{
		return;
	}
	inorderRecursive(n->left);
	std::cout << n->data << " ";
	inorderRecursive(n->right);
}

inline void AVLTree::preorderRecursive(node* n)
{

	if (n == nullptr)
	{
		return;
	}
	std::cout << n->data << " ";
	preorderRecursive(n->left);
	preorderRecursive(n->right);
}

inline void AVLTree::postorderRecursive(node* n)
{
	if (n == nullptr)
	{
		return;
	}
	postorderRecursive(n->right);
	std::cout << n->data << " ";
	postorderRecursive(n->left);
}

inline void AVLTree::givenLevel(node* n, int level)
{
	if (n == nullptr)
	{
		return;
	}
	if (level == 0)
	{
		return;
	}
	if (n != nullptr && level == 1)
	{
		std::cout << n->data << " ";
	}
	else if (level > 1)
	{
		givenLevel(n->left, level - 1);
		givenLevel(n->right, level - 1);
	}
}

inline void AVLTree::levelOrderTraversal(node* n)
{
	if (n == nullptr)
	{
		return;
	}
	int h = height(n);
	for (int i = 1; i <= h; i++)
	{
		givenLevel(n, i);
	}
}