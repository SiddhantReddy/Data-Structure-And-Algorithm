// This Algorithm only works for trees

#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> a[1001]; // Adjacency list
int visited[1001];
int dis[1001]; // Storing distance of a node 'i'from source node

void dfs(int node, int d)
{
    visited[node] = 1;
    dis[node] = d;
    for (int child : a[node])
    {
        if (!visited[child])
        {
            dfs(child, d + 1);
        }
    }
}

int main()
{
    int n; // no of nodes
    cin >> n;
    // Getting edges as input for tree (n-1) Edges
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1, 0); // Applying dfs from source node 1 , and calculating distance array
    for (int i = 1; i <= n; i++)
    {
        cout << dis[i] << " ";
    }
    return 0;
}