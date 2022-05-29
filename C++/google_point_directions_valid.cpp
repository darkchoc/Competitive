/*
https://leetcode.com/discuss/interview-question/1616210/google-india-new-grad-onsite-verify-the-rules
You are given various statements regarding some points and the direction between them. Check if all the statements are correct or not.

For example:

P1 is in North of P2
P2 is in North of P3
P3 is in North of P1

Output: False (since P3 will be in South of P1)

Directions can be N,S,W,E,NW,NE,SW, etc.
The interviewer gave the hint to use graph.
*/

#include <bits/stdc++.h>
using namespace std;

typedef struct Edge{
    string from;
    string to;
    int weight;
    Edge(string f, string t, int w): from(f), to(t), weight(w){};
} Edge;

bool bellmanFord(vector<Edge> &edges, set<string> &vertices){
    map<string, int> dist;
    int n = vertices.size();
    dist[(*vertices.begin())] = 0;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<edges.size(); j++){
            string u = edges[j].from;
            string v = edges[j].to;
            int w = edges[j].weight;
            if(dist.find(u)!=dist.end()){
                if(dist.find(v)==dist.end())
                    dist[v] = dist[u] + w;
                else if(dist[v] > dist[u] + w)
                    dist[v] = dist[u] + w;
            }
        }
    }
    //if any vertice gets relaxed now, means negative cycle 
    for(int i=0; i<edges.size(); i++){
        string u = edges[i].from;
        string v = edges[i].to;
        int w = edges[i].weight;
        if(dist[v] > dist[u] + w)
           return true; 
    }
    return false;
}

bool isValid(vector<vector<string> > &input){
    vector<Edge> yplane;
    vector<Edge> xplane;
    set<string> vertices;
    for(int i=0; i<input.size(); i++){
        string p1 = input[i][0];
        string p2 = input[i][2];
        vertices.insert(p1);
        vertices.insert(p2);
        string dir = input[i][1];
        if(dir=="N"||dir=="NE"||dir=="NW"){
            //p1 is north[east/west] of p2
            yplane.push_back(Edge(p2, p1, -1)); //-1 means inequality edge, 0 means equality edge. Edge from p2 to p1
        }
        if(dir=="S"||dir=="SE"||dir=="SW"){
            //p1 is south[east/west] of p2
            yplane.push_back(Edge(p1, p2, -1));
        }
        if(dir=="N"||dir=="S"){
            xplane.push_back(Edge(p1, p2, 0));
            xplane.push_back(Edge(p2, p1, 0));
        }
        if(dir=="E"||dir=="NE"||dir=="SE"){
            //p1 is east[north/south] of p2
            xplane.push_back(Edge(p2, p1, -1)); //edge from p2 to p1
        }
        if(dir=="W"||dir=="NW"||dir=="SW"){
            //p1 is west[north/south] of p2
            xplane.push_back(Edge(p1, p2, -1)); //edge from p1 to p2
        }
        if(dir=="W"||dir=="E"){
            yplane.push_back(Edge(p1, p2, 0));
            yplane.push_back(Edge(p2, p1, 0));
        }
    }

    //Now we have a graph in yplane and xplane. Two points will have 0 edge in between them if their coordinates are equal (x or y). Otherwise a -1 weight edge to represent inequality. In yplane, we only have edges going to north, and in xplane, we have edges going to east.


    //Now check if there is any cycle that has -1 weight edge. This boils down to finding whether their is a negative weight cycle in the graph. We can do it using Bellman Ford.
    bool negativeCycleFound = bellmanFord(yplane, vertices);
    if(negativeCycleFound)
        return false;
    return !bellmanFord(xplane, vertices);
}

int main(){
    vector<vector<string> > input = {{"P2", "N", "P1"},{"P3", "N", "P2"},{"P3", "N", "P1"}};
    cout << isValid(input) << endl; //1
    input = {{"P2", "N", "P1"},{"P3", "N", "P2"},{"P3", "NE", "P1"}};
    cout << isValid(input) << endl; //0
    input = {{"P2", "N", "P1"},{"P3", "N", "P2"},{"P1", "N", "P3"}};
    cout << isValid(input) << endl; //0
}