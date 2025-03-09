/*
Given a node from a cyclic linked list which is sorted in ascending order, write a function to insert a value into the list such that it remains a cyclic sorted list. The given node can be a reference to any single node in the list, and may not be necessarily the smallest value in the cyclic list.

If there are multiple suitable places for insertion, you may choose any place to insert the new value. After the insertion, the cyclic list should remain sorted.

If the list is empty (i.e., given node is null), you should create a new single cyclic list and return the reference to that single node. Otherwise, you should return the original given node.

The following example may help you understand the problem better:

  1----
  ^    |
  |    ↓
  4<---3 < -- head

In the figure above, there is a cyclic sorted list of three elements. You are given a reference to the node with value 3, and we need to insert 2 into the list.

   1-->2
  ^    |
  |    ↓
  4<---3 < -- head


The new node should insert between node 1 and node 3. After the insertion, the list should look like this, and we should still return node 3.

Constraints:

The number of nodes in the list is in the range [0, 5 * 104].
-106 <= Node.val, insertVal <= 106
*/

#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int x): val(x), next(NULL) {};
};

Node* insertIntoSortedCircularList(Node* head, int x) {
    // if no node
    if(head==NULL){
        head = new Node(x);
        head->next = head;
        return head;
    }
    // if single node
    if(head->next==head){
        head->next = new Node(x);
        head->next->next = head;
        return head;
    }
    Node* temp = head;
    // start iteration
    // This do while is necessary coz consider we have 3 3 3 3, and x = 4. We would go the else part, and then nested else. And we would just keep
    // moving forward, never exiting. So we need to stop once we have completed one round. Now, if we use a while loop, we can't start with condition
    // temp != head, as then we won't even enter the loop. So we instead use do while loop.
    do{
        Node* nextNode = temp->next;
        if(temp->val > nextNode->val){ // we are at end of list. So temp is largest value, and nextNode is smallest
            if(x >= temp->val || x <= nextNode->val){
                temp->next = new Node(x);
                temp->next->next = nextNode;
                return head;
            } else {
                temp = temp->next;
            }
        } else {
            // temp->val <= nextNode->val : meaning we are somewhere in between the list
            if(x >= temp->val && x <= nextNode->val){
                temp->next = new Node(x);
                temp->next->next = nextNode;
                return head;
            } else {
                temp = temp->next;
            }
        }
    } while(temp!=head);
    //  if we exited the loop, means all elements are the same
    Node* nextNode = temp->next;
    temp->next = new Node(x);
    temp->next->next = nextNode;
    return head;
}

Node* insertIntoSortedCircularListConcise(Node* head, int x){
    Node* node = new Node(x);
    if(head==NULL){
        node->next = node;
        return node;
    }
    // If it is single node, head->next will be head
    Node* prev = head; 
    Node* curr = head->next;
    while(curr!=head){
        if((prev->val <= x && x <= curr->val)  // if x is between prev and next
        || (prev->val > curr->val && (x >= prev->val || x <= curr->val)) ) { // if prev is last of list and curr is beginning of list, and x is between them
            break;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    prev->next = node;
    node->next = curr;
    return head;
}


void printList(Node* head){
    Node* temp = head;
    do {
        cout << temp->val << " ";
        temp = temp->next;
    } while(temp != head);
    cout << endl;
}

Node* constructList(vector<int> nums){
    Node* head = new Node(nums[0]);
    Node* temp = head;
    for(int i=1; i<nums.size(); i++){
        temp->next = new Node(nums[i]);
        temp = temp->next;
    }
    temp->next = head;
    return head;
}

int main() {
    printList(insertIntoSortedCircularList(constructList({3,4,1}), 2)); // 3 4 1 2

    printList(insertIntoSortedCircularList(constructList({3}), 2)); // 3 2

    printList(insertIntoSortedCircularList(constructList({3,3,3}), 2)); // 3 3 3 2

    printList(insertIntoSortedCircularList(constructList({3,5,2}), 1)); // 3 5 1 2

    printList(insertIntoSortedCircularList(constructList({3,5,2}), 8)); // 3 5 8 2

    // Making it a bit more concise
    printList(insertIntoSortedCircularListConcise(constructList({3,4,1}), 2)); // 3 4 1 2

    printList(insertIntoSortedCircularListConcise(constructList({3}), 2)); // 3 2

    printList(insertIntoSortedCircularListConcise(constructList({3,3,3}), 2)); // 3 3 3 2

    printList(insertIntoSortedCircularListConcise(constructList({3,5,2}), 1)); // 3 5 1 2

    printList(insertIntoSortedCircularListConcise(constructList({3,5,2}), 8)); // 3 5 8 2

}