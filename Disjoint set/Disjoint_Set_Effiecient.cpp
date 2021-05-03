#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int find(int a) // It uses path compression for optimization
{
    // iterative approach
    // vector<int> v;  
    // while(parent[a]>0)
    // {
    //     v.push_back(a);
    //     a=parent[a];
    // }
    // for(int i=0;i<v.size();i++)
    //   parent[v[i]]=a;
    // return a;
    if (parent[a] < 0)
        return a;
    else
        return parent[a] = find(parent[a]);
}

void Union(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a != b)
    {
        parent[a] += parent[b]; //adding size of set b to set a
        parent[b] = a;          //making a , parent of new set
    }
}

int main()
{
    int n;
    cin >> n;

    // Here if element in parent array has -ve value then it is root and the mod of that is size of that set
    // else if element in parent array has +ve value then it is not root and value of that index is it's parent
    parent.resize(n + 1);
    // parent[0] = -1;
    for (int i = 0; i <= n; i++)
        parent[i] = -1; //initializing

    Union(0, 1);
    Union(1, 2);
    Union(2, 3);
    for (int i = 0; i <= n; i++)
        cout << parent[i] << " ";
}