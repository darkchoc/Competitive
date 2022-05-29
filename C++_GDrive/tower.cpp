#include <bits/stdc++.h>

using namespace std;


vector<int> helper(vector<int> &arr, int range){
	int n = arr.size();
	if(n==0){
		vector<int> ans;
		return ans;
	}
	int i=0;
	vector<int> ans;
	while(i<n){
		int j=i;
		while(j<n && arr[j]-arr[i]<=range)
			j++;
		j--;
		int k = j;
		ans.push_back(arr[k]);
		while(j<n && arr[j]-arr[k]<=range)
			j++;
		i=j;
	}
	return ans;
}


int main(){
	cout << "Enter range" << endl;
	int range;
	cin >> range;
	cout << "How many locations: " << endl;
	int n;
	cin >> n;
	vector<int> arr (n);
	cout << "Enter locations: " << endl;
	for(int i=0; i<n; i++)
		cin >> arr[i];
	cout << "minimum towers: ";
	vector<int> ans = helper(arr, range);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
	return 0;
}