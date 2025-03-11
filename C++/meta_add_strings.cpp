/*
https://leetcode.com/discuss/post/6518222/meta-variant-for-add-strings-lc415-by-co-33kj/

// Add strings. The numbers can have decimal part.

*/



#include <iostream>
using namespace std;

void getIntegerAndDecimal(string &a, string &aInt, string &aDecimal){
    int i = 0;
    // skip leading 0s in integer part
    while(i < a.length() && a[i]=='0')
        i++;
    // get integer part
    while(i < a.length() && a[i]!='.'){
        aInt.push_back(a[i]);
        i++;
    }
    // i is at '.' or i = a.length()
    i++; // increment i nonetheless. We won't enter while loop if i >= a.length()
    while(i < a.length()){
        aDecimal.push_back(a[i]);
        i++;
    }
    // trim trailing zeros from decimal part
    int j = aDecimal.length()-1;
    while(j >= 0 && aDecimal[j]=='0'){
        aDecimal.pop_back();
        j--;
    }
    // instead of keeping strings as empty, set them to 0
    if(aInt=="") aInt = "0";
    if(aDecimal=="") aDecimal = "0";
    return;
}

string addStrings(string a, string b){
    string aInt="", aDecimal="", bInt="", bDecimal="";
    getIntegerAndDecimal(a, aInt, aDecimal);
    getIntegerAndDecimal(b, bInt, bDecimal);
    // add decimals first
    int sum = 0, carry = 0;
    int i=aDecimal.length()-1, j = bDecimal.length()-1; // aDecimal.length and bDecimal.length will be at least 1 since we are setting them to "0" in case 
    // they are not there.
    string decimalSum="";
    while(i>=0 || j>=0) { // NOTICE how we have || condition here. 
        if(i > j) { // aDecimal = 00345 , bDecimal = 01, so for "345", i would be greater than j
            sum = (aDecimal[i]-'0');
            i--;
        } else if(j > i) { // reverse of above
            sum = (bDecimal[j]-'0');
            j--;
        } else { // i==j
            sum = (aDecimal[i]-'0') + (bDecimal[j]-'0') + carry;
            i--;
            j--;
        }
        decimalSum.push_back((sum%10 + '0'));
        carry = sum/10;
    }
    // decimals are added, just reverse the string and remove trailing zeros
    reverse(decimalSum.begin(), decimalSum.end());
    int k = decimalSum.length()-1;
    while(k>=0 && decimalSum[k]=='0'){
        decimalSum.pop_back();
        k--;
    }

    // carry from decimalSum may still be there. Add this carry to integer sum
    i = aInt.length()-1;
    j = bInt.length()-1;
    string intSum = "";
    while(i>=0 && j>=0) { // HERE we are doing &&
        sum = (aInt[i]-'0') + (bInt[j]-'0') + carry;
        intSum.push_back((sum%10 + '0'));
        carry = sum/10;
        i--;
        j--;
    }
    // i or j may not be 0. Only one would be non zero
    while(i >= 0) {
        sum = (aInt[i]-'0') + carry;
        intSum.push_back((sum%10 + '0'));
        carry = sum/10;
        i--;
    }
    while(j >= 0) {
        sum = (bInt[j]-'0') + carry;
        intSum.push_back((sum%10 + '0'));
        carry = sum/10;
        j--;
    }
    if(carry) // will be single digit at most
        intSum.push_back('0'+carry);
    reverse(intSum.begin(), intSum.end());
    // now we have intSum and decimalSum
    string finalAns = intSum;
    if(decimalSum.length()) { // had decimalSum been 0, while removing trailing zeros it would have gone down to "".
        finalAns.push_back('.');
        finalAns = finalAns + decimalSum;
    }
    return finalAns;
}


int main(){
    cout << addStrings("123", "0") << endl; // 123
    cout << addStrings("10.5", "0") << endl; // 10.5
    cout << addStrings("0", "0.05") << endl; // 0.05
    cout << addStrings("12", "233") << endl; // 245
    cout << addStrings("13.04", "20.00") << endl; // 33.04
    cout << addStrings(".7", ".8") << endl; // 1.5
    cout << addStrings("9.6", "2.400") << endl; // 12
    cout << addStrings("3.2", "4.") << endl; // 7.2
    cout << addStrings("14.0000", ".094") << endl; // 14.094
    cout << addStrings("3.0", "2.0") << endl; // 5
    cout << addStrings("3.5", "2") << endl; // 5.5
    cout << addStrings(".5", "2") << endl; // 2.5
    cout << addStrings("0.0", "0") << endl; // 0
    cout << addStrings("2.5", "000.00500") << endl; // 2.505
    cout << addStrings("2.99", "9.09") << endl; // 12.08
    cout << addStrings("0.00056004", "0.00023006") << endl; // 0.0007901
    cout << addStrings("000.000", "0000.") << endl; // 0
}