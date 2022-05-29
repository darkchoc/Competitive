#include <bits/stdc++.h>

using namespace std;

struct abc{
	int pt;
	char c;
	bool operator <(const struct abc * abc_obj) const{
		return pt < abc_obj.pt;
	}
//	bool operator >(const abc * abc_obj) const{
//		return pt > abc_obj.pt;
//	}
};

int main(){
	struct abc arr[10];
	arr[0].pt=3;
	arr[1].pt=6;
	arr[2].pt=1;
        arr[3].pt=4;        
        arr[4].pt=3;
        arr[5].pt=7;
        arr[6].pt=8;
        arr[7].pt=5;
        arr[8].pt=2;
        arr[9].pt=9;

    	arr[0].c='x';
        arr[1].c='n';
        arr[2].c='v';
        arr[3].c='d';
        arr[4].c='s';
        arr[5].c='e';
        arr[6].c='g';
        arr[7].c='r';
        arr[8].c='j';
        arr[9].c='a';
	
	for(int i=0; i<10; i++)
		cout << arr[i].pt << " " ;
	cout << endl;
	for(int i=0; i<10; i++)
		cout << arr[i].c << " " ;
	cout << endl << endl;
	
	sort(arr, arr+10);
	for(int i=0; i<10; i++)
		cout << arr[i].pt <<" " ;
	cout << endl;
	for(int i=0; i<10; i++)
		cout << arr[i].c << " " ;
	cout << endl;
return 0;
	

}
