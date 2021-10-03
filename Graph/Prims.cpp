#include<bits/stdc++.h>
using namespace std;

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

	int N,E;
	cin >> N >> E;
	vector<pair<int,int> > adj[N]; // Adjacency list

	int a,b,wt;
	for(int i = 0; i<E ; i++){
		cin >> a >> b >> wt;
		adj[a].push_back(make_pair(b,wt));
		adj[b].push_back(make_pair(a,wt));
	}	
	
	int parent[N];  // To store parent of node
    int key[N];     // To store weight of edge from parent
    bool mstSet[N];  // To check if node is already in MST (or) NOT
  
    for (int i = 0; i < N; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
    
    priority_queue< pair<int,int>, vector <pair<int,int>> , greater<pair<int,int>> > pq;

    key[0] = 0; 
    parent[0] = -1; 
    pq.push({0, 0});
  
    while(!pq.empty())
    { 
        int u = pq.top().second; 
        pq.pop(); 
        // getting min edge node
        mstSet[u] = true; 
        
        for (auto it : adj[u]) {
            int v = it.first;
            int weight = it.second;
            if (mstSet[v] == false && weight < key[v]) {
                parent[v] = u;
				key[v] = weight; 
                pq.push({key[v], v});    
            }
        } 
    } 
    cout<<"Minimum Spanning Tree Edges : \n";
    for (int i = 1; i < N; i++) 
        cout << parent[i] << " - " << i <<" \n"; 
	return 0;
}