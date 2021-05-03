// This Algorithm is calculate IN and OUT time of Every node
// This can be used to Answer queries like ,if Node A lies in subtree of Node B
//(or) Not in O(1) time

#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> a[1001]; // Adjacency list
int visited[1001];
int IN[1001];  // IN time for Every node
int OUT[1001]; // OUT time for Every node
int timer = 1;

// In this dfs function calculate IN and OUT time of Every node
// When Node enter into stack,called IN time
// When Node exit from stack,called OUT time

void dfs(int node)
{
    visited[node] = 1;
    IN[node] = timer++;
    for (int child : a[node])
    {
        if (!visited[child])
            dfs(child);
    }
    OUT[node] = timer++;
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
    for (int i = 1; i <= n; i++)
        cout << "IN:" << IN[i] << " & "
             << "OUT:" << OUT[i] << "\n";

    return 0;
}