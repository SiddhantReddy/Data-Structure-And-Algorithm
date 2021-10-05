#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& arr, int start, int mid, int end)
{
    int temp[end - start + 1];
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= end)
        temp[k++] = arr[j++];
    
    for (i = start; i <= end; i += 1)
        arr[i] = temp[i - start];
}

void mergeSort(vector<int>& arr, int start, int end)
{

    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
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
    mergeSort(arr,0,n-1);
    cout<<"\nArray after sorting : "; 
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}