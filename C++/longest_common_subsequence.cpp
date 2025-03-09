/*
Find and print the longest common subsequence between two strings
*/

#include <iostream>
using namespace std;

string lcs(string a, string b){
    int n = a.length();
    int m = b.length();
    vector<vector<int> > dp (n+1, vector<int> (m+1, 0)); // dp[i][j] = max lcs between a[0...i-1] and b[0...j-1]
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(a[i-1]==b[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else 
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    int i = n, j = m;
    string ans = "";
    while(i > 0 && j > 0){
        if(a[i-1]==b[j-1]){
            ans.push_back(a[i-1]);
            i--;
            j--; // basically moving to dp[i-1][j-1]
        } else {
            // move to [i-1][j] or [i][j-1] depending on which is longer
            if(dp[i-1][j] > dp[i][j-1])
                i--;
            else   
                j--;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    cout << lcs("axbgcfdsegf", "ratbacvdvewfl") << endl; // abcdef
    cout << lcs("accdejcca", "accadej") << endl; // accdej
}