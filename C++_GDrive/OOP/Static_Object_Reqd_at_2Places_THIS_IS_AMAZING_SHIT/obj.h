#ifndef OBJ_H_
#define OBJ_H_

#include <bits/stdc++.h>

using namespace std;

class Obj{
protected:
	static vector<int> ptr; 
public:
	static vector<int>* get_ptr(){
		return &ptr;
	}
};

vector<int> Obj::ptr;

#endif
