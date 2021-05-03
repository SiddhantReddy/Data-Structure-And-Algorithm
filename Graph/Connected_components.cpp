#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000007

vector<int> a[100001];
int vis[100001];

void dfs(int node)
{
    vis[node] = 1;
    for (int c : a[node])
    {
        if (!vis[c])
            dfs(c);
    }
}

int main()
{
    int n, m; // n = nodes , m = Edges
    cin >> n >> m;
    // Taking Edges as input
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    int component = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i);
            component++;
        }
    }
    cout << component;
    return 0;
}
