/*
We have Uber HCV(High Capacity Vehicles) plying on the same routes in loops. Every route has a certain number of stops. The routes are represented as 2D array as below [[1, 2, 7], [3, 6, 7]] where route[i] shows the route that the ith HCV takes. For e.g 1st HCV route would be 1 -> 2 -> 7 -> 1 -> 2 -> 7... and so on. Find the minimum number of HCV hops needed given a source and a destination hop.
Example 1: Input: HCV routes: [[1, 2, 7], [3, 6, 7]] , Source: 1, Destination: 7 Output: 0 (get into the first HCV on stop 1 and get down at stop 7, no hops needed)
Source: 1, Destination: 6 Output: 1 (get into the first HCV on stop 1, transfer on stop 7 to the next HCV and then get down at stop 6 from the other HCV, hence it needed 1 hop)
Return -1, if it's unable to reach the destination from the given source.
Example 2: HCV routes: [[1,2,3,4,5,6,7,8,9,10], [2,7]]
Source: 1, Destination: 7
Output: 0
(A potential route could be 1->2->3->4->5->6->7 which uses 1 bus, hence 0 hops and 6 moves or 1->2->7 which uses 2 buses and just 2 moves.
In this case, the first route would be the answer because the aim is minimum hops and not minimum stops)




Potential Follow-Up Questions (optional)
Follow up 1: Give weight to the buses, for e.g. cost of hoping on bus "a" is 1, cost of hoping on bus "b" is 2 etc. In this case, is the candidate able to modify BFS traversal to Dijkstra
Follow up 2: Introduce "ticket cost", which is the cost to go from stop A to stop B and instead of optimizing "hops", optimize on "cost", and discuss what changes are required in the original solution.
*/

#include <bits/stdc++.h>
using namespace std;

void buildStopToRoutesMapping(map<int, vector<int> > &stopToRoutes, vector<vector<int> > &routes){
    for(int i=0; i<routes.size(); i++)
        for(int j=0; j<routes[i].size(); j++)
            stopToRoutes[routes[i][j]].push_back(i);
}

void buildGraphOfRoutes(vector<vector<int> > &graph, map<int, vector<int> > &stopToRoutes){
    for(map<int, vector<int> >::iterator stop=stopToRoutes.begin(); stop!=stopToRoutes.end(); stop++){
        if(stop->second.size() > 1){
            //means multiple routes intersect here, so form edge between them
            vector<int> &intersectingRoutes = stop->second;
            for(int i=0; i<intersectingRoutes.size(); i++){
                for(int j=i+1; j<intersectingRoutes.size(); j++){
                    graph[intersectingRoutes[i]].push_back(intersectingRoutes[j]);
                    graph[intersectingRoutes[j]].push_back(intersectingRoutes[i]);
                }
            }
        }
    }
}

int applyBFS(vector<vector<int> > &graph, int source, int target, map<int, vector<int> > &stopToRoutes){
    //possible starting routes
    vector<int> &possibleStartRoutes = stopToRoutes[source];
    
    //mark them as visited and add to queue
    set<int> visitedRoutes (possibleStartRoutes.begin(), possibleStartRoutes.end());
    
    queue<int> q;
    for(int i=0; i<possibleStartRoutes.size(); i++)
        q.push(possibleStartRoutes[i]);

    //possible target routes
    set<int> targetRoutes (stopToRoutes[target].begin(), stopToRoutes[target].end());

    int distance = 1;
    while(!q.empty()){
        int n = q.size();
        while(n){
            int currentRoute = q.front();
            q.pop();
            if(targetRoutes.find(currentRoute)!=targetRoutes.end())
                return distance;
            for(int i=0; i<graph[currentRoute].size(); i++){
                if(visitedRoutes.find(graph[currentRoute][i])==visitedRoutes.end()){
                    visitedRoutes.insert(graph[currentRoute][i]);
                    q.push(graph[currentRoute][i]);
                }
            }
            n--;
        }
        distance++;
    }
    return -1;
}

int findMinHops(vector<vector<int> > &routes, int source, int target){
    //If I can start from some route that passes through source and finally get on some route that has target on it, my job will be done. So here, instead of stops being nodes of a graph, we actually need routes as nodes. Two nodes (routes) are connected if they share a common stop.

    //if source == target, return 0
    if(source == target)
        return 0;

    //First I'm checking what all routes fall on a particular stop. All those routes that pass through a particular stop will be connected.
    map<int, vector<int> > stopToRoutes;
    buildStopToRoutesMapping(stopToRoutes, routes);
    
    //Create graph of routes
    vector<vector<int> > graph (routes.size());
    buildGraphOfRoutes(graph, stopToRoutes);

    return applyBFS(graph, source, target, stopToRoutes);
}

int applyDjikstra(vector<vector<int> > &graph, map<int, vector<int> > &stopToRoutes, vector<int> &routeCosts, int source, int target){
    //The difference between regular djisktra and in this case is that instead of edges having weights, the nodes have weights. So visiting a node will cost us money. Also, in regular djisktra, it is possible that during processing, the distance of a node gets updated as a cheaper route might be found, but here if a node is being put into the min_heap, it can very well be marked visited as the cost to reach it won't get reduced in any case. 

    //possilbe starting routes
    vector<int> &possibleStartRoutes = stopToRoutes[source];

    //add these to min heap for djikstra and also mark them as visited
    set<int> visitedRoutes;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > min_pq;
    for(int i=0; i<possibleStartRoutes.size(); i++){
        min_pq.push(make_pair(routeCosts[possibleStartRoutes[i]], possibleStartRoutes[i]));
        visitedRoutes.insert(possibleStartRoutes[i]);
    }

    //possible target routes
    set<int> targetRoutes (stopToRoutes[target].begin(), stopToRoutes[target].end());

    while(!min_pq.empty()){
        pair<int, int> p = min_pq.top();
        min_pq.pop();
        int currentCost = p.first;
        int currentRoute = p.second;
        if(targetRoutes.find(currentRoute)!=targetRoutes.end())
            return currentCost;
        for(int i=0; i<graph[currentRoute].size(); i++){
            if(visitedRoutes.find(graph[currentRoute][i])==visitedRoutes.end()){
                visitedRoutes.insert(graph[currentRoute][i]);
                min_pq.push(make_pair(currentCost + routeCosts[graph[currentRoute][i]], graph[currentRoute][i]));
            }
        }
    }
    return -1;
}

int findLeastCostRoot(vector<vector<int> > &routes, vector<int> &routeCosts, int source, int target){

    //if source == target, return 0
    if(source == target)
        return 0;

    map<int, vector<int> > stopToRoutes;
    buildStopToRoutesMapping(stopToRoutes, routes);

    vector<vector<int> > graph (routes.size());
    buildGraphOfRoutes(graph, stopToRoutes);

    return applyDjikstra(graph, stopToRoutes, routeCosts, source, target);
}

int main(){
    vector<vector<int> > routes {{1,2,7},{3,6,7}};
    int source = 1;
    int target = 6;
    cout << findMinHops(routes, source, target) << endl; // 2
    cout << findMinHops(routes, 1, 7) << endl; // 1
    cout << findMinHops(routes, 1, 5) << endl; // -1

    routes = {{1,2,3,4,5,6,7,8,9,10},{2,7}};
    cout << findMinHops(routes, 1, 7) << endl; // 1

    routes = {{1,2},{3,4},{1,5},{4,6},{5,7},{7,9,3},{2,6,8}}; 
    source = 1;
    target = 4;
    //two routes possilbe: R1(1-2)->R7(2-6)->R4(6-4) and R3(1-5)->R5(5-7)->R6(7-3)->R2(3-4)
    cout << findMinHops(routes, source, target) << endl;  //should return first route  -> 3
    vector<int> routeCosts {10, 5, 5, 5, 10, 5, 15}; 
    cout << findLeastCostRoot(routes, routeCosts, source, target) << endl; //should return second route -> 25
    cout << findLeastCostRoot(routes, routeCosts, 10, 1) << endl; // -1
    cout << findLeastCostRoot(routes, routeCosts, 8, 9) << endl; //two routes R7(8-2)R1(2-1)R3(1-5)R5(5-7)R6(7-9) : cost 45, R7(8-6)R4(6-4)R2(4-3)R6(3-9) : cost 30 -> ans = 30

    //Follow up 2:
    //form graph between stops instead of routes? Edge weights = ticket cost, and then apply djikstra from source to target?
}

