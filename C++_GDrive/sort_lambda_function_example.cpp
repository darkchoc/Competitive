#include <bits/stdc++.h>
//#include <cstdlib>
//#include <algorithm>
//#include <cstdio>
//#include <iostream>

using namespace std;

struct score{
   int sc;
   int ind;
//   bool operator<(const score& rhs) const {sc < rhs.cs;}
};

int main(){
   struct score arr[5];
   arr[0].sc = 9, arr[1].sc = 4, arr[2].sc=6, arr[3].sc = 8, arr[4].sc = 1;
   arr[0].ind = 1, arr[1].ind=2, arr[2].ind=3, arr[3].ind=4, arr[4].ind=5;
   for(int i = 0 ; i < 5; i++)
	cout << arr[i].sc << " " << arr[i].ind << endl;

   cout << endl;
   sort(arr, arr+5, [](const auto& lhs, const auto& rhs){return lhs.sc < rhs.sc;});
   //sort(arr, arr+5, scorecompare);
   for(int i =0; i< 5; i++)
    	cout << arr[i].sc << " " << arr[i].ind << endl;
   string res = "get_ranks";
   if(res.substr(0,9) == "get_ranks")
	cout << "YO";
   return 0;
    

}
