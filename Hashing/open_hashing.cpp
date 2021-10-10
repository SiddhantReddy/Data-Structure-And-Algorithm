#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define TABLESIZE 10

class Hash
{
    vector<list<int>> table;
public:
    // Constructor
    Hash()
    {
        table.resize(TABLESIZE);
    }

    // insert key into hash table
    void insertItem(int key)
    {
        int tableindex = hashFunction(key);
        table[tableindex].push_front(key);
    }

    // delete key from hash table
    void deleteItem(int key)
    {
        int tableindex = hashFunction(key);
        for (auto it = table[tableindex].begin(); it != table[tableindex].end(); it++)
        {
            if (*it == key)
            {
                table[tableindex].erase(it);
                break;
            }
        }
    }

    bool searchitem(int key)
    {
        int tableindex = hashFunction(key);
        for (auto it = table[tableindex].begin(); it != table[tableindex].end(); it++)
        {
            if (*it == key)
            {
                return true;
            }
        }
        return false;
    }

    // hash function to map values to key
    int hashFunction(int x)
    {
        return (x % TABLESIZE);
    }

    void displayHash()
    {
        for (int ind = 0; ind < TABLESIZE; ind++)
        {
            cout << "Index " << ind;
            for (auto x : table[ind])
                cout << " --> " << x;
            cout << "\n";
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Hash *hashtable = new Hash();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        hashtable->insertItem(x);
    }
    hashtable->displayHash();
    cout << "\n\n";

    auto startfirst = high_resolution_clock::now();
    for (int times = 0; times < 10000; times++)
    {
        for (int i = 0; i < 10; i++)
        {
            int x;
            cin >> x;
            auto start = high_resolution_clock::now();
            hashtable->searchitem(x);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            if(times==0)
            cout << "Search time for " << x << "  " << duration.count() << " ms\n";
        }
    }
    auto stopfirst = high_resolution_clock::now();
    cout << "Answer : Intentional \n\n";
 
    auto startsecond = high_resolution_clock::now();
    for (int times = 0; times < 10000; times++)
    {
        for (int i = 0; i < 10; i++)
        {
            int x;
            cin >> x;
            auto start = high_resolution_clock::now();
            hashtable->searchitem(x);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            if(times==0)
            cout << "Search time for " << x << "  " << duration.count() << " ms\n";
        }
    }
    auto stopsecond = high_resolution_clock::now();
    cout << "Answer : Intentional \n\n";
    auto durationfirst = duration_cast<microseconds>(stopfirst - startfirst);
    auto durationsecond = duration_cast<microseconds>(stopsecond - startsecond);

    cout<<"Average time for search in first set is "<<(double)durationfirst.count()/10000<<" ms"<<"\n";
    cout << "Reason : Because the first set of element above present in the front of Linked list \nand represent best case\n\n";
    cout<<"Average time for search in first set is "<<(double)durationsecond.count()/10000<<" ms"<<"\n";
    cout << "Reason : Because the second set element above mostly present in the last of Linked list \nand represent worst case\n\n";

}