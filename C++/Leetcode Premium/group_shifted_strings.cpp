/*
https://leetcode.ca/2016-08-05-249-Group-Shifted-Strings/

Description
We can shift a string by shifting each of its letters to its successive letter.

For example, "abc" can be shifted to be "bcd".
We can keep shifting the string to form a sequence.

For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
Given an array of strings strings, group all strings[i] that belong to the same shifting sequence. You may return the answer in any order.

 

Example 1:

Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
Example 2:

Input: strings = ["a"]
Output: [["a"]]
 

Constraints:

1 <= strings.length <= 200
1 <= strings[i].length <= 50
strings[i] consists of lowercase English letters.
*/


/*
Thoughts:
We should try to bring each string to it's base form. For example, "def" can be reduced to "abc". 
Similarly, "bfd" can be reduced to "aec". 

What about "dab" ? It's base form would be: "axy". How do we reach here though? 

The shift can be simply calculated by subtracting 'a' from first character of string. So for example, in above case, shift is 'd'-'a' = 3.
Now we need to subtract 3 from all other characters, but ensure that they wrap around.
If a to z is mapped to 0...25, then when we need to subtract 3, we can do: (x-3+26)%26 ? In case when (x-3) > 0, it will simply be (x-3), and in case when
(x-3 < 0), the +26 will bring it to something < 26. So for example, when subtracting 3 from 'a', we do: (0-3+26)%26 = 23, which maps to letter 'x'. 
*/

#include <iostream>
using namespace std;

string getBaseString(string &s) {
    int diff = s[0]-'a';
    // we need to subtract diff from each character now
    string baseString = "";
    for(int i=0; i<s.length(); i++){
        char c = ((s[i]-'a') - diff + 26)%26 + 'a'; // the subtraction and additon of 'a' is to map a to 0, and then 0 to a (similarly for other chars).
        baseString.push_back(c);
    }
    return baseString;
}

void groupNestedStrings(vector<string> words) {
    unordered_map<string, vector<string> > baseStringToActualStringsMap;
    for(int i=0; i<words.size(); i++){
        string baseString = getBaseString(words[i]);
        baseStringToActualStringsMap[baseString].push_back(words[i]);
    }
    vector<vector<string> > ans;
    for(unordered_map<string, vector<string>>::iterator it=baseStringToActualStringsMap.begin(); it!=baseStringToActualStringsMap.end(); it++) {
        ans.push_back(it->second);
    }
    // return ans;
    for(int i=0; i<ans.size(); i++){
        cout << "[";
        for(int j=0; j<ans[i].size(); j++){
            cout << ans[i][j];
            if(j!=ans[i].size()-1)
                cout << ", ";
        }
        cout << "]";
        if(i!=ans.size()-1)
            cout << ", ";
    }
    cout << endl;
}

int main() {
    groupNestedStrings({"abc","bcd","acef","xyz","az","ba","a","z"}); // [acef], [abc, bcd, xyz], [az, ba], [a, z]
    groupNestedStrings({"a"}); // [a]
    groupNestedStrings({"dab", "byz", "j", "r", "x", "z"}); // [dab, byz], [j, r, x, z]
}