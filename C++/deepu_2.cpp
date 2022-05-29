/*
1 2 3 4 5 6
1 6 2 5 3 4

1 2 3 4 5
1 5 2 4 3
*/


#include<bits/stdc++.h>

using namespace std;

struct Node {
	int val;
	struct Node* next;
};

struct Node* reverseList(struct Node* head){
	struct Node* prev, *curr, *next;
	curr = head;
	prev = NULL;
	while(curr){
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

struct Node* ReOrderList(struct Node* head){
	int len = 0;
	struct Node* temp = head;
	while(temp){
		len++;
		temp = temp->next;
	}
	if(len < 3){
		return head;
	}
	struct Node* secondHalf = head;
	struct Node* prev;
	int move = (len+1)/2;
	while(move){
		prev = secondHalf;
		secondHalf = secondHalf->next;
		move--;
	}
 	prev->next = NULL;
	secondHalf = reverseList(secondHalf);
	cout << secondHalf->val << endl;
	struct Node* toRet = new struct Node();
	struct Node* curr = toRet;
	struct Node* itA = head;
	struct Node* itB = secondHalf;
	while(itA){
		curr->next = itA;
		itA = itA->next;
		curr = curr->next;
		if(itB){
			curr->next = itB;
			itB = itB->next;
			curr = curr->next;
		}
	}
	return toRet->next;
} 

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	int x;
	struct Node* head = new struct Node();
	struct Node* curr = head;
	for(int i=0; i<n; i++){
		cin >> x;
		struct Node* node = new struct Node();
		node->val = x;
		curr->next = node;
		curr = curr->next;
	}

	head->next = ReOrderList(head->next);
	curr = head->next;
	while(curr){
		cout << curr->val << " " ;
		curr = curr->next;
	}
	return 0;
}
