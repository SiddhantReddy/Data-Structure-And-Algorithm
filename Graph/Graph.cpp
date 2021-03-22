#include <bits/stdc++.h>
using namespace std;

#define V 5

void addEdgelist(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
void addEdgematrix(int adj[V][V], int u, int v)
{
    adj[u][v] = 1;
    adj[v][u] = 1;
}
void printGraphlist(vector<int> adj[])
{
    for (int v = 0; v < V; v++)
    {
        cout << "\n Adjacency list of vertex "
             << v << "\n head ";
        for (auto x : adj[v])
            cout << "-> " << x;
        printf("\n");
    }
}

void printGraphmatrix(int adj[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

bool dfsvisited[V] = {false}; //visited array for bfs
void dfs(vector<int> adj[], int src)
{
    if (dfsvisited[src])
        return;
    dfsvisited[src] = true;
    cout << src << " ";
    for (auto u : adj[src])
        if (!dfsvisited[u])
            dfs(adj, u);
}

bool bfsvisited[V] = {false}; //visited array for bfs
int d[V]; //distance array
int p[V]; // parent array
queue<int> q;

void bfs(vector<int> adj[], int src)
{
    bfsvisited[src] = true;
    d[src] = 0;
    p[src]=-1;
    q.push(src);
    while (!q.empty())
    {
        int s = q.front();
        q.pop();
        cout<<s<<" ";
        for (auto u : adj[s])
        {
            if (bfsvisited[u])
                continue;
            bfsvisited[u]=true;    
            q.push(u);
            d[u] = d[s] + 1;  // Set distance of 'u' to d[s]+1 and eventually d[u] will be distace of u from src 
            p[u] = s;         //Set parent of 'u' to 's'
        }
    }
}

int main()
{
    int adjmatrix[V][V];
    vector<int> adjlist[V];

    addEdgelist(adjlist, 0, 1);
    addEdgelist(adjlist, 0, 4);
    addEdgelist(adjlist, 1, 2);
    addEdgelist(adjlist, 1, 3);
    addEdgelist(adjlist, 1, 4);
    addEdgelist(adjlist, 2, 3);
    addEdgelist(adjlist, 3, 4);
    printGraphlist(adjlist);
    cout << "\n\n";
    int src=3;
    cout << "DFS : ";
    dfs(adjlist, src);
    cout << "\n\n";
    cout << "BFS : ";
    bfs(adjlist, src);
    cout << "\n\n";
    cout << "Distace Array : ";
    for (int i = 0; i < V; i++)
        cout << d[i] << " ";
    cout << "\n\n";
    cout << "Parent Array : ";
    for (int i = 0; i < V; i++)
        cout << p[i] << " ";

    cout << "\n\n";
    // Initializing matrix with '0'
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            adjmatrix[i][j] = 0;
        }
    }
    addEdgematrix(adjmatrix, 0, 1);
    addEdgematrix(adjmatrix, 0, 4);
    addEdgematrix(adjmatrix, 1, 2);
    addEdgematrix(adjmatrix, 1, 3);
    addEdgematrix(adjmatrix, 1, 4);
    addEdgematrix(adjmatrix, 2, 3);
    addEdgematrix(adjmatrix, 3, 4);
    // printGraphmatrix(adjmatrix);

    return 0;
}
