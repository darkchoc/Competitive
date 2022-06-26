/*

 You have to load some boxes in a train. There are machines which have  maximum capacity. Machines work simultaneously and can load 1 box in 1 minute. Given array of box weights and max cap of each machine, find minimum time to load boxes in train.
Ex:
Boxes = {2 5 2 4 7}
M ={6,8,9}
Return 2

Boxes = {14,12,16,19,16,1,5}
Machine = {19,20}
Return 4

*/


#include <bits/stdc++.h>
using namespace std;

bool possible(int time, vector<int> &boxes, vector<int> &machines){
	int bs = boxes.size(), ms = machines.size();
	int b = 0, m = 0, curr_boxes;
	while(b<bs && m<ms){
		//m is current machine
		//start picking from box b
		curr_boxes = 0;
		while(b<bs && boxes[b]<=machines[m] && curr_boxes<time){
			b++;
			curr_boxes++;
		}
		m++;
	}
	return (b==bs && m<=ms);
}


int func(vector<int> &boxes, vector<int> &machines){
	int b = boxes.size(), m = machines.size();
	sort(boxes.begin(), boxes.end());
	sort(machines.begin(), machines.end());
	if(boxes[b-1] > machines[m-1])
		return -1;
	int high = b, low = b/m;
	while(low<high){
		int mid = (low+high)/2;
		if(possible(mid, boxes, machines))
			high = mid;
		else 
			low = mid+1;
	}
	return low;
}

int main(){
	int b, m, x;
	cin >> b >> m;
	vector<int> boxes;
	for(int i=0; i<b; i++){
		cin >> x;
		boxes.push_back(x);
	}
	vector<int> machines;
	for(int i=0; i<m; i++){
		cin >> x;
		machines.push_back(x);
	}
	cout << func(boxes, machines) << endl;
}