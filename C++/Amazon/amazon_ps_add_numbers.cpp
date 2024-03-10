/*
https://leetcode.com/discuss/interview-question/4794826/Amazon-Phone-Screen

Problem Statement: Write a function that adds two decimal numbers that can be arbitrarily large.

Assumptions discussed:
    1. The numbers are given as strings. (Discussed why linked-list or any other data structure will not be a good idea.)
    2. Both the numbers will have a decimal point. (Even if there were none or atleast one, it will be a couple of checks that I discussed with the interviewer verbally)
    3. Both the numbers will be strictly positive. (Discussed what will happen if there were negatives or positives)

Approach: While the assumptions do make things easier, I'll try to implement in a way that allows positive and negative numbers, as well as numbers which may or may not have decimal point.
*/

#include <bits/stdc++.h>
using namespace std;

string removeTrailing0s(string num, int startIndex){
    int i = num.length()-1;
    while(i >= startIndex && num[i]=='0') i--;
    if(i<startIndex) return "";
    else return num.substr(startIndex, i-startIndex+1);
}

pair<string, string> preProcess(string num){
    int i=0;
    // skip sign and leading 0s
    while(i < num.length() && num[i]!='.' && (num[i]<'1' || num[i] > '9')) 
        i++;
    if(i == num.length()) 
        return make_pair("", "");
    // now i either pointing to . or first digit.
    if(num[i]=='.') {
        return make_pair("", removeTrailing0s(num, i+1));
    } else {
        int integerStartIndex = i;
        while(i < num.length() && num[i]!='.') 
            i++;
        string integerPart = num.substr(integerStartIndex, i-integerStartIndex);
        if(i==num.length())
            return make_pair(integerPart, "");
        else
            return make_pair(integerPart, removeTrailing0s(num, i+1)); 
    }    
}

string addIntegers(string num1, string num2, int carry){
    int i = num1.length()-1, j = num2.length()-1;
    string ans = "";
    int sum = 0;
    while(i >= 0 || j >= 0){
        int d1 = (i >= 0)?num1[i]-'0':0;
        int d2 = (j >= 0)?num2[j]-'0':0;
        sum = (d1 + d2 + carry);
        ans += to_string(sum%10);
        carry = sum/10;
        i--;
        j--;
    }
    reverse(ans.begin(), ans.end());
    if(carry)
        ans = to_string(carry) + ans;
    return ans;
}

pair<string, int> addDecimals(string num1, string num2){
    string ans = "";
    int i = max(num1.length(), num2.length()) - 1;
    int sum = 0, carry = 0;
    bool gotNonZero = false;
    while(i>=0){
        int d1 = (i < num1.length())?num1[i]-'0':0;
        int d2 = (i < num2.length())?num2[i]-'0':0;
        sum = d1 + d2 + carry;
        if(sum%10)
            gotNonZero = true;
        if(gotNonZero)
            ans += to_string(sum%10);
        carry = sum/10;
        i--;
    }
    reverse(ans.begin(), ans.end());
    return make_pair(ans, carry);
}

string addNums(string num1, string num2){
    /* Based on examples I created below, I can think of following steps:
    1. Remove leading 0s. Leading 0s maybe after the sign.
    2. Remove trailing 0s if there is a decimal point
    3. If final answer doesn't have decimal part, then just return integer part
    */

    bool num1Positive = false, num2Positive = false;
    if(num1[0]!='-') num1Positive=true;
    if(num2[0]!='-') num2Positive=true;
    pair<string, string> num1Processed = preProcess(num1);
    pair<string, string> num2Processed = preProcess(num2);
    if(num1Processed.first.length() == 0 && num1Processed.second.length()==0 && num2Processed.first.length()==0 && num2Processed.second.length()==0) 
        return "0";
    if(num1Positive == num2Positive){
        // in this case, simply add.
        pair<string, int> decimalAdd = addDecimals(num1Processed.second, num2Processed.second);
        string integerAdd = addIntegers(num1Processed.first, num2Processed.first, decimalAdd.second);
        string finalAns = "";
        if(num1Positive==false) finalAns += "-";
        if(integerAdd.length() > 0) 
            finalAns += integerAdd;
        else {
            // decimal part must be of non-zero length as both nums have same sign and we have already handled case where both nums are 0.
            finalAns += "0." + decimalAdd.first;
            return finalAns;
        }
        if(decimalAdd.first.length() > 0)
            finalAns += "." + decimalAdd.first;
        return finalAns;
    } else {
        // TODO: IMPLEMENT SUBTRACTION
        return "-1";
    }
}

int main(){
    cout << addNums("123", "455") << endl; // 578
    cout << addNums("10.6", "14.4503") << endl; // 25.0503
    cout << addNums("10.23000", "5.1") << endl; // 15.33
    cout << addNums("-14", "5") << endl; // -9
    cout << addNums("5.5", "4.500") << endl; // 10
    cout << addNums("00034.2", "03") << endl; // 37.2
    cout << addNums("-5.6", "-4.4") << endl; // -10
    cout << addNums("-003.4", "+007") << endl; // 3.6
    cout << addNums("0.54", "-0.2") << endl; // 0.34
    cout << addNums("0.44", "-000.54") << endl; // -0.1
    cout << addNums("0000", "00") << endl; // 0
    cout << addNums("+000", "-000") << endl; // 0
}