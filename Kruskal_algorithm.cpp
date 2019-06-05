// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include<bitset>

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
using namespace std;

// Creating shortcut for an integer pair
typedef pair<int, int> pair_edge;

// Structure to represent a graph
struct Graph
{
	int N, M;
	vector< pair<pair_edge, int> > edges;

	Graph(int N, int M)
	{
		this->N = N;
		this->M = M;
	}

	void addEdge(int u, int v, int w)
	{
		edges.push_back({{u, v}, w});
	}

	int kruskalMST();
};

struct DSets
{
	int *rank, *parent;
	int n;

	DSets(int n)
	{
		this->n = n;
        rank = new int[n+1];
		parent = new int[n+1];

		for (int i = 0; i < n; i++)
		{
			rank[i] = 0;
			parent[i] = i;
		}
	}

	int find(int u)
	{
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// Union
	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		if (rank[y] < rank[x])
			parent[y] = x;
		else
			parent[x] = y;

		if (rank[y] == rank[x])
			rank[y]++;
	}
};


int Graph::kruskalMST()
{
	int mst_weight = 0;
    DSets set(N);
	sort(edges.begin(), edges.end());
	
	vector< pair<pair_edge, int> >::iterator iter;
	for (iter = edges.begin(); iter != edges.end(); iter++)
	{
		int u = iter->first.first;
		int v = iter->first.second;
		int set_u = set.find(u);
		int set_v = set.find(v);

		if (set_u != set_v)
		{
			mst_weight = mst_weight + iter->second;
			set.merge(set_u, set_v);
		}
	}

	return mst_weight;
}

int main()
{
    int N;
    int M;
	scanf("%d", &N);
    scanf("%d", &M);
    //Graph g(N, M);
    int u[50000];
	int v[50000];
	int w[50000];
    for(int i = 0; i < M; i++) {
        scanf("%d %d %d", &u[i], &v[i], &w[i]);
		//g.addEdge(u[i], v[i], w[i]);
    }
	int q;
	scanf("%d", &q);
	int id;
	Graph g1(N, M);

	ofstream f1;
	const char * stri =  "output.txt";
	f1.open(stri);

	//int mem[500];
	for(int i = 0; i < q; i++) {
		scanf("%d", &id);
		w[id-1] = w[id-1] - 1;
		for(int i = 0; i < M; i++) {
			g1.addEdge(u[i], v[i], w[i]);
    	}
		int mst_wt = g1.kruskalMST();
		f1 << mst_wt << '\n';
    }
	

	f1.close();
	//for(int i = 0; i < q; i++) {
	//	cout << mem[i] << '\n';
	//}


	return 0;
}