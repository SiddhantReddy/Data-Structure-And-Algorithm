#include <bits/stdc++.h>
using namespace std;

// Node class for Linkedlist node
class Node
{
public:
    int data;
    Node *next;

    // Default constructor
    Node()
    {
        data = 0;
        next = NULL;
    }

    // Parameterised Constructor
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

// Linked list class
class Linkedlist
{
    Node *head;

public:
    // Default constructor
    Linkedlist() { head = NULL; }

    // Function to insert a new node.
    void insertNode(int data)
    {
        // Create the new Node.
        Node *newNode = new Node(data);

        // if linked list is Null, then new node is head
        if (head == NULL)
        {
            head = newNode;
            return;
        }
        // find last node of linked list
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next; // Update temp
        }
        temp->next = newNode; // Insert at the last.
    }

    // Function to print the linked list.
    void printList()
    {
        Node *temp = head;
        // Check for empty linked list
        if (head == NULL)
        {
            cout << "List empty" << endl;
            return;
        }
        // Traversing the linked list.
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    // Function to remove duplicates
    void removeDuplicates()
    {
        // map to store values node values
        unordered_set<int> mp;

        struct Node *curr = head;
        struct Node *prev = NULL;
        while (curr != NULL)
        {
            // If current value is seen before
            if (mp.find(curr->data) != mp.end())
            {
                prev->next = curr->next;
            }
            else
            {
                mp.insert(curr->data); // insert value in map
                prev = curr;
            }
            curr = prev->next;
        }
    }
};

// Driver Code
int main()
{
    Linkedlist linkedlist;

    // Inserting nodes in linked list
    linkedlist.insertNode(1);
    linkedlist.insertNode(2);
    linkedlist.insertNode(3);
    linkedlist.insertNode(1);
    linkedlist.insertNode(3);
    linkedlist.insertNode(2);
    linkedlist.insertNode(3);
    linkedlist.insertNode(4);
    linkedlist.insertNode(4);
    linkedlist.insertNode(5);

    cout << "\n";
    cout << "Linked list Before removing duplicates : ";
    linkedlist.printList();
    cout << "\n";
    cout << "\n";

    linkedlist.removeDuplicates();

    cout << "Linked list after removing duplicates :  ";
    linkedlist.printList();
    cout << "\n";
    cout << "\n";

    return 0;
}