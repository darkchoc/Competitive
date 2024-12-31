/*
https://leetcode.com/discuss/interview-question/872882/Quora-or-Coding-Challenge-or-Number-of-pairs-whose-sum-is-a-power-of-2

Given an integer array arr, find how many pair of indices (i, j) are present in the array such that arr[i] + arr[j] is a power of 2. Note that i <= j. 

Example:
Input: [1, -1, 2, 3]
Output: 5 -> (0,0), (0,3), (1,2), (1,3), (2,2)

Approach:
Brute force would be to:
    for i in 0..n
        for j in i...n
            sum = arr[i] + arr[j]
            if( sum & (sum-1) == 0) ans++; // to check if power of 2, we can do sum & (sum - 1)

Can we do something better with maps or sets?
If we first sort the array, then start iterating it, then for each element, we can check:
    -> for sums in range (1, 2, 4, 8, ... power of 2 just less than 2*currentElement)

So algo would look like:
    sort(arr)
    mp = {}
    for i in 0..n
        mp[i]++; // since index can be paired with itself.
        p = 0
        while(pow(2, p) <= 2*arr[i]){
            s = pow(2, p)
            ans += mp[s - arr[i]]
        }

So time complexity of first solution is O(n^2)
Time complexity of second solution is O(n*log(max(arr)))

If numbers are going up to 2^31 (as they are ints), the time complexity for second algo would be O(n*31)
*/

#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> arr){
    sort(arr.begin(), arr.end());
    unordered_map<int, int> mp;
    int ans = 0;
    for(int i=0; i<arr.size(); i++){
        mp[arr[i]]++;
        int p = 0;
        while(pow(2, p) <= 2*arr[i]){
            int sum = pow(2, p);
            ans += mp[sum - arr[i]];
            p++;
        }
    }
    return ans;
}

int main(){
    cout << solve({1, -1, 2, 3}) << endl; // 5
    cout << solve({2, 4, 1, 3, -4, 5, -2}) << endl; // 8 -> (0,0), (1,1), (1,6), (2,2), (2,3), (3,5), (3,6), (4,5)
}
