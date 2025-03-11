/*
https://leetcode.com/discuss/post/913010/facebook-phone-compare-linked-lists-by-m-56nr/

Compare strings stored in two Linked Lists . Return true if the strings stored in both the lists are simillar.

List 1 : "He" -> " llo" -> "wor" -> "ld"
List 2 : "H" --> "e" --> "ll" --> "owo" --> "r" --> "ld"

Both the lists store "helloworld".
*/

#include <iostream>
using namespace std;

struct Node {
    Node* next;
    string val;
    Node(string x): val(x), next(nullptr) {};
};

bool areTheySame(Node* l1, Node* l2) {
    if(l1==NULL || l2==NULL) return false;
    Node* p1 = l1; // pointer to node in l1
    Node* p2 = l2; // pointer to node in l2 
    int i1 = 0, i2=0; // pointer to string in p1 and p2.
    while(p1 && p2) {
        while(i1<p1->val.length() && i2<p2->val.length()){
            if(p1->val[i1] == p2->val[i2]) {
                i1++;
                i2++;
            } else {
                return false;
            }
        }
        // one or both of them have reached end of string in the node
        if(i1==p1->val.length()) {
            p1 = p1->next;
            i1 = 0; // reset index
        }
        if(i2==p2->val.length()) {
            p2 = p2->next;
            i2 = 0; // reset index
        }
    }
    // one of them still has some nodes. It would only be valid if all future nodes have value ""
    while(p1){
        if(p1->val!="") return false;
        p1 = p1->next;
    }
    while(p2){
        if(p2->val!="") return false;
        p2 = p2->next;
    }
    return true;
}


Node* constructList(vector<string> parts) {
    if(parts.size()==0) return NULL;
    Node* head = new Node(parts[0]);
    Node* insertNext = head;
    for(int i=1; i<parts.size(); i++) {
        insertNext->next = new Node(parts[i]);
        insertNext = insertNext->next;
    }
    return head;
}

int main() {
    // Test 1
    cout << areTheySame(constructList({"He", "llo", "wor", "ld"}), constructList({"H", "e", "ll", "owo", "r", "ld"})) << endl; // true
    cout << areTheySame(constructList({"He", "", "llowor", "ld"}), constructList({"H", "e", "ll", "owo", "r", "", "ld"})) << endl; // true
    cout << areTheySame(constructList({"He", "llo"}), constructList({"H", "e", "ll", "owo", "r", "ld"})) << endl; // false
    cout << areTheySame(constructList({"He", "llo"}), constructList({"H", "e", "ll", "o", ""})) << endl; // true
    cout << areTheySame(constructList({"He", "llo"}), constructList({"H", "e", "ll", "o", "", "w"})) << endl; // false
    cout << areTheySame(constructList({"He", "llo", "wor", "ld"}), constructList({})) << endl; // false
    cout << areTheySame(constructList({""}), constructList({""})) << endl; // true
   
}
