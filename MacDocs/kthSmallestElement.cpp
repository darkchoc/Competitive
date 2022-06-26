#include <bits/stdc++.h>
using namespace std;

int random(int l, int r){
	//random number between l and r inclusive
	//for now, returning mean.
	return (l+r)/2;
}

int partition(vector<int> &A, int l, int r){
	int p = random(l, r);
	swap(A[p], A[r]);
	int smaller=l;
	for(int i=l; i<r; i++){
		if(A[i]<=A[r]){
			swap(A[smaller], A[i]);
			smaller++;
		}
	}
	swap(A[smaller], A[r]);
	return smaller;
}

int quickSort(vector<int> &A, int l, int r, int k){
	int partitionIndex = partition(A, l, r);
	if(k==partitionIndex)
		return A[partitionIndex];
	if(k<partitionIndex)
		return quickSort(A, l, partitionIndex-1, k);
	else
		return quickSort(A, partitionIndex+1, r, k);
}



int main(){
	int n, k;
	cin >> n >> k;
	int x;
	vector<int> A;
	for(int i=0; i<n; i++){
		cin >> x;
		A.push_back(x);
	}
	cout << quickSort(A, 0, n-1, k-1) << endl;
	return 0;
}