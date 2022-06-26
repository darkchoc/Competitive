//code for max heap
#include <bits/stdc++.h>
using namespace std;

void heapify(vector<int> &A, int root, int size){
	//swap and trickle down to from where you swaped
	int left = 2*root+1;
	int right = 2*root+2;
	int largest = root;
	if (left < size)
		largest = (A[root]>A[left])?root:left;
	if (right < size)
		largest = (A[largest]>A[right])?largest:right;
	if (largest!=root){
		swap(A[largest], A[root]);
		heapify(A, largest, size);
	}
	return;
}

void insert(vector<int> &A, int num){
	int n = A.size();
	A.push_back(num);
	int current = n;
	while(current!=0 && A[(current-1)/2]<A[current]){
		swap(A[current], A[(current-1)/2]);
		current = (current-1)/2;
	}
	return;
}

void print(vector<int> &A){
	for(int i=0; i<A.size(); i++)
		cout << A[i] << " ";
	cout << endl;
}

int main(){
	int n, x;
	cin >> n;
	vector<int> A;
	for(int i=0; i<n; i++){
		cin >> x;
		A.push_back(x);
	}
	//if i is parent -> 2*i + 1 = left
	// 				 -> 2*i + 2 = right
	//if i is left -> (i-1)/2 = parent
	//if i is right -> (i-1)/2 = parent
	//if total n nodes, leaf node = ((n-1)-1)/2 -> basically start heapifying from parent of last node
	for(int i=((n-1)-1)/2; i>=0; i--){
		heapify(A, i, n);
	}
	print(A);
	cout << endl;

	insert(A, 35);
	insert(A, -5);
	print(A);
	cout << endl;

	for(int currentSize=A.size(); currentSize>=2; currentSize--){
		swap(A[0], A[currentSize-1]);
		heapify(A, 0, currentSize-1);
	}
	print(A);
}
