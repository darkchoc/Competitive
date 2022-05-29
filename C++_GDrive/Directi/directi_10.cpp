/*
String to number:
https://www.geeksforgeeks.org/directi-interview-experience-set-16-pool-campus-for-application-developer/

*/

#include <bits/stdc++.h>
using namespace std;

int dfs(map<char, int> &mappings, map<char, char> &adj, set<char> &visited, char curr){
	visited.insert(curr);
	if(adj.find(curr)==adj.end()){
		mappings[curr]=-1;
	}
	else if('0'<= adj[curr] && adj[curr]<= '9'){
		mappings[curr]=adj[curr]-'0';
	}
	else{
		//mapped to character
		if(visited.find(adj[curr])==visited.end()){
			mappings[curr] = dfs(mappings, adj, visited, adj[curr]);
		}
		else{
			mappings[curr]=0;
		}
	}
	return mappings[curr];
}

int main(){
	int n;
	cin >> n;
	map<char, char> adj;
	char a,b;
	set<char> visited;
	for(int i=0; i<n; i++){
		cin >> a >> b;
		adj[a]=b;
	}
	map<char, int> mappings;
	for(map<char, char>::iterator it=adj.begin(); it!=adj.end(); it++){
		if(visited.find(it->first)==visited.end())
			int x = dfs(mappings, adj, visited, it->first);
	}
	int s;
	cin >> s;
	for(int i=0; i<s; i++){
		string word;
		cin >> word;
		string ans = "";
		int j;
		for(j=0; j<word.length(); j++){
			if(mappings.find(word[j])==mappings.end() || mappings[word[j]]==-1){
				cout << 0 << endl;
				break;
			}
			ans += to_string(mappings[word[j]]);
		}
		if(j==word.length())
			cout << ans << endl;
	}
	return 0;
}