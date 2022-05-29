#include <bits/stdc++.h>

using namespace std;


void func2(vector<vector<int> > *c){
	vector<vector<int> > &d = *c;
	for(int i = 0 ; i < d.size(); i++)
		d[i].resize(5);
	for(int i = 0; i<d.size(); i++)
		for(int j=0; j<d[i].size(); j++)
			d[i][j] = i+1+j+1;
	return;
}

void func(vector<vector<int> > *b){
	func2(b);
	return;
}

void func3(vector<vector<int> > *e){
	vector<vector<int> > &f = *e;
	for(int i =0 ; i<f.size(); i++)
		for(int j =0; j<f[i].size(); j++)
			f[i][j] = i+j+2;
	return;
}

int main(){
	ios_base::sync_with_stdio(false);
	vector<vector<int> > a;
	a.resize(5);
	func(&a);
	for(int i =0; i<a.size(); i++){
		for(int j=0; j<a[i].size(); j++)
			cout << a[i][j] << " " ;
		cout << endl;
	}
	cout << endl; 
        vector<vector<int> > b;
	b.resize(5, vector<int> (4));
	func3(&b);
	for(int i =0; i<b.size(); i++){
                for(int j=0; j<b[i].size(); j++)
                        cout << b[i][j] << " " ;
                cout << endl;
        }

return 0;
}
