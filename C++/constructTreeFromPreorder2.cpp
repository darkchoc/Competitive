/*
	Question: https://www.geeksforgeeks.org/construct-a-special-tree-from-given-preorder-traversal/
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {};
};

typedef struct TreeNode TreeNode;

void inorder(TreeNode* root){
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
    return;
}

void preorder(TreeNode* root){
    if(root==NULL)
        return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
    return;
}

void postorder(TreeNode* root){
    if(root==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
    return;
}

TreeNode* construct(vector<int> &pre, vector<char> &preLN){
    if(pre.size()==1)
        return new TreeNode(pre[0]);
    stack<TreeNode*> st;
    TreeNode* root = new TreeNode(pre[0]);
    st.push(root);
    int i = 1;
    while(!st.empty()){
        TreeNode* current = st.top();
        if(preLN[i]=='N'){
            if(current->left==NULL){
                current->left = new TreeNode(pre[i]);
                st.push(current->left);
            } else {
                current->right = new TreeNode(pre[i]);
                st.pop();
                st.push(current->right);
            }
        } else {
            if(current->left==NULL){
                current->left = new TreeNode(pre[i]);
            } else {
                current->right = new TreeNode(pre[i]);
                st.pop();
            }
        }
        i++;
    }
    return root;
}

int main() {
    vector<int> pre = {10,30,20,5,15};
    vector<char> preLN = {'N', 'N', 'L', 'L', 'L'};
    TreeNode* root = construct(pre, preLN);
    cout << "Inorder: "; 
    inorder(root);
    cout << endl;
    cout << "Preorder: ";
    preorder(root);
    cout << endl; 
    cout << "Postorder: "; 
    postorder(root); 
    cout << endl;
    return 0;
}
