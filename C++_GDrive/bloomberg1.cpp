#include <iostream>
#include <string>
#include <vector>

using namespace std;

// "3[abc]" -> "abcabcabc"

// "3[abc][abc]" Invalid

// "3[abc]1[abc]" -> "abcabcabcabc"
// "3[1[a]1[bc]]1[abc]" -> "abcabcabcabc"

// x[string]y[string]z[]

// "3[1[a]1[bc]]" -> "abcabcabc" (invalid)

// "3[123[abc]]"


bool isdigit_(char c){
	if(c-'0'>=0 && c-'0'<=9)
		return true;
	else
		return false;
}

string func_(string str, int &i){
    if(str.length()==0 || i==str.length())
        return "";
    string result="";
    int num;
    while(i<str.length()){
        if(str[i]==']')
            return result;
        else{
            string number="";
            while(i<str.length()){
                if(str[i]=='[')
                    break;
                number+=str[i];
                i++;
            }
            if(number=="")
                num=0;
            else
                num = stoi(number);

            i++;
            string word="";
            if(isdigit_(str[i])){
                word = func_(str, i);
            }
            else{
                while(i<str.length()){
                    if(str[i]==']')
                        break;
                    word+=str[i];
                    i++;
                }
            }

            while(num){
                result+=word;
                num--;
            }
        }
        i++;
    }
    return result;
}

int main(){
    string str;
    cin >> str;
    int ind = 0;
    cout << func_(str, ind);
    return 0;
}




