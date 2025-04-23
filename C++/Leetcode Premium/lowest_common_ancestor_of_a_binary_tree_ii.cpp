/*
Question: https://leetcode.ca/all/1644.html
Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p and q. If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.

Time complexity: O(n)
Space complexity: O(h) -> recursion uses memory on stack
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

TreeNode* lca_helper(TreeNode* root, TreeNode* p, TreeNode* q, int &found) {
    if(root==NULL) return NULL;
    if(root==p || root==q) {
        found++;
        if(found==2) return root;
        // else just call lca_helper on children of this node as well.
    }
    TreeNode* left = lca_helper(root->left, p, q, found);
    TreeNode* right = lca_helper(root->right, p, q, found);
    if(left && right) return root;
    // if root was p or q itself, then instead of return left/right, return root itself
    if(root==p || root==q) return root; 
    // if above is not true, that means this subtree has neither, or just one of the nodes of interest.
    return left?left:right;
}

int lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    // In this case, even if we reach at p or q, we still need to traverse the subtree below it as there can be a case when p or q is itself the LCA. We can also keep a found variable to check if both nodes have been found or not. 
    int found = 0;
    TreeNode* potentialAns = lca_helper(root, p, q, found);
    return found<2?-1:potentialAns->val; 
}


int main() {
    // Build tree
    /*
                3
            /       \
           5        1
        /     \   /   \
       6       2 0     8
              / \
             7   4 
    */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    TreeNode* node1 = root->left->right->left; // 7
    TreeNode* node2 = root->right->left; // 0
    cout << lca(root, node1, node2) << endl; // 3
    cout << lca(root, root->left->right->right, root->left) << endl; // 5
    cout << lca(root, root->left, new TreeNode(10)) << endl; // -1
    cout << lca(root, new TreeNode(10), new TreeNode(15)) << endl; // -1
}

