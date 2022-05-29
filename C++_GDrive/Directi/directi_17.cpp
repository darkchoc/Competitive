/*
Array of 10000000 bits (initially 0).
N Flip operations given (start, end)
Break resulting array in groups of 4, convert to hexadecimal
Count freq of each hexa decimal and print.
https://www.careercup.com/question?id=5999996388245504
*/

#include <bits/stdc++.h>
using namespace std;
vector<int> arr (10000001, 0);
int main(){
	int n;
	cin >> n;
	int x, y;
	for(int i=0; i<n; i++){
		cin >> x >> y;
		arr[x]++;
		arr[y+1]--;
	}
	vector<int> freq(16, 0);
	int sum=0;
	for(int i=1; i<=10000000; i++){
		sum += arr[i];
		arr[i]=sum%2;
		if(i%4==0){
			int num = 1*arr[i] + 2*arr[i-1] + 4*arr[i-2] + 8*arr[i-3];
			freq[num]++;
		}
	}
	for(int i=0; i<16; i++)
		cout << freq[i] << " ";
	cout << endl;
	return 0;
}