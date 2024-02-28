/*
https://leetcode.com/discuss/interview-question/4467674/CAN-ANYONE-SOLVE-THIS/

https://www.reddit.com/r/leetcode/comments/18sm9nq/amazon_oa_need_help_with_this_greedy_problem/?rdt=44081

Given a collection of n cards. The i- th card (1 ≤ i ≤ n) has a number Ai on its front and a number Bi on its back. At the start, all the cards are facing upwards.
He wants to minimize the range of numbers (i. e. the difference between the maximum and minimum values) on the face- up side. He is allowed to flip a maximum of m cards. Flipping a card will transition Bi to the face up side and Ai to the back.
Help him find the minimum possible range after using at most m flips.

Input
The first line of the input consists of 2 integers n and m.
The next line contains n integers, i-th of which denotes Ai.
The next line contains n integers, i-th of which denotes Bi.

Constraints:
3 <= n <= 200000
1 <= m <= n
1 <= Ai, Bi <= 107
Output
Output a single integer, the minimum possible range.
Example
Input:
5 2
1 2 17 16 9
3 4 5 6 11

Output:
8

By flipping card 3 and 4, we get the face up numbers {1, 2, 5, 6, 9}. This makes range=9-1=8.

Some other test case:
2 2 
1 100
9999 10000
Output: 1

2 1
1 100
9999 10000
Output: 99

3 1
88 2 100
1 99999 3
Output: 86

3 2
88 2 100
1 99999 3
Output: 2


So the approach (as given here: https://www.reddit.com/r/leetcode/comments/18sm9nq/comment/kf8uiuj/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button)
 -> Combine numbers given in A and B into one list (num, index, 0/1 -> 0=belongs to A, 1=belongs to B) and sort them. In case A[i]==B[i], include A[i] only. 
 -> After sorting, we need to select a subarray from this combined list such that it contains all indices from 0 to n-1, and at most k elements from B. 
    -> Now, they argue that instead of counting number of elements picked from B, we rather count number of elements picked from A, and that should be greater than equal to n-m (m being most number of elements that can be picked from B). This is done because if we have two elements in the current window with the same index, we pick the one belonging to A and not B. I'm not sure why this decision.

    Basically if both A[i] and B[i] in current window, we consider A[i] and ignore B[i]. 

    So we keep incrementing right as long as not all indices are present in the window. Even if all are present, we keep incrementing as long as elements from A are < n-m. Once elements from A are >= n-m and all indices are also present, we update range = min(range, current max - current min). 

    But now question is how do we know what's current min? What if left is pointing to element B[i] but we have A[i] as well in current window? We need to increment left in this case. We keep incrementing left as long as all n indices are present and elements from A are >= n-m
*/

#include <bits/stdc++.h>

using namespace std;

int minRange(vector<int> A, vector<int> B, int m) {
    int n = A.size();
    vector<vector<int> > combined;
    for(int i=0; i<n; i++){
        combined.push_back({A[i], i, 0}); // 0 -> belongs to A.
        combined.push_back({B[i], i, 1}); // 1 -> belongs to B
    }
    sort(combined.begin(), combined.end());
    int range = combined[2*n-1][0] - combined[0][0]; // max range

    unordered_map<int, int> indices; // to keep track of indices
    for(int left=0, right=0, elementsOfA=0; right < 2*n; right++){
        if(combined[right][2]==0) elementsOfA++;
        indices[combined[right][1]]++; // indices[x] = 1 (means either A[i] or B[i] present), if 2 (both present)
        
        // now we have added combined[right] to our set, but we need to move left pointer forward as long as indices considered == n and elementsOfA >= n-m.

        while(indices.size()==n && elementsOfA >= n-m){
            range = min(range, combined[right][0] - combined[left][0]); // with every iteration of while loop, the range would get smaller. We don't need to worry about left pointing to B[i] when A[i] is already considered ahead. Because in that case, loop will execute one more time to throw B[i] out.
            // now we need to throw left out
            int ind = combined[left][1];
            indices[ind]--;
            if(indices[ind]==0) indices.erase(ind);

            if (combined[left][2] == 0) elementsOfA--;
            left++;
        }
    }
    return range;
}

int main() {
    cout << minRange({1, 2, 17, 16, 9}, {3, 4, 5, 6, 11}, 2) << endl; //8
    cout << minRange({88,2,100}, {1,99999,3}, 2) << endl; //2
    cout << minRange({88,2,100}, {1,99999,3}, 1) << endl; //86
    cout << minRange({5,8,4,3}, {1, 12, 3, 4}, 2) << endl; //4
    cout << minRange({1,100}, {9999,10000}, 2) << endl; //1
    cout << minRange({1,100}, {9999,10000}, 1) << endl; //99
}