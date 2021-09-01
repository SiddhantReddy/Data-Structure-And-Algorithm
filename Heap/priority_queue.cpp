#include <bits/stdc++.h>
using namespace std;

#define CAPACITY 10000

class Priority_queue
{
private:
    int top;
    vector<pair<int,int>> array; // pair<item, priority> 

public:
    Priority_queue()
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
        return array[0].first; //first element is maximum
    }

    // Delete Data (Always root will be deleted i.e. maximum element)
    void DeleteHighestPriority()
    {
        int item;
        if (top== -1) // No element to be deleted ,heap is empty
            return ;
        array[0].first = array[top].first; //Replace it with last element in Heap
        array[0].second = array[top].second;
        top--;                           // Decrease Heap size
        percolateDown(0);                  // Heapify root (or) first element
    }

    void displayPriority_queue()
    {
        if (top == -1)
            return;
        cout<<"priority_queue :";    
        for (int i = 0; i <= top; i++)
            cout <<"{"<< array[i].first << ":"<<array[i].second<<"} ";
        cout << "\n";
    }
    void insert(int item,int priority) //data to be inserted
    {
        top++;
        int i = top;                               // Last index
        while (i > 0 && priority > array[(i - 1) / 2].second) // Compare data to it's parent
        {
            array[i].first = array[(i - 1) / 2].first;
            array[i].second = array[(i - 1) / 2].second;
            i = (i - 1) / 2;
        }
        array[i].first = item; // Storing item in correct position
        array[i].second = priority; 
    }

    // Heapify the element at location i
    void percolateDown(int i)
    {
        int l, r, maxele = i, temp1,temp2;
        l = leftchild(i);
        r = rightchild(i);
        // cout << l << " " << r << " ";
        if (l == -1 && r == -1)
            return;
        if (l != -1 && array[l].second > array[i].second) // checking with left child
            maxele = l;
        else
            maxele = i;
        if (r != -1 && array[r].second > array[maxele].second) // checking with right child
            maxele = r;
        if (maxele != i) //if either of the child is greater
        {
            //swap i <--> maxele
            // swap(array[i], array[maxele]);
            temp1 = array[i].first;
            temp2 = array[i].second;
            array[i].first = array[maxele].first;
            array[i].second = array[maxele].second;
            array[maxele].first = temp1;
            array[maxele].second = temp2;
            // DisplayHeap(h);
            // cout << "\n";
            percolateDown(maxele); // heapify max index or child
        }
    }

    // Building Heap in O(n) Time , Heapify all Non-leaf nodes
    void buildPriority_queue(vector<pair<int,int>> &a, int n) // Arr = array ,On which heap build on , n = size of heap
    {

        for (int i = 0; i < n; i++){ // Copy all array element in heap array
            array[i].first = a[i].first;
            array[i].second = a[i].second;
        }
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
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        cin >> a[i].second;
    }

    Priority_queue pq;
    pq.buildPriority_queue(a, n);
    pq.displayPriority_queue();
    pq.insert(15,4);
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.insert(22,1);
    pq.displayPriority_queue();
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";
    pq.DeleteHighestPriority();
    pq.displayPriority_queue();
    cout << "Element with MAX priority :" << pq.GetHighestPriority() << "\n";

    return 0;
}