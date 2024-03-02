/*
First question of: https://leetcode.com/discuss/interview-question/4326333/Amazon-OA

You are given a tree of n nodes (1 to n). Node 1 is root. 
Given 3 arrays of length n-1: tree_from, tree_to, tree_weight
    -> means edge from tree_from[i] to tree_to[i] with weight tree_weight[i].
Given another array arr of length n.
    -> gives value of node[i].

A tree is special if for all (x, y) pair of nodes such that y is in subtree of x, distance(x,y) <= arr[y].

1 operation consists of removing 1 leaf node of a tree. How many minimum number of operations do we need to do to make the tree special?

Example:
tree_from = [1,1,3,3]
tree_to = [2,3,4,5]
tree_weight = [8,5,2,7]
arr = [12,2,27,11,1]

        1(12)
      /     \
   -(8)-   -(5)-
    /         \
   2(2)      3(27)
             /   \
          -(2)- -(7)-
           /       \
         4(11)     5(1)

-()- gives weight of edge.
() next to number gives value of node.

As we can see, dist(2)=8 > arr[2]=2. (1-indexed). So we have to remove node 2.
Then dist(5)=12 > arr[5]=1. So we need to remove node 5 as well.
Other nodes can exist. So answer = 2.

Example 2

tree_from = [3,1,2]
tree_to = [2,3,4]
tree_weight = [-9,93,-57]
arr = [14,66,86,37]

1(14) -- [93] -- 3(86) -- [-9] -- 2(66) -- [-57] -- 4(37)

[] gives edge weight
Here we can see dist(3)=93 > arr[3]=86 so node 3 has to be removed, causing both node 2 and 4 to be removed as well. So output = 3.

*/ 
#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<pair<int, int> > > &tree, vector<int> &arr, int current, int &visited, int dist){
    visited++;
    for(int i=0; i<tree[current].size(); i++){
        int child = tree[current][i].first;
        int weight = tree[current][i].second;
        if(arr[child] >= dist + weight) dfs(tree, arr, child, visited, dist+weight);
    }
    return;
}

int minRemovalToMakeSpecialTree(vector<int> tree_from, vector<int> tree_to, vector<int> tree_weight, vector<int> arr) {
    /*
    Approach. We can either do dfs or bfs. 
    If DFS
        -> Start from root. If distance to next node is > the value of next node, return. In each dfs call, we increment count.
        At the end, see how many nodes were visited. Subtract them from total number of nodes.

    If BFS
        -> Start from root. Put in queue all nodes for which distance from root is less than equal to the value of the node. Keep counting how many nodes were put in the queue. Subtract from total number of nodes.
    */
    int n = arr.size();
    vector<vector<pair<int, int> > > tree(n);
    for(int i=0; i<tree_from.size(); i++)
        tree[tree_from[i]-1].push_back(make_pair(tree_to[i]-1, tree_weight[i]));
    int visited = 0;

    // implementing dfs approach
    dfs(tree, arr, 0, visited, 0);
    return n - visited;
}

int main(){
    cout << minRemovalToMakeSpecialTree({3,1,2}, {2,3,4}, {-9,93,-57}, {14,66,86,37}) << endl; // 3
    cout << minRemovalToMakeSpecialTree({1,1,3,3}, {2,3,4,5}, {8,5,2,7}, {12,2,27,11,1}) << endl; // 2
}