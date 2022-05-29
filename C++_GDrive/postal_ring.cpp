#include <bits/stdc++.h>

using namespace std;


int djikstra(vector<vector<int> > &graph, int source, int dest){
	vector<int> dist (26,INT_MAX);
	vector<bool> visited (26, false);
	priority_queue <pair<int, int> , vector<pair<int, int> >, greater<pair<int, int> > > pq;
	pq.push(make_pair(0, source));
	dist[source]=0;
	while(!pq.empty()){
		pair<int, int> p = pq.top();
		pq.pop();
		int u = p.second, w = p.first;
		if(visited[u])
			continue;
		if(u==dest)
			return w;
		visited[u]=true;
		for(int i=0; i<26; i++){
			if(graph[u][i]!=-1 && !visited[i] && dist[i]>dist[u]+graph[u][i]){
				dist[i] = dist[u] + graph[u][i];
				pq.push(make_pair(dist[i], i));
			}
		}
	}
	return 0; 
}

int main(){
	vector<int> degree;
	degree.resize(26,0);	
	string word;
	vector<vector<int> > graph;
	graph.resize(26, vector<int> (26, -1));
	int sum_streets=0;
	while(cin >> word){
		if(word=="deadend"){
			//run algo
			vector<int> odd;
			for(int i=0; i<26; i++){
				if(degree[i]%2==1)
					odd.push_back(i);
			}
			if(odd.size()==0)
				cout << sum_streets << endl;
			else
				cout << sum_streets + djikstra(graph, odd[0], odd[1]) << endl;
			//clear variables
			sum_streets=0;
			degree.resize(26,0);
			graph.resize(26, vector<int> (26, -1));
		}
		else{
			//keep taking in the input
			degree[word[0]-'a']++;
			degree[word[word.size()-1]-'a']++;
			graph[word[0]-'a'][word[word.size()-1]-'a']=word.size();
			graph[word[word.size()-1]-'a'][word[0]-'a']=word.size();
			sum_streets += word.size();
		}
	}
	return 0;
}