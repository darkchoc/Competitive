/*
https://leetcode.com/discuss/interview-question/4778515/Amazon-OA-question

Count Maximum Profitable Groups
A team of analysts at Amazon needs to analyze the stock prices of Amazon over a period of several months.

A group of consecutively chosen months is said to be maximum profitable if the price in its first or last month is the maximum for the group. More formally, a group of consecutive months [l, r] (1 ≤ l ≤ r ≤ n) is said to be maximum profitable if either:

stockPrice[l] = max(stockPrice[l], stockPrice[l + 1], ..., stockPrice[r])
or, stockPrice[r] = max(stockPrice[l], stockPrice[l + 1], ..., stockPrice[r])
Given prices over n consecutive months, find the number of maximum profitable groups which can be formed. Note that the months chosen must be consecutive, i.e., you must choose a subarray of the given array.

Function Description

Complete the function countMaximumProfitableGroups function in the editor below.

countMaximumProfitableGroups has the following parameter:

int stockPrice[n]: the stock prices
Returns

long integer: the number of maximum profitable groups

Example 1:

Input: stockPrice = [3, 1, 3, 5]
Output: 10
Explanation:

The 10 possible groups are [3], [3, 1], [1, 3], [1], [3, 1, 3], [1, 3, 5], [1], [3, 1, 3, 5], [3, 5], [5].
In each group, the maximum price is in either the first or last position.

Example 2:

Input: stockPrice = [1, 5, 2]
Output: 5
Explanation:

There are 6 possible groups: [1], [1, 5], [5], [5, 2], [2].
Only [1, 5, 2], is not maximum profitable because its maximum value 5 is not at either end of the group.

Example 3: 

Input: stockPrice = [2, 3, 2]
Output: 5
Explanation:

All 5 groups other than prices [2, 3, 2] are maximum profitable. In [2, 3, 2], the
maximum value 3 is neither the first nor the last element. Return 5.

Constraints:
1 ≤ n ≤ 5 * 105
1 ≤ stockPrice[i] ≤ 108
*/

#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> price) {
    int n = price.size();
    vector<int> leftBigger (n);
    vector<int> rightBigger (n);
    stack<int> st;
    for(int i=0; i<n; i++){
        while(!st.empty() && price[st.top()] <= price[i])
            st.pop();
        if(st.empty()) leftBigger[i] = -1;
        else leftBigger[i] = st.top();
        st.push(i); 
    }
    while(!st.empty()) st.pop();
    for(int i=n-1; i>=0; i--){
        while(!st.empty() && price[st.top()] < price[i])
            st.pop();
        if(st.empty()) rightBigger[i] = n;
        else rightBigger[i] = st.top();
        st.push(i);
    }
    int ans = 0;
    for(int i=0; i<n; i++)
        ans += (i - leftBigger[i]) + (rightBigger[i]-i) - 1; // -1 to exclude double count of single element subarray.
    return ans;
}

int main(){
    cout << solve({3,1,3,5}) << endl; // 10
    cout << solve({1,5,2}) << endl; // 5
    cout << solve({2,3,2}) << endl; // 5
    cout << solve({3,1,5,6,3,4,2,4,5,6,4,3,1}) << endl; // 48
}