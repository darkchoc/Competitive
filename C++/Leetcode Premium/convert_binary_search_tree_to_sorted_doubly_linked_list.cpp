/*
Convert a BST to a sorted circular doubly-linked list in-place. Think of the left and right pointers as synonymous to the previous and next pointers in a doubly-linked list.

Let's take the following BST as an example, it may help you understand the problem better:
            4
          /   \ 
         2     5
       /  \
      1    3

We want to transform this BST into a circular doubly linked list. Each node in a doubly linked list has a predecessor and successor. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.

The figure below shows the circular doubly linked list for the BST above. The "head" symbol means the node it points to is the smallest element of the linked list.

head -> 1 <-> 2 <-> 3 <-> 4 <-> 5 <-
        ^                           |
        |---------------------------|
 
 
Specifically, we want to do the transformation in place. After the transformation, the left pointer of the tree node should point to its predecessor, and the right pointer should point to its successor. We should return the pointer to the first element of the linked list.

The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.

                 4.<.....
                 ^ .  \ .
head      >2< .  | .   \ .
    \    / . \ . | .    \ .
     \  / .   \ .| .     >5
      >1<.     >3 <.

--- successor
... predecessor

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
All the values of the tree are unique.
*/

#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node() {}
    Node(int val): val(val), left(NULL), right(NULL) {}
};

void printList(Node* head) {
    if(head==NULL) {
        cout << "Null" << endl;
        return;
    }
    Node* temp = head;
    do{
        cout << temp->val << " ";
        temp = temp->right;
    } while(temp!=head);
    cout << endl;
}


void inorder_traversal(Node* root, Node* &prev){
    if(root==NULL) return;
    inorder_traversal(root->left, prev);
    root->left = prev;
    prev = root;
    inorder_traversal(root->right, prev);
}

Node* treeToDoublyList(Node* root){
    /*
    Initial thoughts. Do inorder traversal while keeping track of prev node. So after traversal, we'll have:
    1 <- 2 <- 3 <- 4 <- 5. At the end, prev will be pointing to 5. Set the right pointers then.
    We'll get: 1<->2<->3<->4<->5. Finally set pointers between 1 and 5 and return pointer to 1.
    */
   if(root==NULL) return NULL;
   Node* prev = NULL;
   // prev is a variable, but since we want to pass it from reference, we should pass it as Node* &prev. Otherwise even if you change it a call, when the 
   // call returns, it will continue pointing to the old node it was pointing to in upstream function.
    inorder_traversal(root, prev);

    // now prev points to last node in list
    Node* last = prev;
    // Set right pointers while traversing from right to left.
    while(prev->left){
        prev->left->right = prev;
        prev = prev->left;
    }
    // Now prev points to first element.
    Node* head = prev;
    // Connect head and last
    head->left = last;
    last->right = head;
    return head;
}

void inorder_traversal_better(Node* root, Node* &prev, Node* &head){
    if(root==NULL) return;
    inorder_traversal_better(root->left, prev, head);
    root->left = prev;
    if(prev==NULL){
        // first node
        head = root;
    } else {
        prev->right = root; // setting right pointer here as well.
    }
    prev = root;
    inorder_traversal_better(root->right, prev, head);
}

Node* treeToDoublyListBetter(Node* root) {
    if(root==NULL) return NULL;
    Node* head;
    Node* prev = NULL;
    // start inorder traversal, and this time, set both left and right
    inorder_traversal_better(root, prev, head);
    // now just connect head and prev
    head->left = prev;
    prev->right = head;
    return head;
}

int main() {
    // Test 1
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(5);
    root->left->left = new Node(1);
    root->left->right = new Node(3);
    printList(treeToDoublyList(root)); // 1 2 3 4 5

    // Test 2
    Node* root2 = new Node(3);
    printList(treeToDoublyList(root2)); // 3

    // Test 3
    Node* root3 = NULL;
    printList(treeToDoublyList(root3)); // NULL

    // Test 1.1
    Node* root4 = new Node(4);
    root4->left = new Node(2);
    root4->right = new Node(5);
    root4->left->left = new Node(1);
    root4->left->right = new Node(3);
    printList(treeToDoublyListBetter(root4)); // 1 2 3 4 5

    // Test 2.1
    Node* root5 = new Node(3);
    printList(treeToDoublyListBetter(root5)); // 3

    // Test 3.1
    Node* root6 = NULL;
    printList(treeToDoublyListBetter(root6)); // NULL
}