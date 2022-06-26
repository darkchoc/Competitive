/*

You are given a set of words (w1,w2,....,wk) which occur in a certain document D and for each word an associated position list which is an sorted integer array of positions at which that word occurs in D, you need to find smallest range in the document which contains all the words at least once.
N is the count of words in document D K is the count of unique words in document D
[
	[1, 4, 8, 9]
	[2, 3, 6]
	[5, 7]
	[10]
]
->. 6,10

*/


#include <bits/stdc++.h>
using namespace std;

vector<int> func(vector<vector<int> > &words){
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > minHeap;
	int currMax=-1, start=-1, end=-1;
	for(int i=0; i<words.size(); i++){
		minHeap.push(make_pair(words[i][0], make_pair(0, i)));  //position in doc, position in word's own sorted list, #word
		currMax = max(currMax, words[i][0]);
	}
	start = minHeap.top().first; 
	end = currMax;
	while(minHeap.top().second.first < words[minHeap.top().second.second].size()){
		pair<int, pair<int, int> > p = minHeap.top();
		minHeap.pop();
		minHeap.push(make_pair(words[p.second.second][p.second.first+1], make_pair(p.second.first+1, p.second.second)));
		currMax = max(currMax, words[p.second.second][p.second.first+1]);
		if(currMax - minHeap.top().first < end - start){
			start = minHeap.top().first;
			end = currMax;
		}
	}
	vector<int> res;
	res.push_back(start);
	res.push_back(end);
	return res;
}

int main(){
	int w, x, y;
	cin >> w;
	vector<vector<int> > words(w);
	for(int i=0; i<w; i++){
		cin >> x;
		for(int j=0; j<x; j++){
			cin >> y;
			words[i].push_back(y);
		}
	}
	vector<int> minRange = func(words);
	cout << minRange[0] << " " << minRange[1] << endl;
	return 0;
}