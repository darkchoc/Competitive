/*

Given an array of Length N. You have to select two non overlapping K length subarrays from the given array such that the sum of elements of selected subarrays is maximum.
Eg: 6 2
       1 4 3 2 5 3
       Ans - 15
	1. Create array B having sum of k elements starting from current index.
	2. Create another array giving max value between B[i] to last in the above array
	3. Run another loop and store max(ans, B[i] + B[i+k])

*/

#include <bits/stdc++.h>

using namespace std;

int func (vector<int> &arr, int k){
	int n = arr.size();
	vector<int> kSum;
	int sum = 0;
	for(int i=0; i<n; i++){
		sum += arr[i];
		sum -= (i>=k)?arr[i-k]:0;
		kSum.push_back((i>=k-1)?sum:INT_MIN);
	}
	vector<int> maxOnLeft;
	int max_ = INT_MIN;
	for(int i=0; i<n; i++){
		max_ = max(max_, kSum[i]);
		maxOnLeft.push_back(max_);
	}
	int ans = INT_MIN;
	for(int i=n-1; i>=0; i--)
		ans = max(ans, kSum[i] + maxOnLeft[i-k]);
	return ans;
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<int> arr;
	int x;
	for(int i=0; i<n; i++){
		cin >> x;
		arr.push_back(x);
	}
	if(n<2*k)
		cout << "Not possible" << endl;
	else
		cout << func(arr, k) << endl;
	return 0;
}