#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
using namespace std;

int main(){
	string file;
	cin >> file;
	//file is
	/*
	3
	1 2 3
	4 5 6
	7 8 9
	*/
	ifstream myfile(file);
	int n;
	myfile >> n;
	cout << n << endl; 
	cout << "lol\n";
	vector<vector<int> > arr(n, vector<int> (n));
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			myfile >> arr[i][j];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
	return 0;
}