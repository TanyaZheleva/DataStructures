#pragma once
#include <iostream>
#include<vector>
#include<queue>
#include "DisjointSet.h"
using namespace std;
struct Pair
{
	int val;
	int weight;

	Pair(int v, int w) :val(v), weight(w) {}

	bool operator<(const Pair& r)const
	{
		return weight >= r.weight;
	}
};

struct Node
{
	vector<Pair> neighbours;
	void addNeighbour(int v, int w)
	{
		neighbours.push_back({ v ,w });
	}
};

struct Edge
{
	int from;
	int to;
	int weight;

	bool operator< (const Edge& r)const
	{
		return weight < r.weight;
	}
};


class Graph
{
	vector<Node> nodes;

	void DFSUtil(vector<bool>& visited, int start) const
	{
		visited[start] = true;
		std::cout << start << " ";

		for (auto i : nodes[start].neighbours)
		{
			if (!visited[i.val])
			{
				DFSUtil(visited, i.val);
			}
		}
	}

	vector<Edge> gerAllEdges()const
	{
		vector<Edge> edges;
		for (int from = 0; from < nodes.size(); from++)
		{
			for (auto nb : nodes[from].neighbours)
			{
				int to = nb.val;
				int weight = nb.weight;
				if (from < to)
				{
					edges.push_back({ from,to,weight });
				}
			}
		}
		return edges;
	}

public:
	Graph(int n)
	{
		nodes.resize(n + 1);
	}

	void connect(int from, int to, int weight)
	{
		nodes[from].addNeighbour(to, weight);
		nodes[to].addNeighbour(from, weight);
	}

	void BFS(int start) 
	{
		vector<bool> visited(nodes.size(), false);
		queue<Pair> tpn;

		visited[start] = true;
		tpn.push({ start,0 });

		while (!tpn.empty())
		{
			Pair cN = tpn.front();
			int cV = cN.val;
			cout << cV << " ";
			tpn.pop();

			for (auto i : nodes[cV].neighbours)
			{
				int nV = i.val;
				if (!visited[nV])
				{
					visited[nV] = true;
					tpn.push(i);
				}
			}
		}
	}

	void DFS(int start)
	{
		vector<bool>visited(nodes.size(), false);
		DFSUtil(visited, start);
	}

	void Dijkstra(int start)
	{
		vector<int> parent(nodes.size(), -1);
		vector<int> distance(nodes.size(), INT_MAX);
		vector<bool> visited(nodes.size(), false);


		distance[start] = 0;

		priority_queue<Pair> tpn;
		tpn.push({ start,0 });

		while (!tpn.empty())
		{
			Pair cN = tpn.top();
			tpn.pop();
			int cV = cN.val;
			visited[cV] = true;
			for (auto i : nodes[cV].neighbours)
			{
				int nV = i.val;
				if (!visited[nV])
				{
					int altDist = distance[cV] + i.weight;
					if (altDist < distance[nV])
					{
						distance[nV] = altDist;
						parent[nV] = cV;
						tpn.push({ nV,altDist });
					}
				}
			}
		}

		for (int i = 1; i < nodes.size(); i++)
		{
			if (distance[i] == INT_MAX)
			{
				std::cout << -1 << " ";
			}
			else
			{
				std::cout << distance[i] << " ";
			}
		}
	}

	void kruskal() const
	{
		vector<Edge> allEdges = gerAllEdges();
		sort(allEdges.begin(), allEdges.end());

		DisjoinedSet components(nodes.size());
		vector<Edge> tree;

		for (Edge edge : allEdges)
		{
			if (components.find(edge.from) != components.find(edge.to))
			{
				tree.push_back(edge);
				components.merge(edge.from, edge.to);
			}
		}

		for (Edge e : tree)
		{
			cout << e.from << "-" << e.to << "(" << e.weight << ")\n";
		}
	}
};