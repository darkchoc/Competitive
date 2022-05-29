/*

A string is given of some words(plaintext). You have to change it into a cipher using a key. 
The key maps a letter into another letter(may be the same letter). But no two letters can be mapped into a same letter, 
such that a cipher can be identified as a unique. Space will be mapped into space only. 
All the words of the cipher should be anagram of the corresponding word of the plaintext. 
Find, how many different keys are possible to satisfy all the conditions.
Each plaintext has at most 4 words and each word has at most 4 characters.

Eg: abcd bcfg -> 2

*/

#include <bits/stdc++.h>
using namespace std;

void interesect(set<char> &options, set<char> &letters){
	set<char> newset;
	for(set<char>::iterator it=options.begin(); it!=options.end(); it++){
		if(letters.find(*it)!=letters.end())
			newset.insert(*it);
	}
	options = newset;
}

void recurse(map<char, set<char> > &mp, map<char, set<char> >::iterator it, set<char> &occuppied, int &ans){
	if(it==mp.end()){
		ans++;
		return;
	}
	for(set<char>::iterator it_s = (it->second).begin(); it_s!=(it->second).end(); it_s++){
		if(occuppied.find(*it_s)==occuppied.end()){
			occuppied.insert(*it_s);
			recurse(mp, ++it, occuppied, ans);
			it--;
			occuppied.erase(*it_s);
		}
	}
	return;
}

int helper(vector<string> &words){
	map<char, set<char> > mp;
	set<char> s;
	for(int i=0; i<26; i++)
		s.insert('a'+i);
	for(int i=0; i<words.size(); i++){
		for(int j=0; j<words[i].size(); j++){
			if(mp.find(words[i][j])==mp.end()){
				mp[words[i][j]] = s;
			}
		}
	}
	for(int i=0; i<words.size(); i++){
		set<char> letters;
		for(int j=0; j<words[i].size(); j++)
			letters.insert(words[i][j]);
		for(int j=0; j<words[i].size(); j++){
			interesect(mp[words[i][j]], letters);
		}
	}
	set<char> occuppied; 
	int ans = 0;
	recurse(mp, mp.begin(), occuppied, ans);
	return ans;
}

int main(){
	vector<string> words;
	int n;
	cin >> n; 
	string word;
	for(int i=0; i<n; i++){
		cin >> word;
		words.push_back(word);
	}
	cout << helper(words);
	return 0;
}