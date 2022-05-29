#include <bits/stdc++.h>

using namespace std;

int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n;
		cin >> n;
		vector<int> x_Coords (n);
		vector<int> y_Coords (n);
		int x, y;
		for(int i=0; i<n; i++){
			cin >> x >> y;
			x_Coords[i] = (x+y);
			y_Coords[i] = (x-y);

		}
		sort(x_Coords.begin(), x_Coords.end());
		sort(y_Coords.begin(), y_Coords.end());
		long long int min_dist = 1000000000000;
		for(int i=0; i<n-1; i++){
			min_dist = min(min_dist, (long long int)x_Coords[i+1] - (long long int)x_Coords[i]);
			min_dist = min(min_dist, (long long int)y_Coords[i+1] - (long long int)y_Coords[i]);
		}
		cout << (double)min_dist/2.0 << endl;
	}
	return 0;
}