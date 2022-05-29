#include <bits/stdc++.h>

using namespace std;

bool possible(int n, int k, vector<int> &blocks, vector<int> &data, int maxVal){
	int b = 0;
	for(int i=0; i<k; i++){
		int contiguousBlocksRequired = data[i];
		int temp = contiguousBlocksRequired;
		bool dataAssigned = false;
		while(b < n){
			if(blocks[b] > maxVal){
				temp = contiguousBlocksRequired;
			} else {
				temp--;
				if(temp==0){
					b++;
					dataAssigned = true;
					break;
				}
			}
			b++;
		}
		if(!dataAssigned)
			return false;
	}
	return true;
}

int solve(int n, int k, vector<int> &blocks, vector<int> &data){
	int low = 0, high = 200000;
	while(low < high){
		int mid = (low + high)/2; //biased towards low
		if(possible(n, k, blocks, data, mid)){
			high = mid;
		} else {
			low = mid+1;
		}
	}
	return low;
}

int main(){
	int test;
	cin >> test;
	for(int t=0; t<test; t++){
		int n, k;
		cin >> n >> k;
		vector<int> blocks;
		int x;
		for(int i=0; i<n; i++){
			cin >> x;
			blocks.push_back(x);
		}
		vector<int> data;
		for(int i=0; i<k; i++){
			cin >> x;
			data.push_back(x);
		}
		cout << solve(n, k, blocks, data);
	}
}