#include <bits/stdc++.h>

using namespace std;

int helper(vector<int> &a, vector<int> &b, vector<int> &c, int k, vector<vector<vector<int> > > &dp, 
	       int floor, int jumps, int building, int current){
	int n = a.size();
	if(floor==n){
		return current;
	}
	if(dp[building][floor][jumps]!=-1)
		return dp[building][floor][jumps];
	if(jumps==k){
		int ret = 0;
		for(int i=floor; i<n; i++){
			if(building==0)
				ret+=a[i];
			else if(building==1)
				ret+=b[i];
			else
				ret+=c[i];
		}
		dp[building][floor][jumps] = ret;
		return ret;
	}
	if(building==0){
		current += a[floor];
		dp[building][floor][jumps] = max(helper(a,b,c,k,dp, floor+1, jumps, building, current), 
			       						helper(a,b,c,k,dp, floor+1, jumps+1, building+1, current));
	}
	else if(building==1){
		current += b[floor];
		dp[building][floor][jumps] = max(helper(a,b,c,k,dp, floor+1, jumps, building, current),
			                         max(helper(a,b,c,k,dp, floor+1, jumps+1, building-1, current),
			                         	 helper(a,b,c,k,dp, floor+1, jumps+1, building+1, current)));
	}
	else{
		current += c[floor];
		dp[building][floor][jumps] = max(helper(a,b,c,k,dp, floor+1, jumps, building, current),
										helper(a,b,c,k,dp, floor+1, jumps+1, building-1, current));
	}
	return dp[building][floor][jumps];
}

int func(vector<int> &a, vector<int> &b, vector<int> &c, int k){
	int n = a.size();
	if(n==0)
		return 0;
	if(k==0 || n==1){
		int a_=0, b_=0, c_=0;
		for(int i=0; i<n; i++){
			a_ += a[i];
			b_ += b[i];
			c_ += c[i];
		}
		a_ = max(a_, b_);
		a_ = max(a_, c_);
		return a_;
	}
	vector<vector<vector<int> > > dp(3, vector<vector<int> > (n+1, vector<int> (k+1, -1)));
	int ans = max(helper(a,b,c,k,dp, 0, 0, 0, 0), helper(a,b,c,k,dp, 0, 0, 1, 0));
	ans = max(ans, helper(a,b,c,k,dp, 0, 0, 2, 0));
	return ans;
}

int main(){
	int a_arr[] = {3,1};
	vector<int> a (a_arr, a_arr + sizeof(a_arr)/sizeof(a_arr[0]));
	int b_arr[] = {3,3};
	vector<int> b (b_arr, b_arr + sizeof(b_arr)/sizeof(b_arr[0]));
	int c_arr[] = {3,5};
	vector<int> c (c_arr, c_arr + sizeof(c_arr)/sizeof(c_arr[0]));
	int k = 1;
	cout << func(a, b, c, k);
	return 0;
}