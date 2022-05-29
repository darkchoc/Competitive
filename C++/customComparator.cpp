#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> PII;

void howToPassWithCustomComparator(priority_queue<PII, vector<PII>, std::function< bool(const PII, const PII)> > &pq){
    return;
}

//return true if a has to be pushed downward in the priroity queue and false if a has to go towards the top.
bool cmp (const pair<int, int> &a, const pair<int, int> &b){
    if(a.first == b.first){
        return a.second < b.second;
    } else return a.first > b.first;
};

int main(){

    priority_queue<pair<int, int>, vector<pair<int, int> >, std::function<bool(const PII, const PII)>> pq(cmp);
    pq.push(make_pair(1,2));
    pq.push(make_pair(1,3));
    pq.push(make_pair(2,4));

    howToPassWithCustomComparator(pq);

    while(!pq.empty()){
        cout << pq.top().first << " " << pq.top().second << endl;
        pq.pop();
    }

}