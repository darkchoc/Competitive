//Generalized Abbreviations
/*
The logic is as follows. For say "word", I first generate 
1ord, w1rd, wo1d, wor1, 2rd, w2d, wo2, 3d, w3, 4...
Now, consider 1ord, from this we should get -> 1o1d, 1or1, and 1o2. We are skipping the first character (o) and then taking
possible combinations. In order to make function recursive, I added "a" at the beginning of the input, so that when we start 
with index 0, it skips "a", and first makes a1ord, aw1rd, awo1rd... etc. 

The i variable in the helper is the number of letters which we are looking to replace. 
The j variable in the helper is the index from which "i" variables will be replaced. 

Since we substitue the i characters from index j, with i, the next call that is made should be made from character right after 
the number that we inserted. So we add to j the number of digits present in that number (i). 

*/
#include <bits/stdc++.h>

using namespace std;

int digits(int i){
	int cnt=0;
	while(i){
		cnt++;
		i=i/10;
	}
	return cnt;
}

void helper(string word, int ind, vector<string> &ans){
	for(int i=1; i<=(int)word.length()-ind-1; i++){
		for(int j=ind+1; j<=(int)word.length()-i; j++){
			string temp = word.substr(0,j) + to_string(i);
			if(j+i<word.length())
				temp+=word.substr(j+i);
			ans.push_back(temp);
			helper(temp, j+digits(i), ans);
		}
	}
	return;
}

vector<string> func(string word){
	word = "a" + word;
	vector<string> ans;
	helper(word, 0, ans);
	for(int i=0; i<ans.size(); i++)
		ans[i] = ans[i].substr(1);
	return ans;
}

int main(){
	string word;
	cin >> word;
	vector<string> ans = func(word);
	ans.push_back(word);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); ++i)
	{
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}