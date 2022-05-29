#include <bits/stdc++.h>
using namespace std;

void buildGraph(vector<vector<int> > &input, map<int, set<int> > &graph, map<int, int> &hotelScores){
    for(int i=0; i<input.size(); i++){
        int hotel = input[i][0];
        int parent = input[i][1];
        int score = input[i][2];
        
        if(graph[parent].find(hotel)!=graph[parent].end())
            continue;
        hotelScores[hotel] += score;
        if(parent!=-1)
            graph[parent].insert(hotel);
    }
}

void getHotelRoots(vector<vector<int> > &input, set<int> &hotelRoots){
    for(int i=0; i<input.size(); i++)
        if(input[i][1]==-1)
            hotelRoots.insert(input[i][0]);
}

int dfs(map<int, set<int> > &graph, map<int, int> &hotelScores, int currentHotel){
    for(set<int>::iterator i = graph[currentHotel].begin(); i != graph[currentHotel].end(); i++){
        hotelScores[currentHotel] += dfs(graph, hotelScores, *i);
    }
    return hotelScores[currentHotel];
}

vector<vector<int> > getHotelChains(vector<vector<int> > &input){
    map<int, set<int> > graph;
    map<int, int> hotelScores;
    buildGraph(input, graph, hotelScores);

    set<int> hotelRoots;
    getHotelRoots(input, hotelRoots);

    vector<vector<int> > rootHotelScores;
    for(set<int>::iterator it = hotelRoots.begin(); it != hotelRoots.end(); it++)
        rootHotelScores.push_back({*it, dfs(graph, hotelScores, *it)});

    sort(rootHotelScores.begin(), rootHotelScores.end(), [](vector<int> &a, vector<int> &b){
        if(a[1] == b[1])
            return a[0] < b[0];
        else return a[1] > b[1]; 
    });
    return rootHotelScores;
}

int getParent(map<int, int> &parent, int hotel){
    while(parent[hotel]!=hotel){
        parent[hotel] = parent[parent[hotel]];
        hotel = parent[hotel];
    }
    return hotel;
}

vector<vector<int> > getHotelChainsDSU(vector<vector<int> > &input){
    //There is issue of double addition in this. I think it can be handled by checking which hotel is already visited, while calculation scores in second loop.
    //The important trick here is that we first construct DSU and then construct scores. To do both in one pass would require more complexity.
    map<int, int> parent;
    map<int, int> scores;


    //first form DSU
    for(int i=0; i<input.size(); i++){
        int hotel = input[i][0];
        int parentHotel = input[i][1];

        if(parentHotel==-1){
            parent[hotel] = hotel;
        } else {
            if(parent.find(parentHotel)==parent.end())
                parent[parentHotel] = parentHotel;
            int highestParent = getParent(parent, parentHotel);
            parent[hotel] = highestParent;
        }
    }

    //now add scores
    for(int i=0; i<input.size(); i++){
        int hotel = input[i][0];
        int score = input[i][2];

        int topParent = getParent(parent, hotel);
        scores[topParent] += score;
    }

    vector<vector<int> > hotelScores;
    for(map<int, int>::iterator it = scores.begin(); it != scores.end(); it++)
        hotelScores.push_back({it->first, it->second});
    
    sort(hotelScores.begin(), hotelScores.end(), [](const vector<int> &a, const vector<int> &b){
        //if need to keep a before b, return true.
        if(a[1]==b[1])
            return a[0] < b[0]; 
        else return a[1] > b[1];
    });
    return hotelScores;
}

int main(){
    vector<vector<int> > input = {
        {3,0,14}, {0, -1, 10}, {4, 0, 44}, {6, -1, 7}, {10, 6, 13}, {7, 6, 17}, {2, -1, 2}, {14, 2, 9}, {25, 14, 10}, {12, 2, 10}, {13, 0, 1}, {14, 2, 9}
    };
    int k = 2;
    vector<vector<int> > hotelChains = getHotelChains(input);
    for(int i=0; i<min(k, (int)hotelChains.size()); i++)
        cout << "{" << hotelChains[i][0] << ", " << hotelChains[i][1] << "} ";
    cout << endl;

    hotelChains = getHotelChainsDSU(input);
    for(int i=0; i<min(k, (int)hotelChains.size()); i++)
        cout << "{" << hotelChains[i][0] << ", " << hotelChains[i][1] << "} ";
    cout << endl;
    return 0;
}