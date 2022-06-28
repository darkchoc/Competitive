#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	int arr[n];
	int i;
	for(i=0;i<n;i++){
		cin >> arr[i]; 
	}
	int j;
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(arr[j] > arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}

	for(i=0;i<n;i++){
		cout << arr[i] << " ";	
	}
}
