#include <bits/stdc++.h>
using namespace std;

void selectionSort(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        int min_index=i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[min_index])
              min_index=j;
        }
        swap(arr[i],arr[min_index]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cout<<"Array before sorting : "; 
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    selectionSort(arr);
    cout<<"\nArray after sorting : "; 
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}