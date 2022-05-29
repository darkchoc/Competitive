#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007

int main(){
	int test;
	test=1;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n, K, P;
		cin >> n >> K >> P;
		vector<int> nums (n);
		int x;
		for(int i=0; i<n; i++){
			cin >> x;
			nums[i] = x;
		}
		sort(nums.begin(), nums.end());
		vector<vector<long long int> > dp(2, vector<long long int> (n, 0));
		for(int i=0; i<n; i++)
			dp[0][i] = 1;
		int current = 0;
		for(int k=2; k<=K; k++){
			current = !current;
			for(int i=0; i<n; i++)
				dp[current][i]=0;
			int left = 0, right = 0;
			long long int sum = 0;
			while(right<n){
				if(nums[right]-nums[left] <= P){
					sum = (sum+dp[!current][right])%mod;
					right++;
				}
				else{
					sum = (sum - dp[!current][left])%mod;
					dp[current][left]=sum;
					left++;
				}
			}
			while(left<n){
				sum = (sum - dp[!current][left])%mod;
				dp[current][left]=sum;
				left++;
			}
			for(int i=0; i<n; i++)
				cout << dp[current][i] << " ";
			cout << endl;
		}
		long long int ans = 0;
		for(int i=0; i<n; i++)
			ans = (ans + dp[current][i])%mod;
		cout << ans << endl;
	}
	return 0;
}