#include<bits/stdc++.h>

using namespace std;

void fillprimes(vector<int> &primes) {
	vector<bool> nums(100000, true);
	nums[0]=false; 
	nums[1]=false;
	for(int i=2; i<=sqrt(100000); i++){
		if(nums[i]==true){
			for(int j=i*i; j<100000; j+=i){
				nums[j]=false;
			}
			primes.push_back(i);
		}
	}
	return;
}

int main(){
	vector<int> primes;
	fillprimes(primes);
	int t;
	cin >> t;
	for(int test = 0; test<t; test++){
		int total, prime;
		cin >> total >> prime;
		int max_multiplicators = 0;
		for(int i=0; i<primes.size() && total>1; i++){
			while(total%primes[i]==0){
				max_multiplicators++;
				total = total/primes[i];
			}
		}
		if(max_multiplicators>=prime)
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}