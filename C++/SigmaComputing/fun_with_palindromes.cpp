/*
https://leetcode.com/discuss/interview-question/341992/Sigma-Computing-or-Online-Assessment-2019
Question 3 above

The score of a string s is given by the maximum product of two non-overlapping palindromic subsequences of s. 

eg: if s = "attract", the max score we can achieve is "atta" * "c" = 4*1 = 4
NOTICE: the substring from which subsequence is being taken, that substring shouldn't overlap with other substring. Basically, the subsequences cannot be interleaving. Coz if that would have been the case, then in above example, we could have got: "ata" * "tct" = 3*3 = 9 as answer.  THIS IS THE MOST IMPORTANT THING IN THIS QUESTION, otherwise it would become way tooooo hard.

Contraints:
0 <= s.length() <= 3000

Example 2:
s = acdapmpomp
Ans = 15
Reason: pmpmp * aca = 5*3 = 15 

Example 3:
s = axbawbaseksqke
Ans = 25
Reason: ababa * ekske = 5*5 = 25

Approach: We want to identify longest palindromic subsequence between s[0...i] and s[i+1...n-1] for each i. We can simply create dp[i][j] = longest palindromic subsequence in s[i..j]
if s[i]==s[j]
    dp[i][j] = dp[i+1][j-1] + 2
else:
    dp[i][j] = max(dp[i+1][j], dp[i][j-1])
*/

#include <bits/stdc++.h>
using namespace std;

int solve(string s){
    if(s.length() <= 2) return s.length()==2; // 0 if s.length()=0 or 1, 1 if s.length()=2.
    int n = s.length();
    vector<vector<int> > dp (n, vector<int> (n, 0));
    for(int len=1; len<=n; len++){
        for(int i=0, j=i+len-1; j<n; i++, j++){
            if(i==j) dp[i][j]=1;
            else if(s[i]==s[j]) dp[i][j] = 2 + dp[i+1][j-1];
            else dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
        }
    }
    int ans = 1;
    for(int i=0; i<n-1; i++){
        ans = max(dp[0][i]*dp[i+1][n-1], ans);
    }
    return ans;
}

int main(){
    cout << solve("attract") << endl; // 4
    cout << solve("acdapmpomp") << endl; // 15
    cout << solve("axbawbaseksqke") << endl; // 25
    cout << solve("abcd") << endl; // 1
}