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

// Inorder traversal in BST
void inorder(BstNode* root){
    if(!root) return ;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
// preorder traversal in BST
void preorder(BstNode* root){
    if(!root) return ;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
// postorder traversal in BST
void postorder(BstNode* root){
    if(!root) return ;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
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
    cout<<"Inorder   : ";
    inorder(root);
    cout<<"\n"; 
    cout<<"Preorder  : ";
    preorder(root);
    cout<<"\n"; 
    cout<<"Postorder : ";
    postorder(root);

}