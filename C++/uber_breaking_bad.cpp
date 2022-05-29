/*
You are given a set of symbols for the elements in the periodic table 
eg. [... Li, Be, B, C, N, F, Ne, Na, Co, Ni, Cu, Ga, Al, Si...] 
Write the function BreakingBad(name, symbols) that given a name and a set of symbols returns the phrase with the following format. For example:
Symbols = [H, He, Li, Be, B, C, N, F, Ne, Na, Co, Ni, Cu, Ga, Al, Si, Fa]
BreakingBad(“henry alba”, symbols) results in [He]nry [Al]ba
 

Potential Follow-Up Questions (optional)

Additional Examples:
BreakingBad(“connor riddle”, symbols) results in [Co]nnor riddle
BreakingBad(“nicole carry”, symbols) results in [Ni]cole [C]arry
BreakingBad(“jerry seinfeld”, symbols) results in jerry seinfeld
BreakingBad(“ben f gabe”, symbols) results in [Be]n [F] [Ga]be
 
What will happen if we change the symbols to contain 3-4 letter words
Symbols = [Hat, Hey, Liam, Ben, Bot, Can, Net, Fat, He, Na]
BreakingBad(“Henry the Hatter is the Father of Ben”, symbols) results in [He]nry the [Hat]ter is the [Fat]her of [Ben]
*/

#include <bits/stdc++.h>
using namespace std;

class BreakingBad {
    private:
        typedef struct Trie {
            Trie* child[26];
            bool isLeaf = false;
        } Trie;

        Trie* root;

        void addToTrie(string &s){
            Trie* temp = root;
            for(int i=0; i<s.length(); i++){
                int c = (s[i]>='A' && s[i]<='Z')?(s[i]-'A'):(s[i]-'a');
                if(temp->child[c]==NULL){
                    temp->child[c] = new Trie();
                }
                temp = temp->child[c];
            }
            temp->isLeaf=true;
        }

        string transform(string name){
            string completeMatch = "";
            string currentMatch = "";
            string result = "";
            Trie* temp = root;
            for(int i=0; i<name.length(); i++){
                int c = (name[i]>='A' && name[i]<='Z')?(name[i]-'A'):(name[i]-'a');
                if(temp->child[c]){
                    temp = temp->child[c];
                    currentMatch += (c+'a');
                    if(temp->isLeaf){
                        completeMatch = currentMatch;
                    }
                } else {
                    break;
                }
            }
            if(completeMatch!=""){
                result = "[";
                result += toupper(completeMatch[0]);
                result += completeMatch.substr(1) + "]";
            }
            for(int i=completeMatch.length(); i<name.length(); i++)
                result += (name[i]>='A' && name[i]<='Z')?(name[i]-'A'+'a'):name[i];
            return result;
        }

    public:
        BreakingBad(){
            root = new Trie();
        }

        BreakingBad(vector<string> &symbols){
            root = new Trie();
            for(int i=0; i<symbols.size(); i++)
                addToTrie(symbols[i]);
        }

        string BreakingBadConversion(string name){
            string result = "";
            string word = "";
            int i=0;
            while(i<name.length()){
                if(name[i]==' '){
                    if(word!=""){
                        result += transform(word) + " ";
                        word = "";
                    } 
                } else {
                    word += name[i];
                }
                i++;
            }
            if(word!="")
                result += transform(word);
            return result;
        }

        void AddNewSymbols(vector<string> &symbols){
            for(int i=0; i<symbols.size(); i++)
                addToTrie(symbols[i]);
        }
};

int main(){
    vector<string> symbols = {"H", "He", "Li", "Be", "B", "C", "N", "F", "Ne", "Na", "Co", "Ni", "Cu", "Ga", "Al", "Si", "Fa"};

    BreakingBad *bb = new BreakingBad(symbols);
    cout << bb->BreakingBadConversion("henry alba") << endl;
    cout << bb->BreakingBadConversion("connor riddle") << endl;
    cout << bb->BreakingBadConversion("nicole carry") << endl;
    cout << bb->BreakingBadConversion("jerry seinfield") << endl;
    cout << bb->BreakingBadConversion("ben f gabe") << endl;

    vector<string> newSymbols = {"Hat", "Hey", "Liam", "Ben", "Bot", "Can", "Net", "Fat", "He", "Na"};
    bb->AddNewSymbols(newSymbols);
    cout << bb->BreakingBadConversion("Henry the Hatter is the Father of Ben") << endl;
}