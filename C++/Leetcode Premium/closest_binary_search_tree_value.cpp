/*
https://leetcode.ca/all/270.html

Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:

Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.
Example:

Input: root = [4,2,5,1,3], target = 3.714286

    4
   / \
  2   5
 / \
1   3

Output: 4
*/

#include <iostream>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    int val;
    Node(int x): val(x), left(nullptr), right(nullptr) {};
};

int closestNodeVal(Node* root, double k) {
    Node* closest = root;
    double minDiff = (double)INT_MAX;
    while(root){
        if(root->val == k) {
            return k;
        } 
        double diff = abs((double)root->val - k);
        if(diff < minDiff || (diff==minDiff && root->val < closest->val)){
            minDiff = abs(root->val - k );
            closest = root;
        }
        if(root->val > k)
            root = root->left;
        else    
            root = root->right;
    }
    return closest->val;
}

int main() {
    // Test 1
    Node* root1 = new Node(4);
    root1->left = new Node(2); root1->left->left = new Node(1); root1->left->right = new Node(3);
    root1->right = new Node(5);
    cout << closestNodeVal(root1, 3.71) << endl; // 4
    cout << closestNodeVal(root1, 3.3) << endl; // 3
    cout << closestNodeVal(root1, 3.5) << endl; // 3
    cout << closestNodeVal(root1, 2) << endl; // 2
}

