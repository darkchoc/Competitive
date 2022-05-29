#include <bits/stdc++.h>
using namespace std;

int dfs(int currentNode, vector<vector<int> > &adj, vector<int> &count, int parent, int &ansForZero, int distanceFromZero){
    int nodesAtThisSubtree = 0;
    ansForZero += distanceFromZero;
    distanceFromZero++;
    for(int i=0; i<adj[currentNode].size(); i++){
        if(adj[currentNode][i] == parent)
            continue;
        nodesAtThisSubtree += dfs(adj[currentNode][i], adj, count, currentNode, ansForZero, distanceFromZero);
    }
    count[currentNode] = 1 + nodesAtThisSubtree;
    return count[currentNode];
}

void dfs2(int currentNode, int parent, vector<vector<int> > &adj, vector<int> &count, vector<int> &ans, int n){
    ans[currentNode] = ans[parent] - count[currentNode] + n - count[currentNode];
    for(int i=0; i<adj[currentNode].size(); i++){
        if(adj[currentNode][i] == parent)
            continue;
        dfs2(adj[currentNode][i], currentNode, adj, count, ans, n);
    }
}

vector<int> solve(int n, vector<pair<int, int> > edges){
    vector<vector<int> > adj (n);
    for(int i=0; i<edges.size(); i++){
        adj[edges[i].first].push_back(edges[i].second);
        adj[edges[i].second].push_back(edges[i].first);
    }
    vector<int> count(n, 0);
    vector<int> ans(n, 0);
    int ansForZero = 0;
    int distanceFromZero = 0;
    count[0] = dfs(0, adj, count, -1, ansForZero, distanceFromZero);
    ans[0] = ansForZero;
    for(int i=0; i<adj[0].size(); i++){
        dfs2(adj[0][i], 0, adj, count, ans, n);
    }
    return ans;
}

int main(){
    int n = 6;
    vector<pair<int, int> > edges;
    edges.push_back(make_pair(0,1));
    edges.push_back(make_pair(0,2));
    edges.push_back(make_pair(2,3));
    edges.push_back(make_pair(2,4));
    edges.push_back(make_pair(2,5));

    vector<int> ans = solve(n, edges);
    for(int i=0; i<ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
}