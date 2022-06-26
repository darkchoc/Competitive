#include <bits/stdc++.h>
using namespace std;

string lcs(string s1, string s2) {
	int n = s1.length();
	int m = s2.length();
	string ans = "";
	vector<vector<int> > dp (n, vector<int> (m, -1));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(dp[i][j]==-1){
				if(s1[i]!=s2[j]){
					dp[i][j]=0;
				}
				else{
					dp[i][j] = 1 + ((i>0&&j>0)?dp[i-1][j-1]:0);
				}
			}
			if(ans.length() < dp[i][j]){
				ans = s1.substr(i-dp[i][j]+1, dp[i][j]);
			}
		}
	}
	return ans;
}

int main(){
	string s1, s2;
	cin >> s1;
	cin >> s2;
	cout << lcs(s1, s2) << endl;
}