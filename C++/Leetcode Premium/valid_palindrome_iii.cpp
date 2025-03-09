/*
1216. Valid Palindrome III
Given a string s and an integer k, find out if the given string is a K-Palindrome or not.

A string is K-Palindrome if it can be transformed into a palindrome by removing at most k characters from it.

Example 1:

Input: s = "abcdeca", k = 2
Output: true
Explanation: Remove 'b' and 'e' characters.
 

Constraints:

1 <= s.length <= 1000
s has only lowercase English letters.
1 <= k <= s.length
*/

/*
Initial thoughts: Find LCS of string and reverse of it. See if s.length() - LCS.length < k or not. 
*/

#include <iostream>
using namespace std;

bool valid_palindrome_iii(string s, int k){
    string rev = s;
    reverse(rev.begin(), rev.end());
    int n = s.length();
    vector<vector<int> > dp (n+1, vector<int> (n+1, -1)); //dp[i][j] - max lcs between s[0...i-1] && rev[0...j-1]
    // iterative
    // base case
    for(int i=0; i<=n; i++) {
        dp[i][0] = 0; // 0 common if rev has no characters
        dp[0][i] = 0; // 0 common if s has no characters
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++) {
            if(s[i-1]==rev[j-1])
                dp[i][j]=dp[i-1][j-1] + 1;
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return (n - dp[n][n] <= k);
}

bool valid_palindrome_iii_second_way(string s, int k) {
    int n = s.length();
    vector<vector<int> > dp (n, vector<int> (n, 0)); // dp[i][j] --> if i<=j, it gives max palindrome length from s[i...j]. If i>j, it will be 0.
    int maxLen = 0;
    for(int i=0; i<n; i++)
        dp[i][i]=1; 
    for(int i=n-2; i>=0; i--){
        for(int j=i+1; j<n; j++){
            if(s[i]==s[j])
                dp[i][j] = 2 + dp[i+1][j-1];
            else
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            maxLen = max(maxLen, dp[i][j]);
        }
    }
    return n-maxLen <= k;
}

int main() {
    cout << valid_palindrome_iii("abcdeca", 2) << endl; // true
    cout << valid_palindrome_iii("sielvxeks", 3) << endl; // false
    cout << valid_palindrome_iii("sielvxeks", 4) << endl; // false
    cout << valid_palindrome_iii_second_way("abcdeca", 2) << endl; // true
    cout << valid_palindrome_iii_second_way("sielvxeks", 3) << endl; // false
    cout << valid_palindrome_iii_second_way("sielvxeks", 4) << endl; // false
}

