// https://www.geeksforgeeks.org/maximise-size-consecutive-element-subsets-array/

#include <bits/stdc++.h>

using namespace std;

//1 5 11 20 30

int solve(vector<int> &arr, int n, int k){
	int l=0, r=0;
	int remaining=k;
	int ans=1;
	while(r<n){
		if(r==n-1){
			ans = max(ans, arr[r]-arr[l]+1+remaining);
			break;
		} else {
			if(arr[r+1] - arr[r] == 1){
				r++;
				ans = max(ans, arr[r]-arr[l]+1+remaining);
			} else if(arr[r+1] - arr[r] - 1 <= remaining){
				remaining -= arr[r+1] - arr[r] - 1;
				r++;
				ans = max(ans, arr[r]-arr[l]+1+remaining);
			} else if (arr[r+1] - arr[r] - 1 > remaining) {
				ans = max(ans, arr[r]-arr[l]+1+remaining);
				if(arr[r+1] - arr[r] -1 > k ){
					remaining = k;
					r++;
					l = r;
				} else {
					remaining += arr[l+1] - arr[l] - 1;
					l++;
				}
			}
		}
	}
	return ans;
}

int solve2(vector<int> &arr, int n, int k){
	int l=0, r=0, ans=1;
	while(r<n){
		while((arr[r]-arr[l]+1)-(r-l+1) > k)
			l++;
		ans = max(ans, (arr[r]-arr[l]+1) + k - (arr[r] - arr[l] + 1 - (r - l + 1))); //total - remaining spare points = total - (total spare points - used spare points)
		r++;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	vector<int> arr;
	int x, y;
	for(int i=0; i<n; i++){
		cin >> x;
		if(i==0){
			arr.push_back(x);
			y = x;
		} else {
			if(y==x)
				continue;
			else{
				arr.push_back(x);
				y = x;
			}
		}
	}
	cout << solve(arr, (int)arr.size(), k) << endl;
	cout << solve2(arr, (int)arr.size(), k) << endl;
	return 0;
}