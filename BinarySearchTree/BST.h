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

node* insert(node* root, int value)
{
	if (root == nullptr)
	{
		return new node(value);
	}
	else if (root->data < value)
	{
		root->right = insert(root->right, value);
	}
	else if (root->data > value)
	{
		root->left = insert(root->left, value);
	}
	return root;
}

node* find(node* root, int value)
{
	while (root != nullptr)
	{
		if (root->data == value)
		{
			return root;
		}
		if (root->data < value)
		{
			root = root->right;
		}
		if (root->data > value)
		{
			root = root->left;
		}
	}
	return nullptr;
}

node* minElement(node* root)
{
	while (root->left != nullptr)
	{
		root = root->left;
	}
	return root;
}

node* maxElement(node* root)
{
	while (root->right != nullptr)
	{
		root = root->right;
	}
	return root;
}

node* lca(node* root, int v1, int v2)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else if (v1 < v2 && root->data<v1 || v1>v2 && root->data < v2)
	{
		return lca(root->right, v1, v2);
	}
	else if (v1<v2 && root->data>v2 || v1 > v2 && root->data > v1)
	{
		return lca(root->left, v1, v2);
	}
	return root;
}

node* lowerBound(node* root, int value)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	if (root->data == value)
	{
		return root;
	}
	if (root->data < value)
	{
		return lowerBound(root->right, value);
	}
	else
	{
		node* temp = lowerBound(root->left, value);
		if (temp != nullptr)
		{
			return temp;
		}
		else
		{
			return root;
		}
	}

}

node* remove(node* root, int value)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else if (root->data < value)
	{
		root->right = remove(root->right, value);
	}
	else if (root->data > value)
	{
		root->left = remove(root->left, value);
	}
	else if (root->data == value)
	{
		if (root->left == nullptr)
		{
			node* temp = root->right;
			delete root;
			return temp;
		}
		node* maxInLeft = maxElement(root->left);
		root->data = maxInLeft->data;
		root->left = remove(root->left, root->data);
	}
	return root;
}

int getHeightEdges(node* root)
{
	if (root == nullptr)
	{
		return -1;
	}
	return std::max(getHeightEdges(root->left), getHeightEdges(root->right)) + 1;
}

int getHeightLeaves(node* root)
{
	if(root == nullptr)
	{
		return 0;
	}
	return std::max(getHeightLeaves(root->left), getHeightLeaves(root->right)) + 1;
}

void getSortedInVector(node* root,std::vector<int>&traversal)
{
	if (root == nullptr)
	{
		return;
	}

	getSortedInVector(root->left, traversal);
	traversal.push_back(root->data);
	getSortedInVector(root->right, traversal);
}

int KthSmallestElement(node* root, int k)
{
	std::vector<int>sorted;
	getSortedInVector(root, sorted);
	return sorted[k - 1];
}

node* findFloor(node* root, int _find)
{
	node* keep = minElement(root);
	if (keep->data <= _find)
	{
		while (root != nullptr)
		{
			if (root->data == _find)
			{
				return root;
			}
			else if (root->data < _find)
			{
				if (root->data > keep->data)
				{
					keep = root;
				}
				root = root->right;
			}
			else if (root->data > _find)
			{
				root = root->left;
			}
		}
	}
	else
	{
		return nullptr;
	}
	return keep;
}

node* findCeiling(node* root, int _find)
{
	node* keep = maxElement(root);

	if (keep->data >= _find)
	{
		while (root != nullptr)
		{
			if (root->data == _find)
			{
				return root;
			}
			else if (root->data < _find)
			{
				root = root->right;
			}
			else if (root->data > _find)
			{
				if (root->data < keep->data)
				{
					keep = root;
				}
				root = root->left;
			}
		}
	}
	else
	{
		return nullptr;
	}
	return keep;
}

void print(node* root)
{
	if (root != nullptr)
	{
		std::cout << root->data << " ";
		print(root->left);
		print(root->right);
	}
}

void printSorted(node* root)
{
	if (root != nullptr)
	{
		printSorted(root->left);
		std::cout << root->data << " ";
		printSorted(root->right);
	}
}


void printGivenLevel(node* root, int level)
{
	if (root == nullptr)
	{
		return;
	}
	else if (level == 1)
	{
		std::cout << root->data << " ";
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}

void printInLevelOrder(node* root)
{
	int height = getHeightLeaves(root);
	for (int i = 0; i <= height; i++)
	{
		printGivenLevel(root, i);
	}
}

void printInLevelOrderWithQueue(node* root)
{
	std::queue<node*> q;
	q.push(root);
	while (!q.empty())
	{
		node* current = q.front();
		q.pop();
		if (current != nullptr)
		{
			std::cout << current->data << " ";
			q.push(current->left);
			q.push(current->right);
		}
	}
}
