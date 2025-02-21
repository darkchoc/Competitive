/*
Creating a question on my own:
Given a tree, print node in reverse preorder.
Example:
                3
            /       \
           5        1
        /     \   /   \
       6       2 0     8
              / \
             7   4 

Reverse Pre-Order = right, left, root
PreOrder = 3,5,6,2,7,4,1,0,8
Reverse = 8,0,1,4,7,2,6,5,3

While the simple way is to simply do pre-order traversal and then store and nodes and print in reverse order, but instead of storing the nodes in an array, implement recursion.

*** 
This "reverse prorder" is the idea that is used in Flatten List question:
https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
 
*/
#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

void preOrderTraversal(TreeNode* root) {
    if(root==NULL) return;
    preOrderTraversal(root->right);
    preOrderTraversal(root->left);
    cout << root->val << ", ";
}

int main() {
    // Build tree
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    preOrderTraversal(root);
    cout << endl;
}