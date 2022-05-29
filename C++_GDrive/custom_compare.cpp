#include <bits/stdc++.h>

using namespace std;


struct Node{
	int data;
	Node(int x): data(x){}
};

bool my_compare(struct Node a, struct Node b){
	if(a.data < b.data) return true;
	else return false;
}

int main(){
	vector<struct Node> arr;
	arr.resize(5, 0);
	arr[0].data=2;
	arr[1].data=3;
	arr[2].data=1;
	arr[3].data=5;
	arr[4].data=4;
	for(int i=0; i<5; i++)
		cout << arr[i].data << " ";
	cout << endl;	
	sort(arr.begin(), arr.end(), my_compare);
	for(int i=0; i<5; i++)
		cout << arr[i].data << " ";
	cout << endl;
	return 0;
}
