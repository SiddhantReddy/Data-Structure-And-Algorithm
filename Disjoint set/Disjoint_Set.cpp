#include <bits/stdc++.h>
using namespace std;

void initialize(vector<int> &Arr, vector<int> &size, int N)
{
    // N is size of Disjoint set
    for (int i = 0; i < N; i++)
    {
        Arr.push_back(i);
        size.push_back(1);
    }
}

int root(vector<int> &Arr, int i)
{
    while (Arr[i] != i) //chase parent of current element until it reaches root.
    {
        i = Arr[i];
    }
    return i;
}

bool find(vector<int> &Arr, int A, int B) // To find if two set are connected
{
    if (root(Arr, A) == root(Arr, B)) //if A and B have same root,means they are connected.
        return true;
    else
        return false;
}

void weighted_union(vector<int> &Arr, vector<int> &size, int A, int B)
{
    int root_A = root(Arr, A);
    int root_B = root(Arr, B);
    if (size[root_A] < size[root_B]) //Size of A is less than Size of B
    {
        Arr[root_A] = Arr[root_B];
        size[root_B] += size[root_A];
    }
    else //Size of B is less than Size of A
    {
        Arr[root_B] = Arr[root_A];
        size[root_A] += size[root_B];
    }
}

int main()
{
    vector<int> Arr;
    vector<int> size;
    int N=4;
    initialize(Arr,size,N);
    
    weighted_union(Arr,size,0,1);
    weighted_union(Arr,size,1,2);
    weighted_union(Arr,size,2,3);
    
    for(int i=0;i<N;i++)
      cout<<Arr[i]<<" ";
      cout<<endl;
    for(int i=0;i<N;i++)
      cout<<size[i]<<" ";
    return 0;
}
