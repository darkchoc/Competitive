/*
Question: https://leetcode.com/discuss/interview-question/380650/Bloomberg-or-Phone-or-Candy-Crush-1D
Write a function to crush candy in one dimensional board. In candy crushing games, groups of like items are removed from the board. In this problem, any sequence of 3 or more like items should be removed and any items adjacent to that sequence should now be considered adjacent to each other. This process should be repeated as many time as possible. You should greedily remove characters from left to right.

Example 1:
Input: "aaabbbc"
Output: "c"
Explanation:
1. Remove 3 'a': "aaabbbbc" => "bbbbc"
2. Remove 4 'b': "bbbbc" => "c"

Example 2:
Input: "aabbbacd"
Output: "cd"
Explanation:
1. Remove 3 'b': "aabbbacd" => "aaacd"
2. Remove 3 'a': "aaacd" => "cd"

Example 3:
Input: "aabbccddeeedcba"
Output: ""
Explanation:
1. Remove 3 'e': "aabbccddeeedcba" => "aabbccdddcba"
2. Remove 3 'd': "aabbccdddcba" => "aabbcccba"
3. Remove 3 'c': "aabbcccba" => "aabbba"
4. Remove 3 'b': "aabbba" => "aaa"
5. Remove 3 'a': "aaa" => ""

Example 4:
Input: "aaabbbacd"
Output: "acd"
Explanation:
1. Remove 3 'a': "aaabbbacd" => "bbbacd"
2. Remove 3 'b': "bbbacd" => "acd"

The interviewer asked me to consider it not a string but as a sequence of elements. Also, since the data can be huge, we don't want to use extra space. A stack based approach (check bloomberg_practice1.cpp) would cause us to use O(n) space. 

Then, additonal requirment was that we want to change this sequence itself and not create a new sequence. When I said that should I use substr function, he said it would be too time consuming -> O(n). I should probably choose some other data structure. 

I asked if we can get input in the form of a doubly linked list, and he agreed to it. The removal of repeated elements would take O(1).  He asked me to use std::list.
*/

#include <bits/stdc++.h>
using namespace std;

void candyCrush(list<char> &input){
    if(input.size() < 3)
        return;
    list<char>::iterator left = input.begin();
    list<char>::iterator right = input.begin();
    while(right != input.end()){
        int lengthOfRepeatedSequence = 0;
        while(right != input.end() && (*left)==(*right)){
            lengthOfRepeatedSequence++;
            right++;
        }
        if(lengthOfRepeatedSequence < 3){
            left = right;
        } else {
            input.erase(left, right); //[left, right)
            left = right; 

            //Consider case: AABBBAAC -> we remove B's to get AAAC. Right would be pointing to 3rd A.
            //Consider another case: BABBBAAC  -> we remove B's to get BAAAC. Right would be pointing to 2nd A.
            while(left != input.begin() && (*left)==(*right)){
                left--;
            }
            //After the while loop, left would be pointing to 1st A for AAAC and B for BAAAC. We need to check that if left = right value, then we can simply set right = left, but if not, we can increment left by one and start iteration from there (set right = left). 

            //Agreed, there would be some extra traversal, as we'll traverse the list again that the left pointer just traversed, but it would be max 1 or 2 characters as if anytime we get more than 3 characters, we are anyway removing them. This was another area where interviewer commented as I was trying to avoid setting right = left and wanted to calculate before hand what the repeatedsequence count was for this reverse traversal. 
            if((*left)==(*right)){
                right = left;
            } else {
                left++;
                right = left;
            }
        }
    }
}

void printList(list<char> &input){
    list<char>::iterator it = input.begin();
    while(it!=input.end()){
        cout << *it << " ";
        it++;
    }
    cout << endl;
    return;
}

int main(){
    list<char> input = {'A', 'B', 'B', 'B', 'C', 'C'};
    candyCrush(input);
    printList(input);

    input = {'A', 'B', 'C', 'C', 'C', 'B', 'B'};
    candyCrush(input);
    printList(input);

    input = {'A', 'B', 'C', 'C', 'C', 'B', 'B', 'A', 'A', 'C'};
    candyCrush(input);
    printList(input);
}

