/*
Probabilistic Preoder Traversal
Question 3 of : https://www.geeksforgeeks.org/directi-programming-questions/
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode{
	struct TreeNode* left;
	struct TreeNode* right;
	int data;
	TreeNode(int x): left(NULL), right(NULL), data(x){};
};

struct TreeNode* buildTree(vector<int> &nodes, int start, int end){
	if(start>end)
		return NULL;
	if(start==end)
		return new TreeNode(nodes[start]);
	struct TreeNode* node = new TreeNode(nodes[start]);
	int temp = start;
	temp++;
	if(nodes[start+1]>nodes[start]){
		//means right child written first
		while(temp<=end && nodes[temp]>nodes[start])
			temp++;
		node->right = buildTree(nodes, start+1, temp-1);
		node->left = buildTree(nodes, temp, end);
	}
	else{
		//means left child written first
		while(temp<=end && nodes[temp]<nodes[start])
			temp++;
		node->left = buildTree(nodes, start+1, temp-1);
		node->right = buildTree(nodes, temp, end);
	}
	return node;
}

void inorder(struct TreeNode* root){
	if(root==NULL)
		return;
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
	return;
}

void traverse(struct TreeNode* root, int &two_child){
	if(root==NULL)
		return;
	if(root->left!=NULL && root->right!=NULL)
		two_child++;
	traverse(root->left, two_child);
	traverse(root->right, two_child);
	return;
}

int helper(vector<int> &nodes, int n){
	struct TreeNode* root = buildTree(nodes, 0, n-1);
	cout << "Tree's inorder traversal is\n";
	inorder(root); 
	cout << "\nAns is:";
	int two_child = 0;
	traverse(root, two_child);
	return pow(2, two_child);
}

int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n;
		cin >> n; 
		vector<int> nodes(n);
		for(int i=0; i<n; i++)
			cin >> nodes[i];
		cout << helper(nodes, n) << endl;
	}
	return 0;
}