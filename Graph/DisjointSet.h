#pragma once
struct DisjoinedSet
{
	int* parent;
	int* rnk;
	int size;

	DisjoinedSet(int n)
	{
		size = n;
		parent = new int[n];
		rnk = new int[n + 1];
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
			rnk[i] = 0;
		}
	}

	int find(int v)
	{
		if (v != parent[v])
		{
			parent[v] = find(parent[v]);
		}
		return parent[v];
	}

	void merge(int x, int y)
	{
		int set_x = find(x);
		int set_y = find(y);
		if (rnk[x] > rnk[y])
		{
			parent[y] = x;
		}
		else
		{
			parent[set_x] = set_y;
			if (rnk[x] == rnk[y])
			{
				rnk[y]++;
			}
		}
	}
};