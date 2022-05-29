/*
Question: You are given n, X, y and Z. 
y is the buying price of stock, which remains constant.
n is the number of days.
X is the initial amount of money you have
Z is the minimum profit you need to make. 

You can only buy stocks for consecutive k days, within 1 to n days. And you must buy a stock everyday.
The selling price of the stock depends on which day you bought the stock. The selling price of ith day is given by V[i]
You cannot sell stocks before market is completely closed. (after day n)
You can only buy 1 stock per day

Therefore if you decide to buy stocks from day i to j, 1<=i<=j<=n, then you must satisfy the following conditions:
V[i] + V[i+1] + V[i+2] + ... V[j] - y*(j-i+1) >= Z
and y*(j-i+1) <= X

You don't have to maximize profit but achieve the profit by spending minimum number of days in the market.
Also, if two durations are equal, prefer one in which you enter the market later.

Return -1 if not possible

*/

#include <bits/stdc++.h>

using namespace std;

void findminPairs(long long *V, long long n, long long X, long long y, long long Z) {
	long long a=0, b=INT_MAX;
	long long r = INT_MAX;//=b-a;

	for(long long i=1;i<=n;i++) {
		long long int sum = 0;
		for(long long j=i;j<=n && (y*(j-i+1)<=X);j++) {
			sum += (long long int)V[j];
			if((sum-(y*(j-i+1)))>=Z) {
				if((j-i)<=r) {
					b=j;
					a=i;
					r=b-a;
				}
				break;
			}
			else if(sum-(y*(j-i+1))<=0){
				i=j; //basically we want to start from j+1 now, so +1 will be done by for loop
				break;
			}
		}
	}
	if(a==0) {
		cout<<-1<<endl;
	} else { 
    		cout<<a<<" "<<b<<endl;
	}
}

int main() {
	
	long long n, X, y, Z, T;
	cin>>T;
	for(long long t=0;t<T;t++) {
		cin>>n>>X>>y>>Z;
		long long *V=new long long[n+1];
		for(long long i=1;i<=n;i++) {
			cin>>V[i];
		}
		findminPairs(V, n, X, y, Z);
	}

	return 0;
}