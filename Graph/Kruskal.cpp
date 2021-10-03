#include<bits/stdc++.h>
using namespace std;

//Define structure of the node
struct node {
    int u;
    int v;
    int wt; 
    node(int first, int second, int weight) {
        u = first;
        v = second;
        wt = weight;
    }
};
// comparator for sorting node on weigth (wt)
bool comp(node a, node b) {
    return a.wt < b.wt; 
}
// Disjoint set implementation 
int findPar(int u, vector<int> &parent) {
    if(u == parent[u]) return u; 
    return parent[u] = findPar(parent[u], parent); 
}

void unionn(int u, int v, vector<int> &parent, vector<int> &rank) {
    u = findPar(u, parent);
    v = findPar(v, parent);
    if(rank[u] < rank[v]) {
    	parent[u] = v;
    }
    else if(rank[v] < rank[u]) {
    	parent[v] = u; 
    }
    else {
    	parent[v] = u;
    	rank[u]++; 
    }
}
int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

	int N,E;
	cin >> N >> E;
  // store edges in array of nodes
	vector<node> edges; 
	for(int i = 0;i<E;i++) {
	    int u, v, wt;
	    cin >> u >> v >> wt; 
	    edges.push_back(node(u, v, wt)); 
	}
  // sort edges array
	sort(edges.begin(), edges.end(), comp); 
	// initialize parent and rank array
	vector<int> parent(N);
	for(int i = 0;i<N;i++) 
	    parent[i] = i; 
	vector<int> rank(N, 0); 
	
	int cost = 0;
  // Finding MST
	vector<pair<int,int>> mst; 
	for(auto it : edges) {
    // if nodes belong to different component then only add them in MST     
	    if(findPar(it.v, parent) != findPar(it.u, parent)) {
	        cost += it.wt; 
	        mst.push_back({it.u, it.v}); 
          // Combine component after including in MST    
	        unionn(it.u, it.v, parent, rank); 
	    }
	}
	// cout << cost << endl;
    cout<<"Minimum Spanning Tree Edges : \n";
	for(auto it : mst) cout << it.first << " - " << it.second << endl; 
	return 0;
}