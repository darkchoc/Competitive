#include <bits/stdc++.h>

using namespace std;

int main(){
	vector<char> types;
	types.push_back('A');
	types.push_back('B');
	types.push_back('C');
	string str = "";
	for(int i=0; i<types.size(); i++){
		str += types[i];
		if(i!=types.size()-1)
			str+=",";
	}
	cout << str << endl;
	return 0;
}
