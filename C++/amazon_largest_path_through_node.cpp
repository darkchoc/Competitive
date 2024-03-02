/*
https://www.reddit.com/r/leetcode/comments/1ayxehk/amazon_oa_sde1/

Given a graph,
1. Find the minimum distance between two nodes. 
2. Find the largest distance passing through a node and return the distance. 

The graph is undirected and weights are positive.

Example:
A -- 2 -- B -- 6 -- C --4-- D
          |         |\
          8         5 8
          |         |  \
          E         F   G

Here, for example, largest distance passing through B is of 22 length (EBCG)

Now, the question isn't completely clear.
1. Is it a tree or a graph?
2. For minimum distance there can be two possiblities:
    -> Find minimum distance between any two nodes
    -> Find minimum distance of all nodes from a particular source node?
3. For largest distance, there are three possibilities:
    -> Largest path for each node
    -> Largest path passing through source node
    -> Largest path within the graph/tree?

Case A: It's a tree
1.a. We can apply Floyd Warshall to get distance between any two nodes of the tree.
1.b. We can do dfs starting from source and get distance of each node  
2.a. Read 2.c. first. So we can apply the same algo of diameter of N-ary tree. Only addition is that while we are calculating max path passing through a node and taking it's max with answer variable, we also store the max path for that particular node in an array/map.
2.b. We can apply dfs where each node (except source) returns max length child. But for source node, we take two maximum length children and add them and return. 
2.c. Similar to diameter of N-ary tree where we keep a global variable holding answer. At each node, we find max path passing through it by summing 2 longest length children, take max with answer variable, and return the length of longest child upwards.


Case B: It's a graph
1.a. We can apply Floyd Warshall to get distance between any two nodes of the graph.
1.b. We can apply Djikstra's.

2.a,2.b,2.c -> If Eulerian path exists, then answer is simply sum of all edges (for all 3 cases).
A graph has Eulerian path if it has exactly 2 odd degree vertices. If it has 0 odd degree vertices, then it has Eulerian Cycle (which is also good as that's also a Eulerian path). But if it has greater than 2 odd degree vertices, graph won't have a Eulerian Path.

Else:
I am not sure how to go about it now. 




I'll try to implement both.
Let's say we're given two arrays: from, to -> these are string arrays giving node names such that there is an edge between from[i] and to[i].
Let there be another array, weights -> weight[i] gives weight of edge between from[i] and to[i].

Since the first part asks to calculate minimum distance between two nodes, I'm assuming it's a graph and not a tree. There can be cycles. Had it been a tree, finding minDistance from source would have been quite easy. Just apply dfs.


*****

At the moment, while implementing shortest distance, I thought of it to be a graph and implemented Djikstra. While finding largest path, I considered it to be a tree and calculated largest path passing through source. 
*/
#include <bits/stdc++.h>
using namespace std;


int dfsSingleSource(map<char, vector<pair<int, char> > > &tree, char parent, char current){
    int maxDist = 0;
    for(int i=0; i<tree[current].size(); i++){
        if(tree[current][i].second != parent){
            maxDist = max(maxDist, tree[current][i].first + dfsSingleSource(tree, current, tree[current][i].second));
        }
    }
    return maxDist;
}

void singleSourceFunction(vector<char> from, vector<char> to, vector<int> weight, char source){
    /*
    Implementing two things.
    1. Min distance of every other node from source.
    2. Get max distance path passing from source.
    */
    // Create tree
    map<char, vector<pair<int, char> > > tree;
    for(int i=0; i<from.size(); i++){
        tree[from[i]].push_back(make_pair(weight[i], to[i]));
        tree[to[i]].push_back(make_pair(weight[i], from[i]));
    }
    // Part 1 - Djikstra
    map<char, int> dist;
    dist[source] = 0;
    set<pair<int, char> > minPq;
    minPq.insert(make_pair(0, source));
    while(!minPq.empty()){
        pair<int, char> p = *minPq.begin();
        minPq.erase(minPq.begin());
        char u = p.second;
        for(int i=0; i<tree[u].size(); i++){
            char v = tree[u][i].second;
            int w = tree[u][i].first;
            if(dist.find(v)==dist.end()){
                dist[v] = dist[u] + w;
                minPq.insert(make_pair(dist[v], v));
            } else if(dist[v] > dist[u] + w) {
                minPq.erase(make_pair(dist[v], v));
                dist[v] = dist[u] + w;
                minPq.insert(make_pair(dist[v], v));
            }
        }
    }
    cout << "Printing distances from source: ";
    for(map<char, int>::iterator it = dist.begin(); it!=dist.end(); it++)
        cout << it->first << ":" << it->second << ", ";
    cout << endl;

    // Part 2 -> find longest path from source.
    /*
    Approach: Try to find out length of two longest children for source node. But for all other nodes, just return length of longest child.
    */
    int max1 = 0, max2 = 0;
    for(int i=0; i<tree[source].size(); i++){
        int longestPath = tree[source][i].first + dfsSingleSource(tree, source, tree[source][i].second);
        if(longestPath > max1) {
            max2 = max1;
            max1 = longestPath;
        } else if(longestPath > max2){
            max2 = longestPath;
        }
    }
    cout << "Length of longest path through source: " << max1 + max2 << endl;
}

int main() {
    singleSourceFunction({'A','B','B','C','C','C'}, {'B','C','E','D','F','G'}, {2,6,8,4,5,8}, 'B');
    // Distances: A:2, B:0, C:6, D:10, E:8, F:11, G:14 and longest path length = 22.
}