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
    for(int i=0; i<n; i++)
        dp[i][i]=1; 
    for(int i=n-2; i>=0; i--){
        for(int j=i+1; j<n; j++){
            if(s[i]==s[j])
                dp[i][j] = 2 + dp[i+1][j-1];
            else
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
        }
    }
    return n-dp[0][n-1] <= k;
}

bool valid_palindrome_iii_third_way(string s, int k) {
    int n = s.length();
    vector<vector<int> > dp (n, vector<int> (n, 0)); // dp[i][j] -> if i <= j, gives max palindrome length from s[i...j]. If i>j, it will be 0
    for(int l=1; l<=n; l++) { // l = length of string in consideration
        for(int i=0; i+l-1 < n; i++) { // i -> starting point
            if(l==1) dp[i][i]=1; // handling this case separately as otherwise in below case, we'll check for dp[1][-1] (when i=0) and dp[n][n-2] (when i=n-1)
            else if(s[i]==s[i+l-1])
                dp[i][i+l-1] = 2 + dp[i+1][i+l-1-1];
            else
                dp[i][i+l-1] = max(dp[i][i+l-1-1], dp[i+1][i+l-1]);
        }
    }
    return n - dp[0][n-1] <= k;
}

int main() {
    cout << valid_palindrome_iii("abcdeca", 2) << endl; // true
    cout << valid_palindrome_iii("sielvxeks", 3) << endl; // false
    cout << valid_palindrome_iii("sielvxeks", 4) << endl; // true
    cout << valid_palindrome_iii_second_way("abcdeca", 2) << endl; // true
    cout << valid_palindrome_iii_second_way("sielvxeks", 3) << endl; // false
    cout << valid_palindrome_iii_second_way("sielvxeks", 4) << endl; // true
    cout << valid_palindrome_iii_third_way("abcdeca", 2) << endl; // true
    cout << valid_palindrome_iii_third_way("sielvxeks", 3) << endl; // false
    cout << valid_palindrome_iii_third_way("sielvxeks", 4) << endl; // true
}

/*
class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        vector<int> memo(s.length(), 0);

        // To store the previous required values from memo.
        int temp, prev;

        // Generate all combinations of `i` and `j` in the correct order.
        for (int i = s.length() - 2; i >= 0; i--) {
            // 'prev' stores the value at memo[i+1][j-1];
            prev = 0;
            for (int j = i + 1; j < s.length(); j++) {
                // Store the value of memo[i+1][j] temporarily.
                temp = memo[j];

                // Case 1: Character at `i` equals character at `j`
                if (s[i] == s[j])
                    memo[j] = prev;

                // Case 2: Character at `i` does not equal character at `j`.
                // Either delete character at `i` or delete character at `j`
                // and try to match the two pointers using recursion.
                // We need to take the minimum of the two results and add 1
                // representing the cost of deletion.
                else

                    // memo[j] will contain the value for memo[i+1][j]
                    // memo[j-1] will contain the value for memo[i][j-1]
                    memo[j] = 1 + min(memo[j], memo[j - 1]);

                // Copy the value of memo[i+1][j] to `prev`
                // For the next iteration when j=j+1
                // `prev` will hold the value memo[i+1][j-1];
                prev = temp;
            }
        }

        // Return true if the minimum cost to create a palindrome by only deleting the letters
        // is less than or equal to `k`.
        return memo[s.length() - 1] <= k;
    }
};

*/