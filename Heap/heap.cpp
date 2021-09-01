#include <bits/stdc++.h>
using namespace std;

#define CAPACITY 10000

class Heap
{
private:
    int top;
    vector<int> array;

public:
    Heap()
    {
        array.resize(CAPACITY);
        top = -1;
    }

    int parent(int i) // 'i' = Index of Node whose parent is required
    {
        if (i <= 0 || i >= top - 1)
            return -1;
        return (i - 1) / 2;
    }

    // Children of a Node
    int leftchild(int i) // 'i' = Index of Node whose leftchild is required
    {
        int left = 2 * i + 1;
        if (left > top)
            return -1;
        return left;
    }

    int rightchild(int i) // 'i' = Index of Node whose rightchild is required
    {
        int right = 2 * i + 2;
        if (right > top)
            return -1;
        return right;
    }

    // Get Maximum element in Heap
    int GetHighestPriority()
    {
        if (top == -1)
            return -1;   // Heap is empty
        return array[0]; //first element is maximum
    }

    // Delete Data (Always root will be deleted i.e. maximum element)
    int DeleteHighestPriority()
    {
        int data;
        if (top== -1) // No element to be deleted ,heap is empty
            return -1;
        data = array[0];                   // Root of Heap ,first element (Max element)
        array[0] = array[top]; //Replace it with last element in Heap
        top--;                           // Decrease Heap size
        percolateDown(0);                  // Heapify root (or) first element
        return data;
    }

    void displayHeap()
    {
        if (top == -1)
            return;
        for (int i = 0; i <= top; i++)
            cout << array[i] << " ";
        cout << "\n";
    }
    void insert(int data) //data to be inserted
    {
        top++;
        int i = top;                               // Last index
        while (i > 0 && data > array[(i - 1) / 2]) // Compare data to it's parent
        {
            array[i] = array[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        array[i] = data; // Storing data in correct position
    }

    // Heapify the element at location i
    void percolateDown(int i)
    {
        int l, r, maxele = i, temp;
        l = leftchild(i);
        r = rightchild(i);
        // cout << l << " " << r << " ";
        if (l == -1 && r == -1)
            return;
        if (l != -1 && array[l] > array[i]) // checking with left child
            maxele = l;
        else
            maxele = i;
        if (r != -1 && array[r] > array[maxele]) // checking with right child
            maxele = r;
        if (maxele != i) //if either of the child is greater
        {
            //swap i <--> maxele
            // swap(array[i], array[maxele]);
            temp = array[i];
            array[i] = array[maxele];
            array[maxele] = temp;
            // DisplayHeap(h);
            // cout << "\n";
            percolateDown(maxele); // heapify max index or child
        }
    }

    // Building Heap in O(n) Time , Heapify all Non-leaf nodes
    void buildHeap(vector<int> &a, int n) // Arr = array ,On which heap build on , n = size of heap
    {

        for (int i = 0; i < n; i++) // Copy all array element in heap array
            array[i] = a[i];
        top = n - 1;
        // DisplayHeap(h);
        // cout << "\n";
        for (int i = (n - 1) / 2; i >= 0; i--) // (n-1)/2 ,First non-leaf Node
            percolateDown(i);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    Heap heap;
    heap.buildHeap(a, n);
    heap.displayHeap();
    heap.insert(15);
    heap.displayHeap();
    cout << "MAX :" << heap.GetHighestPriority() << "\n";
    heap.insert(22);
    heap.displayHeap();
    cout << "MAX :" << heap.GetHighestPriority() << "\n";
    heap.DeleteHighestPriority();
    heap.displayHeap();
    cout << "MAX :" << heap.GetHighestPriority() << "\n";
    heap.DeleteHighestPriority();
    heap.displayHeap();
    cout << "MAX :" << heap.GetHighestPriority() << "\n";

    return 0;
}