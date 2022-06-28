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
		int temp = arr[i];
		j=i-1;
		while(j>=0 && arr[j]>temp){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=temp;
		for(int k=0;k<n;k++)
			cout << arr[k] << " ";
		cout << endl;
	}
	for(i=0;i<n;i++){
		cout << arr[i] << " ";
	}
}
