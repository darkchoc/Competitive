#include <bits/stdc++.h>

using namespace std;

int lengthOfLIS(vector<int> &arr){
	vector<int> lastElementArray(arr.size(), 0);
	int lastInd = 0;
	lastElementArray[0] = arr[0];
	for(int i=1; i<arr.size(); i++){
		int current = arr[i];
		int left = 0, right = lastInd;
		while(left < right){
			int mid = left + (right - left)/2; //biased towards left
			if(lastElementArray[mid] < current){
				left = mid + 1;
			} else {
				right = mid;
			}
		}
		cout << "current = " << current << " left= " << left << " lastInd = " << lastInd << endl;
		if(left == lastInd){
			if(lastElementArray[lastInd] < current){
				left++;
				lastInd++;
			}
		}
		lastElementArray[left] = current;
		cout << "Current array: ";
		for(int i=0; i<=lastInd; i++){
			cout << lastElementArray[i] << " ";
		}
		cout << endl;
	}
	return lastInd;
}

int main(){
	int n;
	cin >> n;
	vector<int> arr (n);
	for(int i=0; i<n; i++){
		cin >> arr[i];
	}
	int ans = lengthOfLIS(arr);
	ans += 1;
	cout << ans << endl;
	return 0;
}