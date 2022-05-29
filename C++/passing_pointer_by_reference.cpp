#include <bits/stdc++.h>

using namespace std;

typedef struct ListNode ListNode;

struct ListNode {
	int data;
	ListNode* next;
};

void func(ListNode*& root){
	root = root->next;
	return;
}

int main(){
	ListNode* root = new ListNode();
	root->data = 1; 
	root->next = new ListNode();
	root->next->data=2;
	cout << root->data << endl;
	func(root);	
	cout << root->data << endl;
}
