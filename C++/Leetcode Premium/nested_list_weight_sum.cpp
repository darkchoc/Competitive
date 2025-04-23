/*
Given a nested list of integers, return the sum of all integers in the list weighted by their depth.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: 10 
Explanation: Four 1's at depth 2, one 2 at depth 1.
Example 2:

Input: [1,[4,[6]]]
Output: 27 
Explanation: One 1 at depth 1, one 4 at depth 2, and one 6 at depth 3; 1 + 4*2 + 6*3 = 27.
*/


#include <iostream>
using namespace std;
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
 class NestedInteger {
    private:
        vector<NestedInteger> list;
        int val;
        bool islist;
    public:
        // Constructor initializes an empty nested list.
        NestedInteger() {
            list.clear();
            islist = true;
        }
    
        // Constructor initializes a single integer.
        NestedInteger(int value) {
            val = value;
            islist = false;
        }

        // @return true if this NestedInteger holds a single integer, rather than a nested list.
        bool isInteger() {
            return !islist;
        }


        // @return the single integer that this NestedInteger holds, if it holds a single integer
        // Return null if this NestedInteger holds a nested list
        int getInteger(){
            return islist?-1:val;
        }
    
        // Set this NestedInteger to hold a single integer.
        void setInteger(int value) {
            val = value;
            islist = false;
        }
    
        // Set this NestedInteger to hold a nested list and adds a nested integer to it.
        void add(NestedInteger ni) {
            list.push_back(ni);
            islist=true;
        }
    
        // @return the nested list that this NestedInteger holds, if it holds a nested list
        // Return empty list if this NestedInteger holds a single integer
        vector<NestedInteger> getList() {
            return list;
        }
};

int recurse(NestedInteger input, int depth) {
    if(input.isInteger()) return input.getInteger() * depth;
    // now we know it is list, so traverse over list and increase depth for elements within list
    int sum = 0;
    for(int i=0; i<input.getList().size(); i++){
        sum += recurse(input.getList()[i], depth+1);
    }
    return sum;
}

int solve(NestedInteger input) {
    return recurse(input, 0);
}

int main(){ 
    NestedInteger input(5);
    cout << solve(input) << endl; // 0 -> since no list, this is level 0. Input:5

    NestedInteger input2;
    NestedInteger nestedInput2(5);
    input2.add(nestedInput2);
    cout << solve(input2) << endl; // 5 -> since 5 is nested at level 1. Input: [5]

    NestedInteger input3;
    NestedInteger nestedInput3_1(1); // 1
    input3.add(nestedInput3_1); // [1]
    NestedInteger nestedInput3_2; 
    NestedInteger nestedInput3_2_1(2); // 2
    NestedInteger nestedInput3_2_2(3); // 3
    nestedInput3_2.add(nestedInput3_2_1); // [2]
    nestedInput3_2.add(nestedInput3_2_2); // [2,3]
    input3.add(nestedInput3_2); // [1, [2,3]]
    NestedInteger nestedInput3_3;
    NestedInteger nestedInput3_3_1(4); // 4
    nestedInput3_3.add(nestedInput3_3_1); // [4]
    NestedInteger nestedInput3_3_2;
    NestedInteger nestedInput3_3_2_1(5); // 5
    nestedInput3_3_2.add(nestedInput3_3_2_1); // [5]
    nestedInput3_3.add(nestedInput3_3_2); // [4, [5]]
    input3.add(nestedInput3_3); // [1,[2,3],[4,[5]]]
    NestedInteger nestedInput3_6(6); // 6
    input3.add(nestedInput3_6); // [1,[2,3],[4,[5]],6]
    cout << solve(input3) << endl; // 1*1 + 2*2 + 3*2 + 4*2 + 5*3 + 6*1 = 40
}