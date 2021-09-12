#include<bits/stdc++.h>
using namespace std;

class TreeNode {
  public:
    int data;
  TreeNode * left;
  TreeNode * right;
};

// Function to create a new Node in heap
TreeNode* GetNewNode(int data) {
	TreeNode* newNode = new TreeNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

class AVLTree {
  public:
    TreeNode * root;
  AVLTree() {
    root = NULL;
  }
  // Get Height  
  int height(TreeNode * root) {
    if (root == NULL)
      return -1;
    else {
      /* compute the height of each subtree */
      int lheight = height(root -> left);
      int rheight = height(root -> right);

      /* use the larger one */
      if (lheight > rheight)
        return (lheight + 1);
      else return (rheight + 1);
    }
  }

  // Get Balance factor of node N  
  int getBalanceFactor(TreeNode * root) {
    if (root == NULL)
      return -1;
    return height(root -> left) - height(root -> right);
  }

  TreeNode * rightRotate(TreeNode * y) {
    TreeNode * x = y -> left;
    TreeNode * T2 = x -> right;

    // Perform rotation  
    x -> right = y;
    y -> left = T2;

    return x;
  }

  TreeNode * leftRotate(TreeNode * root) {
    TreeNode * y = root -> right;
    TreeNode * T2 = y -> left;

    // Perform rotation  
    y -> left = root;
    root -> right = T2;

    return y;
  }

  TreeNode * Insert(TreeNode * root,int data) {
    if (root == NULL) {
      root = GetNewNode(data);
      return root;
    }

    if (data < root -> data) {
      root -> left = Insert(root -> left,data);
    } else if (data > root -> data) {
      root -> right = Insert(root -> right, data);
    } else {
      cout << "No duplicate datas allowed!" << endl;
      return root;
    }

    int bf = getBalanceFactor(root);
    // Left Left Case  
    if (bf > 1 && data < root -> left -> data)
      return rightRotate(root);
    // Right Right Case  
    if (bf < -1 &&data > root -> right -> data)
      return leftRotate(root);
    // Left Right Case  
    if (bf > 1 && data > root -> left -> data) {
      root -> left = leftRotate(root -> left);
      return rightRotate(root);
    }
    // Right Left Case  
    if (bf < -1 && data < root -> right -> data) {
      root -> right = rightRotate(root -> right);
      return leftRotate(root);
    }
    /* return the (unchanged) node pointer */
    return root;

  }

  TreeNode * mindataNode(TreeNode * root) {
    TreeNode * current = root;
    /* loop down to find the leftmost leaf */
    while (current -> left != NULL) {
      current = current -> left;
    }
    return current;
  }

  TreeNode * Delete(TreeNode * root, int value) {
    // base case 
    if (root == NULL) {
      return NULL;
    }
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    else if (value < root -> data) {
      root -> left = Delete(root -> left, value);
    }
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (value > root -> data) {
      root -> right = Delete(root -> right, value);
    }
    // if key is same as root's key, then This is the node to be deleted 
    else {
      // node with only one child or no child 
      if (root -> left == NULL) {
        TreeNode * temp = root -> right;
        delete root;
        return temp;
      } else if (root -> right == NULL) {
        TreeNode * temp = root -> left;
        delete root;
        return temp;
      } else {
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        TreeNode * temp = mindataNode(root -> right);
        // Copy the inorder successor's content to this node 
        root -> data = temp -> data;
        // Delete the inorder successor 
        root -> right = Delete(root -> right, temp -> data);
        //deleteNode(r->right, temp->data); 
      }
    }

    int bf = getBalanceFactor(root);
    // Left Left Imbalance/Case or Right rotation 
    if (bf == 2 && getBalanceFactor(root -> left) >= 0)
      return rightRotate(root);
    // Left Right Imbalance/Case or LR rotation 
    else if (bf == 2 && getBalanceFactor(root -> left) == -1) {
      root -> left = leftRotate(root -> left);
      return rightRotate(root);
    }
    // Right Right Imbalance/Case or Left rotation	
    else if (bf == -2 && getBalanceFactor(root -> right) <= -0)
      return leftRotate(root);
    // Right Left Imbalance/Case or RL rotation 
    else if (bf == -2 && getBalanceFactor(root -> right) == 1) {
      root -> right = rightRotate(root -> right);
      return leftRotate(root);
    }
    return root;
  }

  void display(TreeNode* root){
    // using BFS(breadth first search) to display tree in 
    // form of array ('#' => NULL node)
    queue<TreeNode*> q;
    q.emplace(root);
	cout<<"AVL Tree : ";
    while(!q.empty()){
        TreeNode* curr=q.front();
        q.pop();
        if(curr==NULL){
            cout<<"#"<<" ";
            continue;
        }
        cout<<curr->data<<" ";
        q.emplace(curr->left);
        q.emplace(curr->right);
    } 
	cout<<"\n\n"; 
}

};

int main() {
  AVLTree obj;
  cout<<"Inserting node 25 ,20 ,30 ,35 ,45 ... \n\n";
  obj.root=obj.Insert(obj.root,25);
  obj.root=obj.Insert(obj.root,20);
  obj.root=obj.Insert(obj.root,30);
  obj.root=obj.Insert(obj.root,35);
  obj.root=obj.Insert(obj.root,45);
  obj.display(obj.root);
  cout<<"Delete node 20 ... \n\n";
  obj.root=obj.Delete(obj.root,20);
  obj.display(obj.root);
  cout<<"Inserting node 55, 65 ... \n\n";
  obj.root=obj.Insert(obj.root,55);
  obj.root=obj.Insert(obj.root,65);
  obj.display(obj.root);
  cout<<"Delete node 30 ... \n\n";
  obj.root=obj.Delete(obj.root,30);
  obj.display(obj.root);
  cout<<"Inserting node 75 ... \n\n";
  obj.root=obj.Insert(obj.root,75);
  obj.display(obj.root);

  return 0;
}