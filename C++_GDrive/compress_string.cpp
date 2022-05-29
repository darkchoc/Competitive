#include<bits/stdc++.h>

using namespace std;

void approach1(string str){
	str = str+"@";
	int i=0;
	int count=1;
	string ans = "";
	while(i<str.length()-1){
		while(i<str.length()-1 && str[i]==str[i+1]){
			count++;
			i++;
		}
		ans += str[i] + to_string(count);
		count=1;
		i++;
	}
	cout << ans << endl;
	return;
}

void approach2(string str){
	int count=1;
	string ans = "";
	int i=0;
	while(i<str.length()){
		while(i<str.length()-1 && str[i]==str[i+1]){
			count++;
			i++;
		}
		ans += str[i] + to_string(count);
		count=1;
		i++;
	}
	cout << ans << endl;
	return;
}

int main(){
	string str;
	cin >> str;
	approach1(str);
	approach2(str);
	return 0;
}
