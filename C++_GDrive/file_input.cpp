#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
	string file_path;
	cout << "Enter file path:" << endl;
	cin >> file_path;
	vector <vector <int> > arr;
	int x;
	fstream my_file(file_path);
//	my_file.open(file_path);
	int feature;
	if(my_file.is_open()){
		my_file >> feature;
		while(!my_file.eof()){
			arr.resize(arr.size() + 1);
			for(int j=0; j<5; j++){
				my_file >> x;
				arr[arr.size()-1].push_back(x);
			}
		}
//		for(int i=0; i<3; i++){
//			for(int j=0; j<5; j++){
//				my_file >> x;
//				arr[i].push_back(x);
//			}
//		}	
		my_file.close();
	}
	else
		cout << "No such file";
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << feature << endl;
return 0;
}

