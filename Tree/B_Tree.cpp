#include <iostream>
using namespace std;

// A BTree node
class BTreeNode
{
    int *keys;     // An array of keys
    int t;         // Minimum degree
    BTreeNode **C; // An array of child pointers
    int n;         // Current number of keys
    bool leaf;     // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int t1, bool leaf1)
    {
        t = t1;
        leaf = leaf1;
        keys = new int[2 * t - 1];
        C = new BTreeNode *[2 * t];
        n = 0;
    }
    // A function that returns the index of the first key that is greater oe equal to k
    int findKey(int k)
    {
        int idx = 0;
        while (idx < n && keys[idx] < k)
            ++idx;
        return idx;
    }

    // A function to remove the key k from the sub-tree rooted with this node
    void remove(int k)
    {
        int idx = findKey(k);

        if (idx < n && keys[idx] == k)
        {
            if (leaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        }
        else
        {
            if (leaf)
            {
                cout << "The key " << k << " is does not exist in the tree\n";
                return;
            }
            bool flag = ((idx == n) ? true : false);
            if (C[idx]->n < t)
                fill(idx);
            if (flag && idx > n)
                C[idx - 1]->remove(k);
            else
                C[idx]->remove(k);
        }
        return;
    }

    // A function to remove the idx-th key from this node - which is a leaf node
    void removeFromLeaf(int idx)
    {
        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];
        n--;

        return;
    }
    // A function to get predecessor of keys[idx]
    int getPred(int idx)
    {
        BTreeNode *cur = C[idx];
        while (!cur->leaf)
            cur = cur->C[cur->n];
        return cur->keys[cur->n - 1];
    }

    int getSucc(int idx)
    {
        BTreeNode *cur = C[idx + 1];
        while (!cur->leaf)
            cur = cur->C[0];
        return cur->keys[0];
    }

    // A function to fill child C[idx] which has less than t-1 keys
    void fill(int idx)
    {
        if (idx != 0 && C[idx - 1]->n >= t)
            borrowFromPrev(idx);
        else if (idx != n && C[idx + 1]->n >= t)
            borrowFromNext(idx);
        else
        {
            if (idx != n)
                merge(idx);
            else
                merge(idx - 1);
        }
        return;
    }

    // A function to borrow a key from C[idx-1] and insert it  into C[idx]
    void borrowFromPrev(int idx)
    {

        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx - 1];
        for (int i = child->n - 1; i >= 0; --i)
            child->keys[i + 1] = child->keys[i];

        if (!child->leaf)
        {
            for (int i = child->n; i >= 0; --i)
                child->C[i + 1] = child->C[i];
        }
        child->keys[0] = keys[idx - 1];

        if (!child->leaf)
            child->C[0] = sibling->C[sibling->n];
        keys[idx - 1] = sibling->keys[sibling->n - 1];
        child->n += 1;
        sibling->n -= 1;
        return;
    }

    // A function to borrow a key from the C[idx+1] and place  it in C[idx]
    void borrowFromNext(int idx)
    {

        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx + 1];

        child->keys[(child->n)] = keys[idx];
        if (!(child->leaf))
            child->C[(child->n) + 1] = sibling->C[0];
        keys[idx] = sibling->keys[0];

        for (int i = 1; i < sibling->n; ++i)
            sibling->keys[i - 1] = sibling->keys[i];

        if (!sibling->leaf)
        {
            for (int i = 1; i <= sibling->n; ++i)
                sibling->C[i - 1] = sibling->C[i];
        }
        child->n += 1;
        sibling->n -= 1;
        return;
    }
 
    // A function to merge C[idx] with C[idx+1] C[idx+1] is freed after merging
    void merge(int idx)
    {
        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx + 1];

        child->keys[t - 1] = keys[idx];
        for (int i = 0; i < sibling->n; ++i)
            child->keys[i + t] = sibling->keys[i];

        if (!child->leaf)
        {
            for (int i = 0; i <= sibling->n; ++i)
                child->C[i + t] = sibling->C[i];
        }
        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];

        for (int i = idx + 2; i <= n; ++i)
            C[i - 1] = C[i];
        child->n += sibling->n + 1;
        n--;
        delete (sibling);
        return;
    }

    // A utility function to split the child y of this node
    // Note that y must be full when this function is called
    void splitChild(int i, BTreeNode *y)
    {
        BTreeNode *z = new BTreeNode(y->t, y->leaf);
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];
        if (y->leaf == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }
        y->n = t - 1;
        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];
        keys[i] = y->keys[t - 1];
        n = n + 1;
    }

    // Function to traverse all nodes in a subtree rooted with this node
    void traverse()
    {
        int i;
        for (i = 0; i < n; i++)
        {
            if (leaf == false)
                C[i]->traverse();
            cout << " " << keys[i];
        }
        if (leaf == false)
            C[i]->traverse();
    }

    // Function to search key k in subtree rooted with this node
    BTreeNode *search(int k)
    {
        int i = 0;
        while (i < n && k > keys[i])
            i++;
        if (keys[i] == k)
            return this;
        if (leaf == true)
            return NULL;
        return C[i]->search(k);
    }

    // A function to remove the idx-th key from this node - which is a non-leaf node
    void removeFromNonLeaf(int idx)
    {

        int k = keys[idx];
        if (C[idx]->n >= t)
        {
            int pred = getPred(idx);
            keys[idx] = pred;
            C[idx]->remove(pred);
        }
        else if (C[idx + 1]->n >= t)
        {
            int succ = getSucc(idx);
            keys[idx] = succ;
            C[idx + 1]->remove(succ);
        }
        else
        {
            merge(idx);
            C[idx]->remove(k);
        }
        return;
    }

    // A utility function to insert a new key in this node
    // The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k)
    {
        int i = n - 1;
        if (leaf == true)
        {
            while (i >= 0 && keys[i] > k)
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
            n = n + 1;
        }
        else 
        {
            while (i >= 0 && keys[i] > k)
                i--;
            if (C[i + 1]->n == 2 * t - 1)
            {
                splitChild(i + 1, C[i + 1]);
                if (keys[i + 1] < k)
                    i++;
            }
            C[i + 1]->insertNonFull(k);
        }
    }
    friend class BTree;
};

class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;           // Minimum degree
public:
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    // function to search a key in this tree
    BTreeNode *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int k)
    {
        if (root == NULL)
        {
            root = new BTreeNode(t, true);
            root->keys[0] = k; // Insert key
            root->n = 1;       // Update number of keys in root
        }
        else 
        {
            if (root->n == 2 * t - 1)
            {
                BTreeNode *s = new BTreeNode(t, false);
                s->C[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);
                root = s;
            }
            else 
                root->insertNonFull(k);
        }
    }

    void remove(int k)
    {
        if (!root)
        {
            cout << "The tree is empty\n";
            return;
        }
        root->remove(k);
        if (root->n == 0)
        {
            BTreeNode *tmp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->C[0];
            delete tmp;
        }
        return;
    }
};

int main()
{
    BTree btree(3); // A B-Tree with minimum degree 3
    cout<<"Inserting 1 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(1);
    cout<<"Inserting 2 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(2);
    cout<<"Inserting 4 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(4);
    cout<<"Inserting 6 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(6);
    cout<<"Inserting 7 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(7);
    cout<<"Inserting 3 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(3);
    cout<<"Inserting 10 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(10);
    cout<<"Inserting 12 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(12);
    cout<<"Inserting 19 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(19);
    cout<<"Inserting 15 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(15);
    cout<<"Inserting 14 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(14);
    cout<<"Inserting 13 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(13);
    cout<<"Inserting 8 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout<<"\n";
    btree.insert(8);

    cout<<"\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout << endl;

    btree.remove(7);
    cout<<"Removing 7 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout << endl;

    btree.remove(10);
    cout<<"Removing 10 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout << endl;

    btree.remove(19);
    cout<<"Removing 19 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout << endl;
    btree.remove(14);
    cout<<"Removing 14 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout << endl;
    btree.remove(15);
    cout<<"Removing 15 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout << endl;
    btree.remove(3);
    cout<<"Removing 3 ...\n";
    cout << "Traversal of Btree :  ";
    btree.traverse();
    cout << endl;
    return 0;
}
