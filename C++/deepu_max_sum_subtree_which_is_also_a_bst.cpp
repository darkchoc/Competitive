#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x), left(NULL), right(NULL) {};  
};

typedef struct TreeNode TreeNode;


TreeNode* makeSampleTree(){
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(3);
	root->right = new TreeNode(2);
	root->left->left = new TreeNode(5);
	root->left->right = new TreeNode(4);
	root->left->left->left = new TreeNode(3);
	root->left->left->right = new TreeNode(6);
	root->left->left->left->left = new TreeNode(2);
	root->left->left->left->right = new TreeNode(4);
	root->right->right = new TreeNode(10);
	root->right->right->left = new TreeNode(9);
	root->right->right->left->left = new TreeNode(8);
	root->right->right->right = new TreeNode(12);
	return root;
}

void recurse(TreeNode* current, int &ans, int &min_, int &max_, bool &valid, int &sum){
	if(current->left==NULL && current->right==NULL){
		//leaf node. Is valid BST.
		ans = max(ans, current->val);
		min_ = current->val;
		max_ = current->val;
		sum = current->val;
		valid = true;
		return;
	}
	bool left_valid = false, right_valid = false;
	int min_left=INT_MIN, max_left=INT_MIN, min_right=INT_MAX, max_right=INT_MAX;
	int sum_left=INT_MIN, sum_right=INT_MIN;
	if(current->left && current->right){
		recurse(current->left, ans, min_left, max_left, left_valid, sum_left);
		recurse(current->right, ans, min_right, max_right, right_valid, sum_right);
		if(left_valid && right_valid && current->val > max_left && current->val < min_right){
			//valid bst
			sum = sum_left + sum_right + current->val;
			ans = max(ans, sum);
			min_ = min_left;
			max_ = max_right;
			valid = true;
			return;
		} else {
			valid = false;
			return;
		}
	} else if(current->left){
		recurse(current->left, ans, min_left, max_left, left_valid, sum_left);
		if(left_valid && current->val > max_left){
			//valid bst
			sum = sum_left + current->val;
			ans = max(ans, sum);
			min_ = min_left;
			max_ = current->val;
			valid = true;
			return;
		} else {
			valid = false;
			return;
		}
	} else if(current->right){
		recurse(current->right, ans, min_right, max_right, right_valid, sum_right);
		if(right_valid && current->val < min_right){
			//valid bst
			sum = sum_right + current->val;
			ans = max(ans, sum);
			min_ = current->val;
			max_ = max_right;
			valid = true;
			return;
		} else {
			valid = false;
			return;
		}
	}
	return;
}

int solve (TreeNode* A){
	if(A==NULL)
		return 0;
	int ans = INT_MIN;
	int min_, max_, sum;
	bool valid = false;
	recurse(A, ans, min_, max_, valid, sum);
	return ans;
}


int main(){
	TreeNode* root = makeSampleTree();
	cout << solve(root);
}