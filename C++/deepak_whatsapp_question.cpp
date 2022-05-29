#include <bits/stdc++.h>

using namespace std;

void merge(vector<pair<int, int> > &rails, int start, int mid, int end){
	int left = start, right = mid+1;
	vector<pair<int, int> > temp;
	while(left <= mid && right <= end){
		if(rails[left].first * rails[right].second + rails[left].second > rails[right].first * rails[left].second + rails[right].second){
			temp.push_back(rails[left]);
			left++;
		}
		else{
			temp.push_back(rails[right]);
			right++;
		}
	}
	while(left <= mid)
		temp.push_back(rails[left++]);
	while(right <= end)
		temp.push_back(rails[right++]);
	for(int i=start; i<=end; i++)
		rails[i] = temp[i-start];
	return;
}

void merge_sort(vector<pair<int, int> > &rails, int start, int end){
	if(start < end){
		int mid = (start + end)/2;
		merge_sort(rails, start, mid);
		merge_sort(rails, mid+1, end);
		merge(rails, start, mid, end);
	}
	return;
}


int main(){
	vector<pair<int, int> > rails;
	rails.push_back(make_pair(2,6));
	rails.push_back(make_pair(1,6));
	rails.push_back(make_pair(6,3));
	rails.push_back(make_pair(10,4));
	rails.push_back(make_pair(7,6));

	merge_sort(rails, 0, rails.size()-1);
	cout << "Best order:\n";
	for(int i=0; i<rails.size(); i++){
		cout << rails[i].first << " " << rails[i].second << endl;
	}
	cout << endl;
	
}