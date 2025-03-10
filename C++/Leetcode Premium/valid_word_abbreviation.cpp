/*
Description
A string can be abbreviated by replacing any number of non-adjacent, non-empty substrings with their lengths. The lengths should not have leading zeros.

For example, a string such as "substitution" could be abbreviated as (but not limited to):

"s10n" ("s ubstitutio n")
"sub4u4" ("sub stit u tion")
"12" ("substitution")
"su3i1u2on" ("su bst i t u ti on")
"substitution" (no substrings replaced)
The following are not valid abbreviations:

"s55n" ("s ubsti tutio n", the replaced substrings are adjacent)
"s010n" (has leading zeros)
"s0ubstitution" (replaces an empty substring)
Given a string word and an abbreviation abbr, return whether the string matches the given abbreviation.

A substring is a contiguous non-empty sequence of characters within a string.

 

Example 1:

Input: word = "internationalization", abbr = "i12iz4n"
Output: true
Explanation: The word "internationalization" can be abbreviated as "i12iz4n" ("i nternational iz atio n").
Example 2:

Input: word = "apple", abbr = "a2e"
Output: false
Explanation: The word "apple" cannot be abbreviated as "a2e".
 

Constraints:

1 <= word.length <= 20
word consists of only lowercase English letters.
1 <= abbr.length <= 10
abbr consists of lowercase English letters and digits.
All the integers in abbr will fit in a 32-bit integer.
*/

#include <iostream>
using namespace std;

/*
Thoughts: Start iterating on both abbreviation and string s. If abb[i] is a letter, compare abb[i] with s[j] and if they are not same, return false.
If abb[i] is number (basically start of a new number sequence), then if abb[i] = 0, then we can simply return false, as neither can we have 
leading zeros, nor can there be a case of "0" in the abbreviation

So once we come a start of a valid number sequence, parse to form the number, also make sure we aren't overflowing. We can also simply check that if 
number is becoming greater than 20, then return false as constraints mention length of word is 20.

Once number parsed, move j (pointer in s) forward by that much and move i by 1. 

At the end of while loop, if both i and j are at the end of the strings, return true, else return false.

*/
bool solve(string abb, string s) {
    int i = 0, j = 0;
    while(i < abb.length() && j < s.length()){
        if(abb[i]>='1' && abb[i]<='9') {
            int num = 0;
            while(i < abb.length() && abb[i]>='0' && abb[i]<='9'){
                num = num*10 + (abb[i]-'0');
                if(num>20) return false; // as constraints mention that max length of word can be 20.
                i++;
            }
            // now i points to a letter, or is at abb.length().
            // move j forward by that much
            j += num;
        } else { // abb[i] is either a letter or '0'
            if(abb[i]==s[j]){ // in case abb[i]=='0', this wouldn't ever satisfy. So we'll return false from below else.
                i++;
                j++;
            } else {
                return false;
            }
        }
    }
    return i==abb.length() && j==s.length();
}

int main() {
    cout << solve("s10n", "substitution") << endl; // 1
    cout << solve("sub4u4", "substitution") << endl; // 1
    cout << solve("12", "substitution") << endl; // 1
    cout << solve("su3i1u2on", "substitution") << endl; // 1
    cout << solve("s55n", "substitution") << endl; // 0
    cout << solve("s010n", "substitution") << endl; // 0 - has leading 0
    cout << solve("s0ubstitution", "substitution") << endl; // 0 - replaces empty string
    cout << solve("i12iz4n", "internationalization") << endl; // 1 
    cout << solve("a2e", "apple") << endl; // 0 - replaces empty string
}

