#include <bits/stdc++.h>

using namespace std;

void merge(int *arr, int start, int mid, int end){ //will create a temporary array to fill sorted numbers, and then copy back in the original array
	if(start == end)
		return;
	int temp[end - start + 1];
	int filler = 0;
	int left = start;
	int right = mid+1;
	while(left <= mid && right <= end){
		temp[filler++] = arr[left] < arr[right] ? arr[left++] : arr[right++];
	}
	
	// only one of the following while loops will execute
	while(left<=mid)
		temp[filler++] = arr[left++];
	while(right<=end)
		temp[filler++] = arr[right++];
	
	//copy elements from temp to original array
	//just overly brainy implementation to not introduce another variable and for loop for copying. Do simply when need be.
	while(filler--)
		arr[end - filler] = temp[end - filler - start];
	return;
}

void merge_sort(int *arr, int start, int end){
	if (start < end){
		int mid = (start + end)/2;
		merge_sort(arr, start, mid);
		merge_sort(arr, mid+1, end);
		merge(arr, start, mid, end); // passing mid to tell where the array was divided into two
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	int arr[n];
	int i = 0;
	for( i=0 ; i<n ; i++){
		cin >> arr[i];
	}
	merge_sort(arr, 0, n-1);
	for( i=0; i<n ; i++)
		cout << arr[i] << " " ;
}
