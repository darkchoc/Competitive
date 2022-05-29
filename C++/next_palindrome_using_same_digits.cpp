/*
Question: https://leetcode.ca/2021-07-03-1842-Next-Palindrome-Using-Same-Digits/
Given a very large palindrome string consisting of only digits, find the next largest palindrome using the same digits.
*/

#include <bits/stdc++.h>
using namespace std;

/*
Approach: consider first half of palindrome (excluding middle element if odd length palindrome)
From the end, see first point where s[i] > s[i-1]. Swap these. Sort all elements towards the right of i.
Replicate string to get palindrome (keep middle element between replicas if odd length palindrome).

THIS APPROACH IS WRONG. Consider: 1254334521
My current approach will generate: 1523443251
Correct answer should be: 1324554231

My appraoch is wrong because I'm just swapping i and i+1 whenever s[i] < s[i+1]. But actually, we should swap i with j (j>i), such that s[j] is the just greater element to s[i]. 
Basically, we are generating the next permutation of the first half of the string and then making a palindrome.
*/

string nextPalindromeWrong(string s){
    string middle = "";
    if(s.length()%2)
        middle = s[s.length()/2];
    string firstHalf = s.substr(0, s.length()/2);
    int i=firstHalf.length()-1;
    while(i>0 && firstHalf[i] <= firstHalf[i-1])
        i--;
    if(i==0){
        //palindrome already greatest
        return "already greatest";
    }
    //swap i and i-1
    swap(firstHalf[i], firstHalf[i-1]);
    sort(firstHalf.begin()+i, firstHalf.end()); //important, sorting should include original firstHalf[i-1].
    //now replicate
    string secondHalf = firstHalf;
    reverse(secondHalf.begin(), secondHalf.end());
    return firstHalf + middle + secondHalf;
}

bool generateNextPermutation(string &s, int end){
    //we need to consider string from 0 to end-1
    int i = end-1;
    while(i>0 && s[i] <= s[i-1])
        i--;
    if(i==0)
        return false;
    //s[i] > s[i-1]
    int smallerElementAtIndex = i-1;
    //find element just greater than s[i-1]. Since s[i...end-1] is sorted in descending order, we can just iterate and find the first j where s[j]<=s[i]. Our index of interest will be j-1.
    int j = i;
    while(j<end && s[j] > s[smallerElementAtIndex])
        j++;
    j--;
    swap(s[smallerElementAtIndex], s[j]);
    //now we just need to reverse s[smallerElementAtIndex+1 ... end-1] as array again in descending order
    reverse(s.begin()+smallerElementAtIndex+1, s.begin()+end); //reverse from [start, end).
    return true;
}

string nextPalindromeCorrect(string s){
    bool possible = generateNextPermutation(s, s.length()/2);
    if(!possible)
        return "already greatest";
    int i=0, j=s.length()-1;
    while(i<j){
        s[j]=s[i];
        j--;
        i++;
    }
    return s;
}

int main(){
    cout << nextPalindromeWrong("432234") << " " << nextPalindromeCorrect("432234") << endl; //already greatest
    cout << nextPalindromeWrong("4321234") << " " << nextPalindromeCorrect("4321234") << endl; //already greatest
    cout << nextPalindromeWrong("125423324521") << " " << nextPalindromeCorrect("125423324521") << endl; //125432234521
    cout << nextPalindromeWrong("12542324521") << " " << nextPalindromeCorrect("12542324521") << endl; //14225352241 and not 15224342251
    cout << nextPalindromeWrong("1254213124521") << " " << nextPalindromeCorrect("1254213124521") << endl; //1412253522141 and not 1512243422151
    cout << nextPalindromeWrong("12654232100123245621") << " " << nextPalindromeCorrect("12654232100123245621") << endl; //12654301222210345621
    cout << nextPalindromeWrong("1254334521") << " " << nextPalindromeCorrect("1254334521") << endl; //1324554231 and not 1524334251
}

