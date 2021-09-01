#include<bits/stdc++.h>
using namespace std;

//Definition of Node for Binary search tree
struct BstNode {
	int data; 
	BstNode* left;
	BstNode* right;
};

// Function to create a new Node in heap
BstNode* GetNewNode(int data) {
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// To insert data in BST, returns address of root node 
BstNode* Insert(BstNode* root,int data) {
    // Tree is Empty , then create a new node
	if(root == NULL) {
		root = GetNewNode(data);
	}
	// if data is lesser, insert in left subtree. 
	else if(data <= root->data) {
		root->left = Insert(root->left,data);
	}
	// if data is greater, insert in right subtree. 
	else {
		root->right = Insert(root->right,data);
	}
    // return root of BST
	return root;
}

//Function to find minimum in a tree for delete operation in BST.  
BstNode* FindMin(BstNode* root)
{
	while(root->left != NULL) root = root->left;
	return root;
}

// Function to search a delete a value from tree.
BstNode* Delete(BstNode* root, int data) {
    // First find the node which you want to delete
	if(root == NULL) return root; 
	else if(data < root->data) root->left = Delete(root->left,data);
	else if (data > root->data) root->right = Delete(root->right,data);	
	else {  // you found the node
		// Node has No child
		if(root->left == NULL && root->right == NULL) { 
			delete root;
			root = NULL;
		}
		//Node has One child 
		else if(root->left == NULL) {
            // To free memory of BstNode we store it in temp for further deletion
			BstNode* temp = root;
			root = root->right;
            // free memory of BstNode
			delete temp;
		}
		else if(root->right == NULL) {
            // To free memory of BstNode we store it in temp for further deletion
			BstNode* temp = root; 
			root = root->left;
            // free memory of BstNode
			delete temp;
		}
		// Node has 2 children
		else { 
            // You can either replace Empty place with ,
            // 1 => Minimum node in right subtree (or)
            // 2 => Maximum node in left subtree 
			BstNode* temp = FindMin(root->right); // find minimum
			root->data = temp->data; // Change data of node to be deleted
			root->right = Delete(root->right,temp->data); // delete the right subtree node
		}
	}
	return root;
}

//To search an element in BST, returns true if element is found
bool Search(BstNode* root,int data) {
	// termination condition for recursion
    if(root == NULL) {
		return false;
	}
    // data is found
	else if(root->data == data) {
		return true;
	}
    // data is less than root, then search in left subtree
	else if(data <= root->data) {
		return Search(root->left,data);
	}
    // data is greater than root, then search in left subtree
	else {
		return Search(root->right,data);
	}
}

void display(BstNode* root){
    // using BFS(breadth first search) to display tree in 
    // form of array ('#' => NULL node)
    queue<BstNode*> q;
    q.emplace(root);
    while(!q.empty()){
        BstNode* curr=q.front();
        q.pop();
        if(curr==NULL){
            cout<<"#"<<" ";
            continue;
        }
        cout<<curr->data<<" ";
        q.emplace(curr->left);
        q.emplace(curr->right);
    }  

}

int main() {
	BstNode* root = NULL;  // Creating root of tree
    // populating tree
	root = Insert(root,25);
	root = Insert(root,40);
	root = Insert(root,35);
	root = Insert(root,20);	
	root = Insert(root,30);
	root = Insert(root,10);	
	root = Insert(root,15);
	root = Insert(root,5);  
	display(root);
    cout<<"\n";
    Delete(root,30);
    // Delete(root,5);
	display(root);
    cout<<"\n";

}