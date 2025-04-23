/*
https://leetcode.ca/2020-06-06-1650-Lowest-Common-Ancestor-of-a-Binary-Tree-III/
Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).
Each node will have a reference to its parent node. The definition for Node is below:
class Node {
    public int val;
    public Node left;
    public Node right;
    public Node parent;
}

The number of nodes in the tree is in the range [2, 10^5].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q
p and q exist in the tree.
*/
#include <iostream>
#include <set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(int x, TreeNode* p): val(x), parent(p), left(NULL), right(NULL) {}
};


int lca(TreeNode* p, TreeNode* q) {
    // We can simply travel upto the root for p and store all node values. Then do same for q and when we see an already seen node, that is the LCA.
    set<TreeNode*> ancestorsOfP;
    while(p) {
        ancestorsOfP.insert(p);
        p = p->parent;
    } 
    while(q){
        if(ancestorsOfP.find(q)!=ancestorsOfP.end()) return q->val;
        q = q->parent;
    }
    return -1; // will never be the case since both p and q always exist in the tree.
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
    cout << lca(root->left->right->left, root->right->left) << endl; // 3 (checking for node 7 and 0)
    cout << lca(root->left->right->right, root->left) << endl; // 5 (checking for node 4 and 5)
}

