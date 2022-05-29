#include <bits/stdc++.h>
#include "obj.h"
#include "myheader.h"

using namespace std;

int main(){
	A* ptr_a = new A();
	ptr_a->func();
	int* arr = Obj::get_ptr();
	vector<int>& vec_ = *arr; 
	for(int i=0; i<vec_.size(); i++)
		cout << vec_[i] << endl;
	return 0;
}
