/*
Question: https://stackoverflow.com/questions/34861791/how-can-i-run-vscode-with-sudo-on-osx

Question:
A country has multiple cities which are represented as vertices of a graph and cities are interconnected with each other through roads. These roads are represented as undirected edges between the vertices with unit weight (same weight for all roads). Now calculate the shortest path between 'A' to 'B' such that you are travelling in a car with a capacity of 'c' and there are only few cities which have fuel stations where you can fill the car to complete capacity (when you visit that vertex). When you travel from one city to another you conume a unit of fuel and at the source city you start with full capacity of fuel.

Sample Input:
Roads: [[1,2],[2,3],[3,4],[4,5],[4,6],[6,7]]
A: 1, B: 7, capacity 'c': 4
fuel stations: [5]

Graphical notation of input graph
1
|
2
|
3
|
4 - 5
|
6
|
7

sample output: 7 (as shortest path is 1-2-3-4-5-4-6-7)

Approach: My first approach is to apply BFS. The state is given by city and the amount of fuel we have there. If we have already visited a state, we don't add it back to the queue. Also, when we arrive at a city having fuel, we simply add that state to queue (if not already visited). 

Optimisation: It only makes sense to add an already visited city to queue, if we are visiting it this time with more fuel. So for each city, we can keep track of max fuel with which we have visited it. This actually removes the need to keep visited set.

*/

#include <bits/stdc++.h>
using namespace std;

int minDistance(vector<vector<int> > roads, vector<int> stations, int capacity, int n){
    //Assuming we are always going from 1 to n.
    //build graph
    vector<vector<int> > graph (n);
    for(int i=0; i<roads.size(); i++){
        graph[roads[i][0]-1].push_back(roads[i][1]-1);
        graph[roads[i][1]-1].push_back(roads[i][0]-1);
    }

    //initialisations
    set<int> citiesWithFuel;
    for(int i=0; i<stations.size(); i++)
        citiesWithFuel.insert(stations[i]-1);
    vector<int> maxFuelForThisCity (n, 0);

    //start bfs
    queue<pair<int, int> > q;
    q.push(make_pair(0, capacity));
    maxFuelForThisCity[0]=capacity;
    int distance = 0;
    while(!q.empty()){
        int s = q.size();
        while(s){
            pair<int, int> p = q.front();
            q.pop();
            int u = p.first;
            if(u==n-1)
                return distance;
            int fuel = p.second;
            for(int i=0; i<graph[u].size() && fuel>0; i++){
                int v = graph[u][i];
                int fuelOnArrival = fuel-1;
                if(citiesWithFuel.find(v)!=citiesWithFuel.end())
                    fuelOnArrival = capacity;
                if(maxFuelForThisCity[v] >= fuelOnArrival)
                    continue;
                maxFuelForThisCity[v] = fuelOnArrival;
                q.push(make_pair(v, fuelOnArrival));
            }
            s--;
        }
        distance++;
    }
    return -1;
}

int main(){
    cout << minDistance({{1,2},{2,3},{3,4},{4,5},{4,6},{6,7}}, {5}, 4, 7) << endl;
}