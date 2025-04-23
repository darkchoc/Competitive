/*There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

Example 1:

Input:
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]

Output: "wertf"
Example 2:

Input:
[
  "z",
  "x"
]

Output: "zx"
Example 3:

Input:
[
  "z",
  "x",
  "z"
]

Output: "" 

Explanation: The order is invalid, so return "".
Note:

You may assume all letters are in lowercase.
You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.
*/

/*
Thoughts. Compare ith word with i+1 th word. See where they differ for the first time. Create an edge
from character in i to character in i+1

Now, once graph is ready, if there is a cycle in the graph, return empty string, otherwise keep appending
the characters once the subtree within it has been visited. Reverse the string thus formed, and return.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool dfsCycleFound(vector<vector<int> > &graph, vector<int> &visited, int i, string &dictionary) {
  visited[i]=1;
  for(int j=0; j<graph[i].size(); j++){
    if(visited[graph[i][j]]==0){
      if(dfsCycleFound(graph, visited, graph[i][j], dictionary)) return true;
      // basically if cycle found somewhere in dfs, return true from here also
    } else if(visited[graph[i][j]]==1){
      // cycle, so return true
      return true;
    } else {
      // it's 2, so continue
      continue;
    }
  }
  visited[i]=2;
  dictionary.push_back(i+'a');
  return false; // no cycle found, so return false and add word to dictionary
}

string getOrdering(vector<string> words){
  // construct graph. Map letters to integers
  vector<vector<int> > graph (26);
  for(int i=1; i<words.size(); i++){
    int j = 0;
    for(j=0; j<words[i].length() && j<words[i-1].length(); j++){
      if(words[i-1][j]!=words[i][j]) {
        graph[words[i-1][j]-'a'].push_back(words[i][j]-'a');
        break;
      }
    }
    if(j==words[i].length()) return ""; // this means words[i] and words[i-1] were same initially, 
    // but words[i-1] was longer. Example "ab", followed by "a". This is clearly wrong.
  }

  // check which letters are even present in words present in words array
  vector<bool> presentInWords (26, false);
  for(int i=0; i<words.size(); i++)
    for(int j=0; j<words[i].length(); j++)
      presentInWords[words[i][j]-'a']=true;

  // start dfs
  string dictionary = "";
  vector<int> visited(26, 0); // 0 means undiscovered, 1 means in progress, 2 means completed discovery
  for(int i=0; i<26; i++){
    if(visited[i]==0 && presentInWords[i]==true){
      if(dfsCycleFound(graph, visited, i, dictionary)) return "";
    }
  }
  reverse(dictionary.begin(), dictionary.end());
  return dictionary;
}

int main() {
  cout << getOrdering({"wrt","wrf","er","ett","rftt"}) << endl;
  cout << getOrdering({"z","x"}) << endl;
  cout << getOrdering({"z","x","z"}) << endl;
  cout << getOrdering({"ab", "a"}) << endl;
}