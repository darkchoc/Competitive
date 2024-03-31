/*
https://leetcode.com/discuss/interview-question/341992/Sigma-Computing-or-Online-Assessment-2019

Given a list of strings that may represent valid latitude/longitude pairs, test for validity. Print a string, either "Valid" or "Invalid" representing your results for each test.

A string (X,Y) is considered valid if the following criteria are met.
- The string starts with a (, has a comma after X and ends with a ).
- There is no space between opening parenthesis and first character of X
- There is no space between comma and last character of X
- There is one space between comma and first character of Y
- There is no space between last character of Y and closing parenthesis
- X and Y are decimal numbers and may be preceded by a sign.
- There are no leading zeros.
- No other characters are allowed in X and Y
- -90 <= X <= 90 and -180 <= Y <= 180

Example:
Input           Output          Reason
(90, 180)       Valid
(+90, +180)     Valid
 (90, 180)      Invalid         Extra space in beginning
(90.0, 180.1)   Invalid         Out of range
(85S, 95W)      Invalid         Invalid characters
*/

#include <bits/stdc++.h>
using namespace std;

bool isNumValid(string num, int lower, int upper){
    if(num.length()==0) return false;
    bool isNegative = false;
    int i = 0;
    if(num[0]=='-'){ 
        isNegative = true;
        i++;
    }
    if(num[0]=='+') i++;
    int j = i;
    int countDecimals = 0, decimalIndex = -1, firstNonZero = -1;
    while(j < num.length()){
        if(num[j]=='.'){
            countDecimals++;
            if(countDecimals > 1) return false;
            decimalIndex = j;
        } else if(num[j] < '0' || num[j] > '9'){
            return false;
        } else if(num[i]!='0'){
            if(firstNonZero==-1)
                firstNonZero = i;
        }
        j++;
    }
    if(firstNonZero!=-1){
        // see if two or more zeros before decimal
        if(countDecimals==1){
            if(decimalIndex < firstNonZero && decimalIndex >= i+2) return false; // +00.01
            else if(decimalIndex > firstNonZero && firstNonZero > i) return false; // +01.01
        } else {
            if (firstNonZero > i) return false; // +00189
        }
    } else {
        if(countDecimals==1){
            if(decimalIndex > i+1) return false; // +00.0 or 00.0. Valid case would be: +0.000 or 0.000 or +.00
        } else {
            if(i!=num.length()-1) return false; // 000 or 00. Valid case is just 0
        }
    }
    int n = 0;
    while(i < num.length()){
        if(num[i]=='.'){
            // just check if number formed till now is right at boundry (say 180) and if the decimal part is non zero then it is out of range else no need to actually construct the number
            if(n==upper){
                i++;
                while(i < num.length()){
                    if(num[i]!='0') return false;
                    i++;
                }
                return true;
            } else return true;
        } else {
            n = n*10 + (num[i]-'0');
        }
        if(n > upper) return false;
        i++;
    }
    return true;
} 

string isValid(string input){
    if(input.length() < 6) return "Invalid";
    if(input[0]!='(' || input[input.length()-1]!=')') return "Invalid";
    string x = "";
    string y = "";
    int i=1;
    while(i<input.length() && input[i]!=',')
        x += input[i++];
    if(i>=input.length()-3) return "Invalid"; // we would need at least 3 characters after , for it to be valid.
    if(input[i+1]!=' ') return "Invalid";
    i+=2; // now i should point to first character of y.
    while(i<input.length() && input[i]!=')')
        y += input[i++];
    if(i!=input.length()-1) return "Invalid"; // now i should have been at )
    return (isNumValid(x, -90, 90) && isNumValid(y, -180, +180))?"Valid":"Invalid";
}

int main(){
    cout << isValid("(90, 180)") << endl; // Valid
    cout << isValid("(+90, +180)") << endl; // Valid
    cout << isValid(" (90, 180)") << endl; // Invalid
    cout << isValid("(90.0, 180.1)") << endl; // Invalid
    cout << isValid("(85S, 95W)") << endl; // Invalid
    cout << isValid("(0.0, +0.0)") << endl; // Valid
    cout << isValid("(00.0, -000.0)") << endl; // Invalid
    cout << isValid("(0, 0.0)") << endl; // Valid
}