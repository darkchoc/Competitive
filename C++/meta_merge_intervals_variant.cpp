/*
https://leetcode.com/discuss/post/6654684/meta-e4-infra-us-pass-by-anonymous_user-37ip/

Variant of merge intervals where you are given two lists of intervals and have to merge them.

Think of it myself. So let's say we have two lists:
l1 -> {1,3}, {4,8}, {10, 15}
l2 -> {1,2}, {3, 5}, {8, 9}, {11, 12}, {13, 16}, {18, 20}

The result should be: 
{1,9}, {10, 16}, {18, 20}

*/

/*
Thoughts:

What if we merge both the lists? And then simply do merge intervals? 
*/

#include <iostream>
using namespace std;

void printMergedIntervals(vector<vector<int> > l1, vector<vector<int> > l2) {
    for(int i=0; i<l2.size(); i++)
        l1.push_back(l2[i]);
    // now do merge intervals on l1
    sort(l1.begin(), l1.end());
    vector<vector<int> > ans;
    vector<int> currentInterval = l1[0];
    int i = 1;
    while(i < l1.size()) {
        if(l1[i][0] <= currentInterval[1]){
            currentInterval[1] = max(currentInterval[1], l1[i][1]);
            i++;
        } else {
            ans.push_back(currentInterval);
            currentInterval = l1[i];
            i++;
        }
    }
    ans.push_back(currentInterval);
    // print ans
    for(int i=0; i<ans.size(); i++) {
        cout << "[" << ans[i][0] << "," << ans[i][1] << "], ";
    }
    cout << endl;
}


int main() {
    printMergedIntervals({{1,3}, {4,8}, {10, 15}}, {{1,2}, {2, 5}, {8, 9}, {11, 12}, {13, 16}, {18, 20}}); // {1,9}, {10, 16}, {18, 20}
    printMergedIntervals({{1,3}, {6,8}}, {{4,5}, {9,10}}); // {1,3}, {4,5}, {6,8}, {9,10}
}