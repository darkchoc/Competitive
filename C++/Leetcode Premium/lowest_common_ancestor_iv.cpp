/*
https://leetcode.ca/2020-07-02-1676-Lowest-Common-Ancestor-of-a-Binary-Tree-IV/
Given the root of a binary tree and an array of TreeNode objects nodes, return the lowest common ancestor (LCA) of all the nodes in nodes. All the nodes will exist in the tree, and all values of the tree's nodes are unique.

The number of nodes in the tree is in the range [2, 10^5].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q
p and q exist in the tree.

Initial thoughts: We can basically find lca of first two elements in the list,
then lca of that with third element in the list, 
then lca of above with fourth element in the list,
.. and so on.
The time complexity would be O(n^2) and this would cause TLE. Need to think something else.

So, second option is that if the current element = any of the elements given in the list, we return
the current element back. This way, if left subtree returns something and right subtree returns 
something, then we know root is the lca of at least these two, and we return the root.

Now further up in the tree, again if both children return something, then that node must be lca at least.
*/
#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(int x, TreeNode* p): val(x), parent(p), left(NULL), right(NULL) {}
};


TreeNode* lca_helper(TreeNode* root, set<TreeNode*> &setOfNodes) {
    if(root==NULL) return NULL;
    if(setOfNodes.find(root)!=setOfNodes.end()) return root;
    TreeNode* left = lca_helper(root->left, setOfNodes);
    TreeNode* right = lca_helper(root->right, setOfNodes);
    if(left && right) return root;
    return left?left:right;
}

int lca(TreeNode* root, vector<TreeNode*> nodes) {
    // We can simply travel upto the root for p and store all node values. Then do same for q and when we see an already seen node, that is the LCA.
    set<TreeNode*> setOfNodes {nodes.begin(), nodes.end()};
    return lca_helper(root, setOfNodes)->val;
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
    TreeNode* root = new TreeNode(3, NULL);
    root->left = new TreeNode(5, root);
    root->right = new TreeNode(1, root);
    root->left->left = new TreeNode(6, root->left);
    root->left->right = new TreeNode(2, root->left);
    root->left->right->left = new TreeNode(7, root->left->right);
    root->left->right->right = new TreeNode(4, root->left->right);
    root->right->left = new TreeNode(0, root->right);
    root->right->right = new TreeNode(8, root->right);
    cout << lca(root, {root->left->right->left, root->right->left}) << endl; // 3 (checking for node 7 and 0)
    cout << lca(root, {root->left->right->right, root->left}) << endl; // 5 (checking for node 4 and 5)
    cout << lca(root, {root->left->left, root->left->right->left, root->left->right->right}) << endl; // 5 (checking for 6, 7, 4)
    cout << lca(root, {root->left->left, root->left->right->left, root->right->left}) << endl; // 3 (checking for 6, 7, 0)
}

