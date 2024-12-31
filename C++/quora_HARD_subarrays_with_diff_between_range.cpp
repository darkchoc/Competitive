/*
ASKED AS FOLLOWUP IN ALGO ROUND (wasn't expected to solve as I had already solved first question).
Given an array, find number of subarrays where the difference between the max and min of the subarray is between p and q.

Example: arr = [1,4,3,7,8,9,3], p = 4, q = 7
Output: 13
Explanation:
[1,4,3,7],[4,3,7],[3,7]
[1,4,3,7,8],[4,3,7,8],[3,7,8]
[4,3,7,8,9],[3,7,8,9]
[4,3,7,8,9,3],[3,7,8,9,3],[7,8,9,3],[8,9,3],[9,3]

Approach: Break down the question into: find subarrays where diff between max and min of the subarray is less than equal to k.
Then answer is simply diff_less_than_k(q) - diff_less_than_k(p-1);
*/

#include <bits/stdc++.h>
using namespace std;

int num_subarrays_with_diff_less_than_equal_to_k(vector<int> &arr, int k){
    int l = 0, r = 0;
    int count = 0;
    // Basically, we want to store max and min between l and r. This can be done using deques. When we add r, we add r to both DQs (max and min) and remove appropriate elements from back before adding r.
    // Now we need to see if the max - min between subarray pointed by l and r have diff <= k. If not, we need to move l forward. For this, we need to check that if any of the DQs have l as their first element, we must remove it.
    deque<int> maxDq;
    deque<int> minDq;
    while(r < arr.size()){
        while(!maxDq.empty() && arr[maxDq.back()] <= arr[r])
            maxDq.pop_back();
        maxDq.push_back(r);
        while(!minDq.empty() && arr[minDq.back()] >= arr[r])
            minDq.pop_back();
        minDq.push_back(r);
        while(!maxDq.empty() && arr[maxDq.front()] - arr[minDq.front()] > k){
            // IMPORTANT: need to add !maxDp.empty() here as it was breaking in the case where k = -1. (when both p and q = 0).
            if(maxDq.front()==l)
                maxDq.pop_front();
            if(minDq.front()==l)
                minDq.pop_front();
            l++;
        }
        // now all subarrays that start from l to r and end at r will have diff <= k
        count += (r-l+1);
        r++;
    }
    return count;
}

int num_subarrays_with_diff_between_range(vector<int> arr, int p, int q){
    return num_subarrays_with_diff_less_than_equal_to_k(arr, q) - num_subarrays_with_diff_less_than_equal_to_k(arr, p-1);
}

int main(){
    cout << num_subarrays_with_diff_between_range({1,4,3,7,8,9,3}, 4, 7) << endl; // 13
    cout << num_subarrays_with_diff_between_range({2,4,1,0,9,4,3,7,10,3,12,3,5}, 6, 10) << endl; // 54
    cout << num_subarrays_with_diff_between_range({2,4,3}, 1, 1) << endl; // 1
    cout << num_subarrays_with_diff_between_range({2,2,4,3}, 0, 0) << endl; // 5
}