/*
Blue Berry Cheesecake
School with n classes. There are B blue berry cheesecakes. Given students in each of the n classes, what is the minimum
of the maximum students per cake, given each class receives at least 1 cake.

https://discuss.codechef.com/t/directi-recruitment-test-question-blueberry-cheese-cake/17641
*/

#include <bits/stdc++.h>
using namespace std;

bool possible(int st_per_cake, vector<int> &classes, int b, int n){
	int i;
	for(i=0; i<n && b>0; i++){
		int cakes_required = ceil((double)classes[i]/(double)st_per_cake);
		b -= cakes_required;
	}
	if(i==n && b>=0)
		return true;
	else
		return false;
}

int helper(vector<int> &classes, int b, int n){
	int lower = 1;
	int upper=0;
	for(int i=0; i<n; i++)
		upper = max(upper, classes[i]);
	while(lower<upper){
		int mid = (lower+upper)/2;
		if(possible(mid, classes, b, n)){
			upper=mid;
		}
		else
			lower=mid+1;
	}
	return lower;
}	

int main() {
	int n, b; 
	cin >> n >> b;
	vector<int> classes(n);
	for(int i=0; i<n; i++)
		cin >> classes[i];
	cout << helper(classes, b, n);
	return 0;
}