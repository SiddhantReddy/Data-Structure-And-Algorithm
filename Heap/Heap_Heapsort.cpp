#include <iostream>
using namespace std;

// Heap structure
struct Heap
{
    int *array;
    int capacity; //max capacity of array
    int count;    //no of element present currently
    int heap_type;
};

// Creating Heap data structure
struct Heap *CreateHeap(int capacity, int heap_type)
{
    struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap)); //Memory for Heap struct
    if (h == NULL)
    {
        cout << "Memory Error";
        return NULL;
    }
    h->capacity = capacity;
    h->heap_type = heap_type;
    h->count = 0;
    h->array = (int *)malloc(sizeof(int) * h->capacity); //Memory for array
    if (h->array == NULL)
    {
        cout << "Memory Error";
        return NULL;
    }
    return h;
}

// Parent of a Node
int parent(struct Heap *h, int i) // 'i' = Index of Node whose parent is required
{
    if (i <= 0 || i >= h->count - 1)
        return -1;
    return (i - 1) / 2;
}

// Children of a Node
int leftchild(struct Heap *h, int i) // 'i' = Index of Node whose leftchild is required
{
    int left = 2 * i + 1;
    if (left >= h->count)
        return -1;
    return left;
}

int rightchild(struct Heap *h, int i) // 'i' = Index of Node whose rightchild is required
{
    int right = 2 * i + 2;
    if (right >= h->count)
        return -1;
    return right;
}

// Get Maximum element in Heap
int getmaximum(struct Heap *h)
{
    if (h->count == 0)
        return -1;      // Heap is empty
    return h->array[0]; //first element is maximum
}

// Resizing heap (Double the capacity)
void ResizeHeap(struct Heap *h)
{
    int *array_old = h->array;                               // Temporary pointer pointing to heap array
    h->array = (int *)malloc(sizeof(int) * h->capacity * 2); // Allocating space to new heap
    if (h->array == NULL)
    {
        cout << "Memory Error";
        return;
    }
    for (int i = 0; i < h->capacity; i++) // Copy element from old array
        h->array[i] = array_old[i];
    h->capacity *= 2;
    free(array_old);
}

void DisplayHeap(struct Heap *h)
{
    if (h == NULL)
        return;
    for (int i = 0; i < h->count; i++)
        cout << h->array[i] << " ";
}

// Heapify the element at location i
void percolateDown(struct Heap *h, int i)
{
    int l, r, maxele = i, temp;
    l = leftchild(h, i);
    r = rightchild(h, i);
    // cout << l << " " << r << " ";
    if (l == -1 && r == -1)
        return;
    if (l != -1 && h->array[l] > h->array[i]) // checking with left child
        maxele = l;
    else
        maxele = i;
    if (r != -1 && h->array[r] > h->array[maxele]) // checking with right child
        maxele = r;
    if (maxele != i) //if either of the child is greater
    {
        //swap i <--> maxele
        // swap(h->array[i], h->array[maxele]);
        temp = h->array[i];
        h->array[i] = h->array[maxele];
        h->array[maxele] = temp;
        // DisplayHeap(h);
        // cout << "\n";
        percolateDown(h, maxele); // heapify max index or child
    }
}

// Delete Data (Always root will be deleted i.e. maximum element)
int deleteMax(struct Heap *h)
{
    int data;
    if (h->count == 0) // No element to be deleted ,heap is empty
        return -1;
    data = h->array[0];                   // Root of Heap ,first element (Max element)
    h->array[0] = h->array[h->count - 1]; //Replace it with last element in Heap
    h->count--;                           // Decrease Heap size
    percolateDown(h, 0);                  // Heapify root (or) first element
    return data;
}

// Insert data in Heap (insert always at last and then heapify)
void insert(struct Heap *h, int data) //data to be inserted
{
    if (h->count == h->capacity) // Heap is full
        ResizeHeap(h);
    h->count++;
    int i = h->count - 1;                          // Last index
    while (i >= 0 && data > h->array[(i - 1) / 2]) // Compare data to it's parent
    {
        h->array[i] = h->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->array[i] = data; // Storing data in correct position
}

// Delete Heap
void DestroyHeap(struct Heap *h)
{
    if (h == NULL)
        return;
    free(h->array);
    free(h);
    h == NULL;
}

// Building Heap in O(n) Time , Heapify all Non-leaf nodes
void BuildHeap(struct Heap *h, int Arr[], int n) // Arr = array ,On which heap build on , n = size of heap
{

    if (h == NULL)
        return;
    while (n > h->capacity) // Resize until heap is large enough
        ResizeHeap(h);
    for (int i = 0; i < n; i++) // Copy all array element in heap array
        h->array[i] = Arr[i];
    h->count = n;
    // DisplayHeap(h);
    // cout << "\n";
    for (int i = (n - 1) / 2; i >= 0; i--) // (n-1)/2 ,First non-leaf Node
        percolateDown(h, i);
}

void Heapsort(int Arr[], int n, int heap_type)
{
    struct Heap *h = CreateHeap(n, heap_type);
    int old_size, temp;
    BuildHeap(h, Arr, n);
    old_size = h->count;
    for (int i = n - 1; i >= 0; i--)
    {
        temp = h->array[0];
        h->array[0] = h->array[h->count - 1];
        h->array[i] = temp;
        h->count--;
        percolateDown(h, 0);
    }
    h->count = old_size;
    cout << "After Sort  :";
    DisplayHeap(h);
}

int main()
{
    int Arr[] = {1, 5, 14, 2, 10, 21, 18, 3, 11, 8, 7, 12};
    int capacity = 12;
    int heap_type = 1;
    struct Heap *h = CreateHeap(capacity, heap_type);
    // cout<<h->capacity<<" ";
    // cout<<"\n"<<h->count<<" ";
    // BuildHeap(h, Arr, capacity);
    cout << "Before Sort :";
    for (int i = 0; i < capacity; i++)
        cout << Arr[i] << " ";
    cout << "\n";
    Heapsort(Arr, capacity, heap_type);
  
    return 0;
}
