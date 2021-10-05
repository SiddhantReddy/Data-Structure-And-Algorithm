#include <bits/stdc++.h>
using namespace std;

#define range 10

void countSort(vector<int> &arr, int n, int place)
{
    int i, freq[range] = {0};
    int output[n];
    for (i = 0; i < n; i++)
        freq[(arr[i] / place) % range]++;
    for (i = 1; i < range; i++)
        freq[i] += freq[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[freq[(arr[i] / place) % range] - 1] = arr[i];
        freq[(arr[i] / place) % range]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
void radixSort(vector<int> &arr, int n, int maxx)
{
    //maxx is the maximum element in the array
    int mul = 1;
    while (maxx)
    {
        countSort(arr, n, mul);
        mul *= 10;
        maxx /= 10;
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
    cout << "Array before sorting : ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    radixSort(arr, n, 1e9);
    cout << "\nArray after sorting : ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}