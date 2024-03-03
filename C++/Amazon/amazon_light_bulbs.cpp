/*
https://leetcode.com/discuss/interview-question/4812451/SDE-AMAZON-OA


Solar power consumption has increased due to concern over global warming. Some Amazon offices have decided to replace some of their electricity-powered bulbs with solar-powered bulbs. Here electricity-powered means using a wired supply of electricity and solar-powered means powered by an
independent solar panel.
In one such office, the lights are arranged sequentially represented by a binary sequence, bulbs. The electricity-powered bulbs are represented by '0', and the solar powered bulbs are '1'.
It is desired to have as many solar-powered bulbs as possible, but the electricity-powered ones are brighter than the solar powered bulbs. An electricity-powered bulb can be replaced by a solar-powered bulb only if the new solar-powered bulb is not adjacent to a solar-powered bulb. More formally, a 0 can be replaced by a 1 if and only if it does not become adjacent to some other 1 on replacement.
Find the maximum number of solar powered bulbs that can be placed in the office. Not that the initial lighting may already have some adjacent solar powered bulbs. The constraint is only for new bulbs.
Note: Report the total number of solar powered bulbs and not just the number of replaced bulbs.

Example
Input: "1111110001"
Output: 8
Explanation: We can replace only one 0 (the one in the middle). So total ones = 8

Input: "1010000110000"
Output: 7
Explanation: Replace 3rd zero and 3rd last 0 and last 0. So total ones = 7

Input: "00100010100001001000010"
Output: 10
Explanation: We can get: (1)010(1)010100(1)0100100(1)010

Approach: So I'm thinking if we should first handle the leading and trailing 0's separately. 
For leading 0s, we can replace num_leading_0s/2
For trailing 0s, again same: num_trailing_0s/2
For groups of 0s trapped between 2 ones: (num_0s - 1)/2

*/

#include <bits/stdc++.h>
using namespace std;

int solve(string bulbs) {
    // trying to do it in one pass instead of 2 or 3.
    int countOnes = 0;
    int ans = 0;
    int countZerosInIntervals = 0;
    for(int i=0; i<bulbs.length(); i++) {
        if(bulbs[i]=='1'){
            if(countOnes == 0){
                // this is the first one. So countZerosInIntervals represents leading 0s.
                ans += countZerosInIntervals/2;
                countZerosInIntervals = 0;
            } else {
                // countZerosInIntervals represents 0s between 2 ones.
                ans += (countZerosInIntervals - 1)/2;
                countZerosInIntervals = 0;
            }
            countOnes++;
        } else {
            countZerosInIntervals++;
        }
    }
    if (countZerosInIntervals > 0){
        // these represent trailing 0s
        ans += countZerosInIntervals/2;
    }
    return ans + countOnes;
}

int main() {
    cout << solve("1111110001") << endl; //8
    cout << solve("1010000110000") << endl; //7
    cout << solve("00100010100001001000010") << endl; //10
}