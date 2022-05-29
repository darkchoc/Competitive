#include <bits/stdc++.h>
using namespace std;

void helper(vector<int> &arr, vector<int> &subset, int ind){
	if(ind == arr.size()){
		if(subset.size() >= 3){
			for(int i=0; i<subset.size(); i++)
				cout << subset[i] << " ";
			cout << endl;
		}
		return;
	}
	subset.push_back(arr[ind]);
	helper(arr, subset, ind+1);
	subset.pop_back();
	helper(arr, subset, ind+1);
	return;
}

int main(){
	vector<int> arr = {1,2,3,4,5};
	vector<int> subset; 
	helper(arr, subset, 0);
}
