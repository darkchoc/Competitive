/*
Given arr, and P array. After one round, arr[i] will go to P[i] position. After how many swaps will the array be same?
The current code will work only for distinct elements. Not for repeated elements.
For it to work on repeated elements, the graph should be formed between array elements itself. 
*/
#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
    if(a<b){
        int temp = a;
        a = b;
        b = temp;
    }
    if(a%b==0)
        return b;
    else return gcd(b, a%b);
}

int lcm(int a, int b){
    return (a*b)/(gcd(a,b));
}

void cycle(vector<vector<int> > &adj, vector<bool> &visited, 
           int curr, int &cnt){
    visited[curr-1]=true;
    cnt++;
    if(visited[adj[curr][0]-1]==true)
        return;
    else
        cycle(adj, visited, adj[curr][0], cnt);
    return;
}

int helper(vector<int> &arr, vector<int> &P){
    int ans = 1;
    vector<bool> visited (arr.size(), false);
    vector<vector<int> > adj (arr.size()+1); //graph, consider all indices as nodes.
    for(int i=0; i<arr.size(); i++){
        adj[P[i]].push_back(P[P[i]-1]);
    }
    for(int i=0; i<arr.size(); i++){
        if(visited[i]==false){
            int cnt = 0;
            cycle(adj, visited, i+1, cnt);
            ans = lcm(ans, cnt);
        }
    }
    return ans;
}

int main() {
	vector<int> arr = {1,2,3,4,5,6,7};
	vector<int> P = {2,1,7,3,4,5,6};
	cout << helper(arr, P) << endl;

    vector<int> arr1 = {1,2,3}; 
    vector<int> P1 ={3,2,1};
    cout << helper(arr1, P1) << endl;

    vector<int> arr2 = {4,5,1,2,3};
    vector<int> P2 = {1,4,2,5,3};
    cout << helper(arr2, P2) << endl;
	return 0;
}