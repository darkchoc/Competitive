#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

string getOrdering(vector<string> words) {
    // construct graph and indegree
    unordered_map<char, vector<char> > graph;
    unordered_map<char, int> indegree;
    // set indegree of all characters as 0
    for(int i=0; i<words.size(); i++)
        for(int j=0; j<words[i].length(); j++)
            indegree[words[i][j]]=0;
    // now construct graph
    for(int i=1; i<words.size(); i++){
        // comparing words[i] and words[i-1]
        int j = 0;
        for(j; j<words[i].length() && j<words[i-1].length(); j++) {
            if(words[i][j]!=words[i-1][j]){
                graph[words[i-1][j]].push_back(words[i][j]);
                indegree[words[i][j]]++;
                break;
            }
        }
        // if j reached end of word[i], then it is wrong mapping (Case: words[i-1]="ab", words[i]="a")
        if(j==words[i].length()) return "";
        // if we want to extract the graph creation function, then instead of returning "", we can clear
        // the graph and indegree maps and return the function from there.
    }

    // now, add to queue all chars where indegree[char] = 0. Also, we can either keep count of how many
    // characters are added to queue, and compare that with size of indegree map to see if cycle present 
    // or not. Or we can compare size of ordering (result we return) to indegree map's size, since each
    // element is of size 1, so elements added to queue = length of ordering.
    string ordering = "";
    queue<char> q;
    for(unordered_map<char, int>::iterator it=indegree.begin(); it!=indegree.end(); it++){
        if(it->second==0)
            q.push(it->first);
    }
    while(!q.empty()){
        char c = q.front();
        q.pop();
        ordering.push_back(c);
        for(int i=0; i<graph[c].size(); i++){
            // reduce indegree of neighbours
            indegree[graph[c][i]]--;
            if(indegree[graph[c][i]]==0)
                q.push(graph[c][i]);
        }
    }
    if(ordering.length() == indegree.size()) return ordering;
    return "";
}

int main(){
    cout << getOrdering({"wrt","wrf","er","ett","rftt"}) << endl;
    cout << getOrdering({"z","x"}) << endl;
    cout << getOrdering({"z","x","z"}) << endl;
    cout << getOrdering({"ab", "a"}) << endl;
}