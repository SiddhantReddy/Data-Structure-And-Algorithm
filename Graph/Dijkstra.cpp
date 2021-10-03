#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

	int n,m,source;
	cin >> n >> m;
	vector<pair<int,int> > adj[n+1]; 	// Adjacency list for of graph
  // Making graph with weights
	int a,b,wt;
	for(int i = 0; i<m ; i++){
		cin >> a >> b >> wt;
		adj[a].push_back(make_pair(b,wt));
		adj[b].push_back(make_pair(a,wt));
	}	

	// Dijkstra's algorithm begins from here
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
    // min-heap ; In pair => (dist,from)
	vector<int> distTo(n+1,INT_MAX); 	
    // Array for calculating shortest paths; 
	distTo[0] = 0; // distance of source is 0
	pq.push(make_pair(0,0));	// (dist,from)
	
	while( !pq.empty() ){
		int dist = pq.top().first; // Current distance
		int prev = pq.top().second; // current node
		pq.pop();
		
		vector<pair<int,int> >::iterator it;
		for( it = adj[prev].begin() ; it != adj[prev].end() ; it++){
			int next = it->first; 
			int nextDist = it->second;
            // if new distance is less then update distance
			if( distTo[next] > distTo[prev] + nextDist){
				distTo[next] = distTo[prev] + nextDist;
				pq.push(make_pair(distTo[next], next));
			}
		}
		
	}
	
	cout << "The distances from source to all vertices is \n";
	for(int i = 1 ; i<n ; i++)	{
        cout<<"0 to "<<i<<" : ";
        cout << distTo[i] << "\n";
    }
	cout << "\n";
	
	return 0;
}