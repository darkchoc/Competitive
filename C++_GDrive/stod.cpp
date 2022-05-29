#include <bits/stdc++.h>

using namespace std;

string helper(int ind, string &str, map<string, string> &dict, string res){
	if(ind==str.length()){
		return res;
	}
	string temp = "";
	for(int i=ind; i<str.length(); i++){
		temp += str[i];
		sort(temp.begin(), temp.end());
		if(dict.find(temp)!=dict.end()){
			if(ind==0){
				string sentence = helper(i+1, str, dict, dict[temp]);
				if(sentence.length()!=0)
					return sentence;
			}
			else{
				string sentence = helper(i+1, str, dict, res+" "+dict[temp]);
				if(sentence.length()!=0)
					return sentence;
			}
		}
	}
	return "";
}

int main(){
	string str = "ehllotehotwolrds";
	vector<string> wordset;
	wordset.push_back("hello");
	wordset.push_back("to");
	wordset.push_back("the");
	wordset.push_back("world");
	map<string, string> dict;
	for(int i=0; i<wordset.size(); i++){
		string temp = wordset[i];
		sort(temp.begin(), temp.end());
		dict[temp] = wordset[i];
	}
	cout << helper(0, str, dict, "") << endl;
	return 0;
}
