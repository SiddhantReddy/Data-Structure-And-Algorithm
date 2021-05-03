// This Algorithm is to check if a given graph is Bipartite (or) not

#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> a[1001]; // Adjacency list
int visited[1001];
int color[1001];

// In this dfs function we try to color all nodes of graph with two colors '0'
// and '1' , If coloring can be possible without having same color any two
// adjacent node then graph is Bipartite.

bool dfs(int node, int c)
{
    visited[node] = 1;
    color[node] = c;
    for (int child : a[node])
    {
        if (!visited[child])
        {
            if (dfs(child, c ^ 1) == false) // Coloring child with different color
                return false;
        }
        else
        {
            if (color[child] == color[node]) // Checking color of parent and child
                return false;
        }
    }
    return true;
}

int main()
{
    int n, m; // no of nodes and Edges
    cin >> n >> m;
    // Getting edges as Input
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    if (dfs(1, 0))
        cout << "Graph is Bipartite";
    else
        cout << "Graph is not Bipartite";

    return 0;
}