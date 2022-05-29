#include <bits/stdc++.h>

using namespace std;

int boardSize = 8;

bool valid(vector<int> &combo, int tillCol){
	for(int i=0; i<tillCol; i++){
		if(combo[i]==combo[tillCol])
			return false;
		if((double)(i-tillCol)/(combo[i]-combo[tillCol])==1.0 || (double)(i-tillCol)/(combo[i]-combo[tillCol])==-1.0) //basically if slope is 1 or -1, means same diagonal.
			return false;
	}
	return true;
}

void recurse(vector<int> &combo, int col, vector<vector<int> > &validCombos){
	if(col==boardSize){
		validCombos.push_back(combo);
		return;
	}
	for(int i=0; i<boardSize; i++){
		combo[col]=i;
		if(valid(combo, col))
			recurse(combo, col+1, validCombos);
		combo[col]=-1;
	}
}

int checkDiff(vector<int> &validCombo, vector<int> &order){
	int ans = 0;
	for(int i=0; i<boardSize; i++){
		ans += (validCombo[i] != order[i]);
 	}
	return ans;
}

int main(){
	vector<vector<int> > validCombos;
	vector<int> combo (boardSize, -1);
	recurse(combo, 0, validCombos);
	cout << "Valid combinations are: " << validCombos.size() << endl;
	int test;
	cin >> test;
	for(int t=0; t<test; t++){
		vector<int> order;
		int x;
		for(int i=0; i<boardSize; i++){
			cin >> x;
			order.push_back(x);
		}
		int ans = INT_MAX;
		for(int i=0; i<validCombos.size(); i++){
			ans = min(ans, checkDiff(validCombos[i], order));
		}
		cout << ans << endl;
	}
}