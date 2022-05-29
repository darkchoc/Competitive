/*
Given two binary trees T1 and T2, you have to find minimum number of insertions to be done in T1 to make it structurally identical to T2. Return -1 if not possible.

Notes

Assume insertions are done in a normal fashion in the BSTs.
Assume while inserting, if the value of a node v is equal to value being inserted, we insert it in left subtree of node v.
You can insert any positive or negative integer.

Input 1: 

T1:       10
         / \
        9   20

T2:       5
         / \
        2   7
       /
      1

If you insert 8 into T1, it will be structurally identical to T2. Hence answer is 1.


Input 2: 

T1:       10
         / \
        9   20

T2:       5
           \
            7

You cannot make T1 and T2 structurally identical. Hence answer is -1.
*/

#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x), left(NULL), right(NULL) {};
};

typedef struct TreeNode TreeNode;

TreeNode* makeTree1(){
	TreeNode* root = new TreeNode(10);
	root->right = new TreeNode(20);
	root->left = new TreeNode(9);
	return root;
}

TreeNode* makeTree2(){
	TreeNode* root = new TreeNode(5);
	root->right = new TreeNode(7);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(1);
	return root;
}

TreeNode* makeTree4(){
	TreeNode* root = new TreeNode(5);
	root->left = new TreeNode(7);
	return root;
}

int count(TreeNode* A){
	if(A==NULL)
		return 0;
	return count(A->left) + count(A->right) + 1;
}

int solve(TreeNode* A, TreeNode* B){
	if(B==NULL){
		if(A==NULL)
			return 0;	
		else
			return -1;
	} else if(A==NULL){
		return count(B);
	}
	int left = solve(A->left, B->left);
	int right = solve(A->right, B->right);
	if(left==-1 || right==-1)
		return -1;
	else return left+right;
}

int main(){
	TreeNode* tree1 = makeTree1();
	TreeNode* tree2 = makeTree2();
	TreeNode* tree3 = makeTree1();
	TreeNode* tree4 = makeTree4();
	cout << solve(tree1, tree2);
	cout << endl;
	cout << solve(tree3, tree4);
	cout << endl;
	return 0;
}