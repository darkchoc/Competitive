#include <bits/stdc++.h>
using namespace std;

int func(int x){
	if(x<3)
		return x;
	int k = log2(x+1);
	int ans = (pow(2,k-1)*k);
	if(x==pow(2,k)-1)
		return ans;
	ans += x - pow(2,k) + 1;
	ans += func(x - pow(2,k));
	return ans;
}

int main(){
	int x;
	cin >> x;
	cout << func(x) << endl;
}
