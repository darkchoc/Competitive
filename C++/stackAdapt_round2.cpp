/*
You are given a 0-indexed string text and another 0-indexed string pattern of length 2, both of which consist of only lowercase English letters.

You can add either pattern[0] or pattern[1] anywhere in text exactly once. Note that the character can be added even at the beginning or at the end of text.

Return the maximum number of times pattern can occur as a subsequence of the modified text.

A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters..

example:
Input: text = "abdcdbc", pattern = "ac"
Output: 4

// aabdcdbc
// abdcdbcc -> ccbdcdba

Approach: Best case would be to either add pattern[0] at start of string, or pattern[1] at end of string. After that just check how many times sequence occurs in these two cases.

*/

#include <bits/stdc++.h>
using namespace std;

int countSequence(string text, string pattern){
  int ans = 0;
  int countOfSecondChar = 0;
  for(int i=text.size()-1; i>=0; i--){
    if(text[i]==pattern[0])
      ans += countOfSecondChar;
    if(text[i]==pattern[1])
      countOfSecondChar++;
  }
  return ans;
}

int solve(string text, string pattern){
  string reversed = text;
  reverse(reversed.begin(), reversed.end());
  return max(countSequence(pattern[0] + text, pattern), countSequence(pattern[1] + reversed, pattern));
}

int main(){
  cout << solve("abdcdbc", "ac") << endl; // 4
  cout << solve("abcdefgg", "kl") << endl; // 0
  cout << solve("aaaa", "ba") << endl; // 4
  cout << solve("aaaa", "aa") << endl; // 10
}