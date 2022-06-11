/*
Question: https://leetcode.com/discuss/interview-question/1582402/Google-or-Onsite-or-Minimum-Cost-to-Travel

A car has to travel from point A to point B.
The fuel capacity of the tank of the car is V units.
Initially, the tank is completely filled.

There are m Gas Stations at points D1, D2, .... Dm on the way between A and B and the cost of fuel at each Gas Station is given by a price array P, where Pi = price of fuel per unit at Gas Station i. Each Gas Station is having unlimited quantity of fuel and you may fill as much as you want (obviously <=V).

Return the minimum cost to travel from point A to point B.

The function is as follows:

int minimumCost(int V, int A, int B, vector<int> dis, vector<int> price)
}

Approach: 
For two petrol pumps, i and j, such that i < j, if price[i] <= price[j], we would prefer buying as little of petrol as possible from j and rather buy from i. 
Let petrolRequired[i] be the level upto which we should fill or tank at petrol pump i. So considering the above j and i, we would want to fill enough petrol in our car at ith station itself that when we reach j, we already have petrolRequired[j] petrol with us.

If we consider petrol pumps from right to left, what we are doing is that for every station, we will try to fill as much petrol as possible at this station, considering the stations on right of it which have price > current station's price. If we encounter a station k on right which has price < current station's price, then we will only fill upto to the level that allows us to reach station k, as rest we can fill from there itself. 

Now, when we move further left, do we need to consider petrol pumps that we have discarded (because we found another cheaper petrol pump on their left from where we can fill enough fuel to let go the need to fill fuel at that expensive station)? No, right! So we can discard them and only consider those stations from which we are currently considering buying petrol. We can maintain a stack for this, popping those which get discarded.

*/

#include <bits/stdc++.h>
using namespace std;

int getMinCost(vector<int> pumps, vector<int> price, int capacity, int start, int end){
    if(end-start <= capacity)
        return 0;
    //only consider petrol pumps >= start and < end.
    vector<int> location;
    vector<int> cost;
    for(int i=0; i<pumps.size(); i++){
        if(pumps[i] > start && pumps[i] < end){
            location.push_back(pumps[i]);
            cost.push_back(price[i]);
        }
    }

    //check whether it is possible to reach end from start
    int n = location.size();
    if(n==0 || location[0]-start > capacity || end-location[n-1] > capacity)
        return -1;
    for(int i=1; i<n; i++)
        if(location[i] - location[i-1] > capacity)
            return -1;

    //start main algorithm
    vector<int> petrolRequired (n, 0);
    stack<int> st; //keeps index of petrol pump, in location array
    //initialize
    petrolRequired[n-1] = end - location[n-1];
    st.push(n-1);
    for(int i=n-2; i>=0; i--){
        petrolRequired[i] = location[i+1] - location[i]; //st.top() would be i+1 (pushed in previous iteration)
        while(!st.empty() && cost[st.top()] >= cost[i]){
            //means we can prefer buying petrol at i instead of st.top()
            //check if we buy petrolRequired[st.top()] here 
            if(petrolRequired[st.top()] <= capacity - (petrolRequired[i])){
                petrolRequired[i] += petrolRequired[st.top()];
                st.pop(); //we can discard buying petrol from st.top()
            } else {
                //fill to full capacity
                petrolRequired[i]=capacity;
                break;
            }
        }
        st.push(i);
    }

    int tankLevel = capacity;
    int position = start;
    int moneyRequired = 0;
    for(int i=0; i<n && position < end; i++){
        tankLevel -= location[i] - position;
        if(tankLevel < petrolRequired[i]){
            int toPurchase = petrolRequired[i] - tankLevel;
            tankLevel = petrolRequired[i];
            cout << "Buying " << toPurchase << " at " << i << " for " << toPurchase*cost[i] << endl;
            moneyRequired += toPurchase*cost[i];
        }
        position = location[i];
    }
    return moneyRequired;
}

int main(){
    cout << getMinCost({2,14,20,22,26,32,39,45,50,58,63,67,74,76,80,85,90}, {5,2,8,4,6,5,10,13,8,6,10,12,1,9,3,9,5}, 10, 5, 81) << endl;
}