#ifndef MYHEADER_H_
#define MYHEADER_H_

#include <bits/stdc++.h>
#include "obj.h"

using namespace std;

class A{
public: 
	void func(){
		vector<int> * vec = Obj::get_ptr();
		if(vec==nullptr)
			cout << "Currently ptr is set to nullptr\n";
		else
			cout << "vec is not null" << endl; 
		vector<int>& vec_ = *vec; // & is put so that the original vector is not copied and vec_ is only a reference to it. 
		// vector<int> vec_ = *vec; //this won't work as then all changes will be happening in this local variable and not original static vector.

  		// vector<int>& vec_ = *(Obj::get_ptr()); //this would also work 
		vec_.resize(5);
		vec_[0]=1; vec_[1]=2; vec_[2]=3; vec_[3]=4; vec_[4]=5;
		if(vec==nullptr)
			cout << "still set to nullptr\n";
	}
};
#endif
