#include <bits/stdc++.h>
using namespace std;

int partition (vector<int>&arr,int low,int high)
{
    // pivot - Element at right most position
    int pivot = arr[high];  
    int i = (low - 1);
    for (int j = low; j <= high-1; j++)
    {
        // If current element is smaller than the pivot, swap the element with pivot
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>&arr,int low,int high)
{
    if (low < high)
    {
        int pivot_index = partition(arr, low, high);

        quickSort(arr, low, pivot_index - 1);  // sort before pivot_index
        quickSort(arr, pivot_index + 1, high); // sort after pivot_index
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
    quickSort(arr,0,n-1);
    cout<<"\nArray after sorting : "; 
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}