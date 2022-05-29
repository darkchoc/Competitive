/*
Question: https://leetcode.com/discuss/interview-question/428711/Palantir-or-Shortest-substring-that-only-appears-in-that-string

Question: Given a list of strings, for each string, output the shortest substring that only appears in that string

Example:

Input: [ "palantir", "pelantors","cheapair", "cheapoair"]
output:{
	"palantir": "ti", # ti only appears in "palantir"
	"pelantors": "s", # s only appears in "pelantors"
	"cheapair": "pai" or "apa", # either substring only appears in "cheapair"
	"cheapoair": "po" or "oa" # either substring only appears in cheapoair
}
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    typedef struct Trie {
        Trie* child[26];
        set<int> substringOf;
    } Trie;

    Trie *root;

    void addToTrie(string s, int ind){
        Trie* temp = root;
        for(int i=0; i<s.length(); i++){
            if(temp->child[s[i]-'a']==NULL)
                temp->child[s[i]-'a'] = new Trie();
            temp = temp->child[s[i]-'a'];
            temp->substringOf.insert(ind); //insert for all nodes while traversing
        }
    }

    void addSubstringsToTrie(vector<string> &words){
        for(int i=0; i<words.size(); i++){
            for(int j=0; j<words[i].length(); j++){
                string s = words[i].substr(j); //palantir, alantir, lantir, antir, ntir, tir, ir, r
                addToTrie(s, i);
            }
        }
    }

    bool allIndicesHereHaveAnswer(set<int> &s, vector<string> &result){
        if(s.empty())
            return false; //root node
        for(auto it=s.begin(); it!=s.end(); it++){
            if(result[*it]=="")
                return false;
        }
        return true;
    }

    void applySmartBFS(vector<string> &result){
        queue<pair<Trie*, string> > q;
        q.push(make_pair(root, "")); 
        int foundAnswerFor = 0;
        while(!q.empty() && foundAnswerFor < result.size()){
            pair<Trie*, string> current = q.front();
            q.pop();
            if(current.first->substringOf.size()==1){
                if(result[*(current.first->substringOf.begin())] == ""){
                    result[*(current.first->substringOf.begin())] = current.second;
                    foundAnswerFor++;
                }
                continue;
            } else if(allIndicesHereHaveAnswer(current.first->substringOf, result)) {
                //TODO: Can make it better by storing bitmask of words for which substring found, and compare bitmask with that of result. This would work if number of words < 32.
                continue; //no point exploring this further
            } else {
                for(int i=0; i<26; i++){
                    if(current.first->child[i]!=NULL){
                        q.push(make_pair(current.first->child[i], current.second + (char)('a' + i)));
                    }
                }
            }
        }
        return;
    }

    void printSubstrings(vector<string> &results){
        for(int i=0; i<results.size(); i++)
            cout << results[i] << endl;
    }

public:
    Solution(){
        root = new Trie();
    }

    vector<string> getShortestUniqueSubstring(vector<string> &words){
        vector<string> result (words.size());
        addSubstringsToTrie(words);
        applySmartBFS(result);
        printSubstrings(result);
        return result;
    }

};


int main(){
    vector<string> words = {"palantir", "pelantors","cheapair", "cheapoair"};
    Solution *solution = new Solution();
    solution->getShortestUniqueSubstring(words);
}