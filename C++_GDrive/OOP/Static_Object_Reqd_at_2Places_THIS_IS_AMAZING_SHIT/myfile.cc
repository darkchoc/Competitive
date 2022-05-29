#include <bits/stdc++.h>
#include "obj.h"
#include "myheader.h"

using namespace std;

int main(){
	A* ptr_a = new A();
	ptr_a->func();
	vector<int>* arr = Obj::get_ptr();
	vector<int>& vec_ = *arr; // & put to get a refernce to original vector instead of copying it altogether.
	// vector<int> vec_ = *arr ; // Here this would also work since we only need to read/print values, and not update them. In this case, the original vector is copied into this local vec_ vector. 
	for(int i=0; i<vec_.size(); i++)
		cout << vec_[i] << endl;
	return 0;
}
