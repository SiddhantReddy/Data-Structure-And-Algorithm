// This Algorithm is to check if a given graph has cycle (or) not

#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> a[1001]; // Adjacency list
int visited[1001];
int parent[1001];

// In this dfs function we try to find a back edge (where child has two different parent)
// And if back edge is there then we say cycle is present

bool dfs(int node, int par)
{
    visited[node] = true;
    for (int child : a[node])
    {
        if (!visited[node])
        {
            if (dfs(child, node) == true)
                return true;
        }
        else
        {
            if (child != par) // Back Egde is present
                return true;
        }
    }
    return false;
}

int main()
{
    int n, m; // no of nodes and edges
    cin >> n >> m;
    // Getting edges as input
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    if (dfs(1, 1))
        cout << "Graph has Cycle";
    else
        cout << "No Cycle";
    return 0;
}