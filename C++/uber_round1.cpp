#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
A jump means adding or subtracting 1.
“Converge” means all the elements get to the same value.
Given an integer array, find if all the elements could converge with 1 jump (or less) and return the converge value.

input elements could be numbers between 0 and 9 inclusive
9 plus 1, gives you 0
0 minus 1, gives you 9

EXAMPLE
Input: 
 [ 1, 0, 9, 9, 1, 1, 0 ] 

Output: 0
*/

int converge(vector<int> &arr){
  vector<bool> present (10);
  int n = arr.size();
  for(int i=0; i<n; i++)
    present[arr[i]]=true;
  vector<int> uniqueValues;
  for(int i=0; i<10; i++)
    if(present[i])
      uniqueValues.push_back(i);
  if(uniqueValues.size()==1)
    return uniqueValues[0];
  if(uniqueValues.size() > 3)
    return -1;
  if(uniqueValues.size()==2){
      if(uniqueValues[1]-uniqueValues[0] < 3)
        return (uniqueValues[0] + uniqueValues[1])/2;
      if(uniqueValues[0]==0 && (uniqueValues[1]==8 || uniqueValues[1]==9))
        return (uniqueValues[1] + 1)%10;
      if(uniqueValues[0]==1 && uniqueValues[1]==9)
        return 0;
      return -1;
  }
  if(uniqueValues.size()==3){
    if(uniqueValues[0]==uniqueValues[1]-1 && uniqueValues[1]==uniqueValues[2]-1)
      return uniqueValues[1];
    if(uniqueValues[0]==0 && uniqueValues[2]==9){
      if(uniqueValues[1]==1)
        return 0;
      if(uniqueValues[1]==8)
        return 9;
      return -1;
    }
  }
  //if > 3 values present, then false
  //if 3 values present -> (0,8,9), (0,1,9), (x, x+1, x+2) -> true
  // (9,0,1) (7,8,9) (8,9,0). => 9 
  //if 2 values present -> if diff <= 2 || values are (8,0),(0,9),(1,9) -> then true
  //if 1 value present -> true
}

int converge2(vector<int> &arr, int n){
  int ele1 = -1;
  int ele2 = -1;
  int ele3 = -1;
  int max_=arr[0], min_=arr[0];
  for(int i=0; i<arr.size(); i++){
    max_ = max(max_, arr[i]);
    min_ = min(min_, arr[i]);
  }
  if(max_ == min_)
    return max_; //1 value present
  int possibleAnswer;
  //if diff between max_ and min_ > 2 -> then possible answer -> min_, max_, 0
      // if min_ != 0 -> ans = 0? 
      // else max_ or min_? 
  //else (min_ + max_)/2
  
}

int main() {
  vector<int> arr = {1, 0, 9, 9, 1, 1, 0}; //0
  cout << converge(arr) << endl;
  arr = {1,4,2,0,3}; //-1
  cout << converge(arr) << endl;
  arr = {0,9,8,0,0,8}; //9
  cout << converge(arr) << endl;
  arr = {9,7,8,9}; //8
  cout << converge(arr) << endl;
  arr = {0,0,8,0}; //9
  cout << converge(arr) << endl;
  arr = {9,9,0,9}; //0
  cout << converge(arr) << endl;
  arr = {9,1,9,9,1}; //0
  cout << converge(arr) << endl;
  arr = {3,3,3,3}; //3
  cout << converge(arr) << endl;
  arr = {3,4,3,4,3}; //3
  cout << converge(arr) << endl;
  arr = {6,8,6,6,8}; //7
  cout << converge(arr) << endl;
  return 0;
}
