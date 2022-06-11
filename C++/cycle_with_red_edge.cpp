/*
I made this question myself while trying to solve google_point_directions_valid.cpp.

A directed graph has red and blue edges. There can be more than 2 edges between two vertices, but not self-loops. Find out if there is a directed cycle, containing at least one red edge.

Input:
A vector of pair specifying all the blue edges.
A vector of pair specifying all the red edges.

Examples:
Input1:
Blue:[(0,1),(1,0),(1,2),(2,1),(1,3),(3,1)]
Red:[]
Output: False

Input2:
Blue:[]
Red:[(0,1),(1,2),(0,2)]
Output: False

Input3:
Blue:[(0,1),(1,0),(2,1),(1,2)]
Red:[(0,2)]
Output: True

Input4:
Blue:[]
Red:[(0,1),(1,2),(2,0)]
Output: True

Input5:
Blue:[(0,1),(1,0),(1,2),(2,1),(4,5),(5,4)]
Red:[(3,4)]
Output: False

Input6:
Blue:[(1,2),(2,3),(2,4),(4,2)]
Red:[(3,4)]
Output: True

Inpu7:
Blue:[(1,2),(2,1),(2,3)]
Red:[(3,2)]
Output: True

Input8:
Blue:[]
Red:[(0,1),(1,2),(0,3),(3,4),(4,2)]
Output: False

Input9:
Blue:[(0,3),(3,0)]
Red:[(0,1),(1,2),(3,4),(4,2)]
Output: False

Input10:
Blue:[]
Red:[(0,1),(1,2),(4,2),(3,4),(3,0)]
Output: False

Input11:
Blue:[(1,2),(2,1),(2,3)]
Red: [(3,2)]
Output: True

Approach: While doing dfs, keep track of number of red edges encountered till now. Now when you're doing dfs from a vertex, if you encounter another already visited vertice, with less number of red edges encountered than current count, we have a cycle containing red edge.
*/

#include <bits/stdc++.h>
using namespace std;

bool dfs(unordered_map<int, vector<pair<int, int> > > &graph, set<int> &visited, unordered_map<int, int> &redCount, int current){
    visited.insert(current);
    for(int i=0; i<graph[current].size(); i++){
        pair<int, int> neighbour = graph[current][i];
        int v = neighbour.second;
        int type = neighbour.first;
        if(visited.find(v)==visited.end()){
            redCount[v] = redCount[current] + type;
            if(dfs(graph, visited, redCount, v))
                return true;
            redCount.erase(v);
        } else if(redCount.find(v) == redCount.end()){
            //case when we visited v before, but that path ended and now we are visiting it again from some other path.
            //In this case, we can simply continue as we are reaching a vertex whose subtree is already visited.
            continue;
        } else {
            if(redCount[v] < redCount[current] + type){ //+type to accomodate edge connecting current to v.
                return true; //cycle found with red edge
            } else {
                //redCount[v] == redCount[current]
                //blue cycle
                continue;
            }
        }
    }
    return false;
}


bool redEdgedCyclePresent(vector<vector<int> > blue, vector<vector<int> > red){
    unordered_map<int, vector<pair<int, int> > > graph;
    for(int i=0; i<red.size(); i++)
        graph[red[i][0]].push_back(make_pair(1, red[i][1]));
    for(int i=0; i<blue.size(); i++)
        graph[blue[i][0]].push_back(make_pair(0, blue[i][1]));
    unordered_map<int, int> redCount; //this will be used only to keep track of those vertices which are currently in path (gray vertices, if we draw analogy to coloring in dfs).
    set<int> visited; //this will keep track of all visited vertices
    for(auto it = graph.begin(); it!=graph.end(); it++){
        if(visited.find(it->first)==visited.end()){
            redCount[it->first]=0;
            if(dfs(graph, visited, redCount, it->first))
                return true;
            redCount.erase(it->first);
        }
    }
    return false;
}

bool bellmanFord(unordered_map<int, vector<int> > &graph, vector<vector<int> > &red, vector<vector<int> > &blue, set<int> &visited, int source){
    visited.insert(source);
    unordered_map<int, int> dist;
    dist[source]=0;
    int n = graph.size();
    for(int i=0; i<n-1; i++){
        //longest path can have n-1 length. So run loop n-1 times
        for(int j=0; j<red.size(); j++){
            int u = red[j][0], v = red[j][1], w = -1;
            if(dist.find(u)!=dist.end()){
                if(dist.find(v)==dist.end() || dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                }
                visited.insert(v);
            }
        }
        for(int j=0; j<blue.size(); j++){
            int u = blue[j][0], v = blue[j][1], w = 0;
            if(dist.find(u)!=dist.end()){
                if(dist.find(v)==dist.end() || dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                }
                visited.insert(v);
            }
        }
    }
    //now check if any vertice is still having relaxation -> means negative cycle
    for(int i=0; i<red.size(); i++){
        int u = red[i][0], v = red[i][1], w = -1;
        if(dist.find(u)!=dist.end()){
            if(dist[v] > dist[u] + w)
                return true;
        }
    }
    for(int i=0; i<blue.size(); i++){
        int u = blue[i][0], v = blue[i][1], w = 0;
        if(dist.find(u)!=dist.end())
            if(dist[v] > dist[u] + w)
                return true;
    }
    return false;
}

bool redEdgedCycleBellmanFord(vector<vector<int> > blue, vector<vector<int> > red){
    //Second approach, the one I used in google_point_directions_valid.cpp
    //Apply bellman ford on each connected component. If there n total vertices, the worst case complexity would be n^2, as we'll apply bellman ford (o(n)) to all components (n, in worst case). Trying to optimize by keeping size of component might become tough as we have a directed graph and not undirected. 

    //Consider red edges as negative edges.
    unordered_map<int, vector<int> > graph;
    for(int i=0; i<red.size(); i++)
        graph[red[i][0]].push_back(red[i][1]);
    for(int i=0; i<blue.size(); i++)
        graph[blue[i][0]].push_back(blue[i][1]);
    set<int> visited;
    for(auto it = graph.begin(); it!=graph.end(); it++){
        if(visited.find(it->first)==visited.end()){
            if(bellmanFord(graph, red, blue, visited, it->first))
                return true;
        }
    }
    return false;
}

int main(){
    cout << redEdgedCyclePresent({{0,1},{1,0},{1,2},{2,1},{1,3},{3,1}}, {}) << " " << redEdgedCycleBellmanFord({{0,1},{1,0},{1,2},{2,1},{1,3},{3,1}}, {}) << endl; //0
    cout << redEdgedCyclePresent({}, {{0,1},{1,2},{0,2}}) << " " << redEdgedCycleBellmanFord({}, {{0,1},{1,2},{0,2}}) << endl; //0
    cout << redEdgedCyclePresent({{0,1},{1,0},{2,1},{1,2}}, {{0,2}}) << " " << redEdgedCycleBellmanFord({{0,1},{1,0},{2,1},{1,2}}, {{0,2}}) << endl; //1
    cout << redEdgedCyclePresent({}, {{0,1},{1,2},{2,0}}) << " " << redEdgedCycleBellmanFord({}, {{0,1},{1,2},{2,0}}) << endl; //1
    cout << redEdgedCyclePresent({{0,1},{1,0},{1,2},{2,1},{4,5},{5,4}}, {{3,4}}) << " " << redEdgedCycleBellmanFord({{0,1},{1,0},{1,2},{2,1},{4,5},{5,4}}, {{3,4}}) << endl; //0
    cout << redEdgedCyclePresent({{1,2},{2,3},{2,4},{4,2}}, {{3,4}}) << " " << redEdgedCycleBellmanFord({{1,2},{2,3},{2,4},{4,2}}, {{3,4}}) << endl; //1
    cout << redEdgedCyclePresent({{1,2},{2,1},{2,3}}, {{3,2}}) << " " << redEdgedCycleBellmanFord({{1,2},{2,1},{2,3}}, {{3,2}}) << endl; //1
    cout << redEdgedCyclePresent({}, {{0,1},{1,2},{0,3},{3,4},{4,2}}) << " " << redEdgedCycleBellmanFord({}, {{0,1},{1,2},{0,3},{3,4},{4,2}}) << endl; //0
    cout << redEdgedCyclePresent({{0,3},{3,0}}, {{0,1},{1,2},{3,4},{4,2}}) << " " << redEdgedCycleBellmanFord({{0,3},{3,0}}, {{0,1},{1,2},{3,4},{4,2}}) << endl; //0
    cout << redEdgedCyclePresent({}, {{0,1},{1,2},{4,2},{3,4},{3,0}}) << " " << redEdgedCycleBellmanFord({}, {{0,1},{1,2},{4,2},{3,4},{3,0}}) << endl; //0
    cout << redEdgedCyclePresent({{1,2},{2,1},{2,3}}, {{3,2}}) << " " << redEdgedCycleBellmanFord({{1,2},{2,1},{2,3}}, {{3,2}}) << endl; //1
    return 0;
}
