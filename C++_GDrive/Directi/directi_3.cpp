/*
Given two strings of brackets, find how many balanced strings you can form, keeping order of individual strings maintained. 
*/

#include <bits/stdc++.h>
using namespace std;

bool check_balances(string a, int ind, int open){
	while(ind < a.length()){
		if(a[ind ]=='(')
			open++;
		else{
			if(open==0)
				return false;
			else
				open--;
		}
		ind++;
	}
	return open==0;
}

int func(vector<vector<int> > &dp, int open, string a, string b, int inda, int indb){
	if(inda==a.length() && indb==b.length()){
		if(open==0)
			return 1;
		else return 0;
	}
	if(inda==a.length()){
		if(check_balances(b, indb, open))
			return 1;
		else return 0;
	}
	if(indb==b.length()){
		if(check_balances(a, inda, open))
			return 1;
		else return 0;
	}
	if(dp[inda][indb]!=-1)
		return dp[inda][indb];
	dp[inda][indb]=0;
	if(a[inda]==')'){
		if(open>0)
			dp[inda][indb] += func(dp, open-1, a, b, inda+1, indb);
	}
	if(b[indb]==')'){
		if(open>0)
			dp[inda][indb] += func(dp, open-1, a, b, inda, indb+1);
	}
	if(a[inda]=='(')
		dp[inda][indb] += func(dp, open+1, a, b, inda+1, indb);
	if(b[indb]=='(')
		dp[inda][indb] += func(dp, open+1, a, b, inda, indb+1);
	return dp[inda][indb];
}

int helper(string a, string b){
	int lena = a.length();
	int lenb = b.length();
	vector<vector<int> > dp (lena, vector<int> (lenb, -1));
	int open = 0;
	return func(dp, open, a, b, 0, 0);
}

int main(){
	cout << helper(")))", "(((");
}