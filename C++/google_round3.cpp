/*
Given a list of cities and distances between them, find the shortest path from start city to end city.
Example:
(A, B, 75), (A, C, 150), (B, C, 25), (B, D, 150), (C, D, 75)

Basically apply djikstra, but a bit modified to get shortest path as well.


//Follow up:
Now you're also given the car's efficient speed. Also, for each road you are given the speed limit. The car will travel at exactly the speed limit on that road. 
For deviation on either side of the efficient speed, the car's efficiency reduces linearly.
Eg: if efficient speed is 50, then both at 49 and 51, the car would be equally inefficient. At 48 and 52, again same.
You are also given the gas that would be spent per mile if travelling at efficient speed. We can get fuel at other speeds using: 

Fuel consumed at speed x, per mile = | x - efficientSpeed| + minFuel

Return the most efficient path - (Consuming the least gas).


My approach: 
In the interview I made a mistake saying that minFuel can be assumed to be 0, but that is wrong. Two paths having exact speed as efficient speed will have different fuel consumption based on distance.

But my approach was fine in the sense that I want to decide the weight based on fuel consumed on the road.
So while building graph:
    int w = calculateGasReqd(get<3>(roads[i]), efficient_speed, minFuel, get<2>roads[i]); 

    //get<3>(roads[i]) => speed_limit, get<2>(roads[i]) => distance, 

    The gas reqd would be: (|speed_limit - efficient_speed| + minFuel) * distance.

*/


#include <bits/stdc++.h>
using namespace std;

void printShortestPath(string start, string end, vector<tuple<string, string, int> > roads){
    //build graph
    unordered_map<string, set<tuple<int, string> > > graph;
    for(int i=0; i<roads.size(); i++){
        string u = get<0>(roads[i]);
        string v = get<1>(roads[i]);
        int w = get<2>(roads[i]);
        graph[u].insert(make_tuple(w, v));
        graph[v].insert(make_tuple(w, u));
    }

    //djikstra
    unordered_map<string, int> distance;
    unordered_map<string, string> parent;
    distance[start] = 0;
    set<tuple<int, string> > minPq;
    minPq.insert(make_tuple(0, start));
    while(!minPq.empty()){
        tuple<int, string> current = *minPq.begin();
        minPq.erase(minPq.begin());
        string city = get<1>(current);
        int dist = get<0>(current);
        if(city == end)
            break;
        for(auto it = graph[city].begin(); it!=graph[city].end(); it++){
            string neighbour = get<1>(*it);
            int roadDistance = get<0>(*it);
            if(distance.find(neighbour)==distance.end()){
                distance[neighbour] = roadDistance + dist;
                parent[neighbour] = city;
                minPq.insert(make_tuple(distance[neighbour], neighbour));
            } else if(distance[neighbour] > roadDistance + dist){
                minPq.erase(make_tuple(distance[neighbour], neighbour));
                distance[neighbour] = roadDistance + dist;
                parent[neighbour] = city;
                minPq.insert(make_tuple(distance[neighbour], neighbour));
            }
        }
    }

    //build path
    vector<string> path;
    if(parent.find(end) == parent.end()){
        cout << "Path doesn't exist";
        return;
    }
    string currentCity = end;
    while(parent.find(currentCity)!=parent.end()){
        path.push_back(currentCity);
        currentCity = parent[currentCity];
    }
    path.push_back(currentCity);
    reverse(path.begin(), path.end());

    //print path
    for(int i=0; i < path.size(); i++)
        cout << path[i] << " ";
    cout << endl;
}

int main(){
    printShortestPath("A", "D", {make_tuple("A", "B", 75), make_tuple("A", "C", 150), make_tuple("B", "C", 25), make_tuple("B", "D", 150), make_tuple("C", "D", 75)});
}


