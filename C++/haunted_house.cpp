//Question: https://www.hackerrank.com/contests/w15/challenges/haunted-house/problem

#include <bits/stdc++.h>
using namespace std;

//binary search approach is Wrong!!!!!
bool possible(vector<pair<int, int> > &nakhre, int peopleGoing){
    int howManyWilling = 0;
    for(int i=0; i<nakhre.size(); i++){
        if(nakhre[i].first + 1 <= peopleGoing && nakhre[i].second + 1 >= peopleGoing)
            howManyWilling++;
    }
    return howManyWilling>=peopleGoing;
}

int maxPeopleForHauntedHouse_WRONG(vector<pair<int, int> > &nakhre){
    //FUNCTION ISN'T MONOTONIC so can't apply binary search. There can be 4 people willing to go with total 4 people, 7 people willing to go with total 7 people, but 0 people willing to go with 5 people. 
    
    int n = nakhre.size();
    int low = 0, high = n;
    //Our binary values would look like this: T T T T T F F F F. We want to find the max i for which we get true
    while(low < high){
        int mid = (low + high + 1)/2; //bias it towards high
        if(possible(nakhre, mid)){
            low = mid;
        } else {
            high = mid-1;
        }
    }
    return low;
}

int maxPeopleForHauntedHouse(vector<pair<int, int> > &nakhre){
    int n = nakhre.size(); //answer will be between 0 and n
    vector<int> willing (n+1, 0);
    /*
    for every guy, let's add 1 to willing[nakhre[i].first+1].. meaning 1 more person is willing to go if nubmer of people are nakhre[i].first+1. 
    And let's subtract 1 from willing[nakhre[i].second+2].. meaning 1 less person is willing to go if number of people are >= nakhre[i].second+2.
    So if we iterate on "willing", each index will tell us how many people are willing to go if there are i people going.
    
    Also, we're adding 1 to nakhre[i].first/second to get total number of people this person is willing to go with, instead of number of "other" people he is willing to go with.
    */
    for(int i=0; i<n; i++){
        if(nakhre[i].first+1 > n)
            continue;
        else
            willing[nakhre[i].first+1]++;
        if(nakhre[i].second+1 > n)
            continue; //he is willing to go with all n people, so he is ready for all #people from nakhre[i].first+1 to n. No need to subtract
        else
            willing[nakhre[i].second+2]--;
    }
    
    //now iterate on willing
    int peopleCurrentlyReady = 0;
    int maxPeopleReady = 0;
    for(int i=0; i<=n; i++){
        peopleCurrentlyReady += willing[i]; //with every index, we add difference of people who were ready from this index onward and people who declined from this index. Index gives value of #total people we plan to take
        if(peopleCurrentlyReady >= i){
            //if we are planning to take i people, a valid answer would be when people willing to go are more than equal to i.
            maxPeopleReady = max(maxPeopleReady, i); //we'll take i people, even though more are ready to go if taking i in total. But since taking i people in total, we would have to leave some people behind, even though they were ready.
        }
    }
    return maxPeopleReady;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int people;
    cin >> people;
    vector<pair<int, int> > nakhre;
    int x, y;
    for(int i=0; i<people; i++){
        cin >> x >> y;
        nakhre.push_back(make_pair(x, y));
    }
    //cout << maxPeopleForHauntedHouse_WRONG(nakhre);
    cout << maxPeopleForHauntedHouse(nakhre);
    return 0;
}
