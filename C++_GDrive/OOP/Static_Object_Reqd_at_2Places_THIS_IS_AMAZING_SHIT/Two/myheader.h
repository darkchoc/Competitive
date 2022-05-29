#ifndef MYHEADER_H_
#define MYHEADER_H_

#include <bits/stdc++.h>
#include "obj.h"

using namespace std;

class A{
public: 
	void func(){
		int * arr = Obj::get_ptr();
		if(arr==nullptr)
			cout << "Currently arr is set to nullptr\n";
		else
			cout << "arr is not null" << endl; 
		vector<int> vec_;
		vec_.resize(5);
		vec_[0]=1; vec_[1]=2; vec_[2]=3; vec_[3]=4; vec_[4]=5;
		arr = &vec_;
	}
};
#endif
