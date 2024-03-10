#include <bits/stdc++.h>
using namespace std;

set<vector<string> > getCombinations(vector<pair<int, string> > visits){
    set<vector<string> > s;
    for(int i=0; i<visits.size(); i++)
        for(int j=i+1; j<visits.size(); j++)
            for(int k=j+1; k<visits.size(); k++)
                s.insert({visits[i].second, visits[j].second, visits[k].second});
    return s;
}

void solve(vector<string> username, vector<int> timestamp, vector<string> website) {
    map<string, vector<pair<int, string> > > mp;
    for(int i=0; i<username.size(); i++){
        mp[username[i]].push_back(make_pair(timestamp[i], website[i]));
    }
    map<vector<string>, int> frequency;
    int maxFreq = 0;
    vector<string> maxFreqCombo;
    for(auto it = mp.begin(); it!=mp.end(); it++){
        if(it->second.size() < 3) continue;
        // sort on timestamp
        sort(it->second.begin(), it->second.end());
        // create combinations of 3
        set<vector<string> > combinations = getCombinations(it->second);
        for(auto it2=combinations.begin(); it2!=combinations.end(); it2++){
            int newFreq = ++frequency[*it2];
            if(newFreq > maxFreq){
                maxFreq = newFreq;
                maxFreqCombo = (*it2);
            } else if(newFreq == maxFreq && (*it2) < maxFreqCombo)
                maxFreqCombo = (*it2);
        }
    }
    for(int i=0; i<maxFreqCombo.size(); i++)
        cout << maxFreqCombo[i] << ", ";
    cout << endl;
    return;
}

int main(){
    solve({"joe","joe","joe","james","james","james","james","mary","mary","mary"}, {1,2,3,4,5,6,7,8,9,10}, {"home","about","career","home","cart","maps","home","home","about","career"}); // home, about, career
    solve({"ua","ua","ua","ub","ub","ub"}, {1,2,3,4,5,6}, {"a","b","a","a","b","c"}); // a, b, a
}