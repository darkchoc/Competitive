#include <bits/stdc++.h>
#include "obj.h"
#include "myheader.h"

using namespace std;

int main(){
	A* ptr_a = new A();
	ptr_a->func();
	vector<int>** arr = Obj::get_ptr();
	if(arr == nullptr)
		cout << "arr is still a nullptr\n";
	vector<int>& vec_ = *(*arr); //Putting & so that vector is not copied but rather vec_ is only a reference to the original vector. 
	//vector<int> vec_ = *(*arr); //this would also work but here the original vector is copied in vec_
	cout << "size of vec_ is " << vec_.size() << endl; 
	for(int i=0; i<vec_.size(); i++)
		cout << vec_[i] << endl;
	return 0;
}
