#include <bits/stdc++.h>

using namespace std;

int partition( int *arr, int start, int end){
	int divider = arr[end];
	int larger = start;  //larger is the index of number larger than divider, (not the larger index)
	for(int i=start; i<end; i++){
		if (arr[i] < divider){
			int temp = arr[i];
			arr[i] = arr[larger];
			arr[larger] = temp;
			larger++;
		}
	}
	int temp = arr[larger];
	arr[larger] = arr[end];
	arr[end] = temp;
	return larger;

}

void quick_sort(int *arr, int start, int end){
	if (start < end ){
		int p_index = partition(arr, start, end);
		quick_sort(arr, start, p_index-1);
		quick_sort(arr, p_index+1, end);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	int arr[n];
	int i=0;
	for( i=0; i<n; i++){
		cin >> arr[i];
	}
	quick_sort(arr, 0, n-1);
	for( i=0; i<n; i++){
		cout << arr[i] << " ";
	}
}
