/* https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
Given root of tree, as well as the two nodes in the tree, find LCA. So we are sure that
the two nodes exist in the tree.

Time complexity of solution: O(N)
space complexity: O(h) -> recursion also requires memory on the stack.
*/

/*
How to explain to an interviewer:
-> Suppose I am a node in the tree. If I try to find p and q in my left and right child, and both return with some values, that means both sub-trees have either p or q in them. And then I must be the lowest common ancestor. In this case, I should return myself to the user.
-> If only one subtree returns a value, then there are two cases: either the lca is somewhere below me, and I should return the lca upstream as well. 
   Or the lca is somewhere above me, and in that case too, I should tell my upstream that I do have one of p or q within my subtree.
-> If I am myself p or q, in that case too I should return to my upstream that I am p or q.

This works because we know both p and q exist. So root of tree must be the lca if nothing else. 
*/

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root==NULL || root==p || root==q) return root;
    TreeNode* left = lca(root->left, p, q);
    TreeNode* right = lca(root->right, p, q);
    if(left && right) return root;
    return left?left:right;
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
    cout << lca(root, node1, node2)->val << endl; // 3
    cout << lca(root, root->left->right->right, root->left)->val << endl; // 5
}

