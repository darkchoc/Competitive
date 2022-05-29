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

string function_(string str){
    if(str.length()==0)
        return "";
    string result="";
    int i=0;
    int num;
    while(i<str.length()){
        
        //first get the number of times word has to be repeated
        string number = "";
        while(i<str.length()){
            if(str[i]=='[')
                break;
            number += str[i];
            i++;
        }
        if(number=="")
            num=0;
        else
            num = stoi(number);
            
        i++;
        string word="";
        if(isdigit_(str[i])){
            int j = i;
            int opening_bracket=1;
            while(j<str.length()){
                if(str[j]=='[')
                    opening_bracket++;
                else if(str[j]==']'){
                    opening_bracket--;
                    if(opening_bracket==0)
                        break;
                }
                j++;
            }
            word = function_(str.substr(i, j-i));
            i = j;
        } 
        else{
            while(i<str.length()){
        	if(str[i]==']')
                	break;
            	word += str[i];
            	i++;
	    }
        }
        
        while(num){
            result+=word;
            num--;
        }
        i++;
    }
    return result;
         
/*        i++;
        
        //get the word that has to be repeated
        string word = "";
        while(i<str.length()){
            if(str[i]==']')
                break;
            word += str[i];
            i++;
        }
        
        //add the word to result string , num times
        while(num){
            result += word;
            num--;
        }
        i++;
    }
    return result;
*/
}

int main(){
    string str;
    cin >> str;
    cout << function_(str);
    return 0;
}




