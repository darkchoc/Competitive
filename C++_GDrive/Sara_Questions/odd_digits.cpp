/*
Question: Given a sequence of numbers, find the number of sub sequences which satisfy the following:
	The sum of numbers in the sequence should have odd number of odd digits.
	Two sequences are same if their sorted sequences are same.
Basically, sequence means you can skip elements.
Inputs: n <= 60 and each elements will be less than equal to 2000.
Example: 3 3 6 8 6
Here we have
{3} -> 3, 1 odd digit (so odd number of odd digits)
{3,6} -> 9, 1 odd digit
{6,6} -> 12, 1 odd digit
{3,3,6} -> 12, 1 odd digit
{3,6,6} -> 15, 1 odd digit
{3,3,6,6} -> 18, 1 odd digit
{3,3,8} -> 14, 1 odd digit
{3,6,6,8} -> 23, 1 odd digit

So in all there are 8 subsequences.
Example 2: 0 1 0
{1} -> 1
{0,1} -> 1
{0,0,1} -> 1
So in all 3 subsequences
*/

#include <bits/stdc++.h>

using namespace std;

bool OddDigit(int curr_num){
	int odd_digits=0;
	while(curr_num){
		int dig = curr_num%10;
		if(dig%2)
			odd_digits++;
		curr_num /= 10;
	}
	if(odd_digits%2)
		return true;
	else return false;
}

void badrecurse(vector<int> &nums, int n, long long int &ans, int curr_num, int curr_sum){
	if(curr_num==n){
		if(OddDigit(curr_sum))
			ans++;
		return;
	}
	//including curr_num
	badrecurse(nums, n, ans, curr_num+1, curr_sum+nums[curr_num]);
	//not including curr_num
	int i=curr_num;
	while(i<n && nums[curr_num]==nums[i]){
		i++;
	}
	badrecurse(nums, n, ans, i, curr_sum);
	return;
}

long long int badhelper (vector<int> &nums, int n){
	long long int ans = 0;
	badrecurse(nums, n, ans, 0, 0);
	return ans;
}


long long int goodhelper(vector<int> &nums, int n, vector<bool> &odd_sums){
	int sum = 0;
	for(int i=0; i<n; i++)
		sum += nums[i];
	vector<long long int> freq(sum+1, (long long int)0);
	freq[0]=(long long int)1;
	int left=0, right=0;
	while(right<n){
		while(right<n && nums[left]==nums[right])
			right++;

		vector<long long int> curr_freq (sum+1, (long long int)0);
		for(int k=1; k<=right-left; k++){
			int num = nums[left]*k;
			for(int j=sum; j>=num; j--){
				curr_freq[j] += freq[j-num];
			}
		}
		for(int i=0; i<=sum; i++)
			freq[i] += curr_freq[i];
		left = right;
	}
	long long int ans = 0;
	for(int i=0; i<=sum; i++){
		if(odd_sums[i])
			ans += freq[i];
	}
	return ans;
}	

int main(){
	//with given constraints total sum is max 120000
	vector<bool> odd_sums(125001, false);
	for(int i=0; i<=125000; i++)
		odd_sums[i] = OddDigit(i);

	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n;
		cin >> n;
		vector<int> nums(n);
		for(int i=0; i<n; i++){
			cin >> nums[i];
		}
		sort(nums.begin(), nums.end());
		if(n==0)
			cout << 0 << endl;
		else
			cout << goodhelper(nums, n, odd_sums) << endl;// <<  " " << badhelper(nums, n) << endl;
	}
	return 0;
}
