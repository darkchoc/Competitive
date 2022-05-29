/*
For a chemical reaction represented by a string, verify that the chemical reaction is a balanced reaction (i.e. that we didn't somehow lose or gain an atom during reaction). If the reaction is balanced return true, otherwise return false.

For example, for the hydrogen combustion reaction:

'2 H2 + O2 -> 2 H2O'
would output true because the number of atoms in the reactants match up with the number of atoms in the product.

However, for the precipitation of silver-chloride:

'NaCl + AgNO3 -> NaNO3 + Ag'
the output should be false because we're missing the chlorine atom in the products.

The reactancts and products will always be separated by a right pointing arrow "->" and the individual molecules within the reactants/products are always separated by a "+" sign. Multiple molecules are represented by a number and space prefacing the molecule (e.g., "2 H20").

Other test cases:

'O2 -> NaCl' = false
'C6H12O6 + 6 O2 -> 6 CO2 + 6 H2O' = true
'10 NH3 + 10 H2O -> 10 NH4 + OH' = false
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void static printMap(map<string, int> &mp){
        for(map<string, int>::iterator it = mp.begin(); it!=mp.end(); it++){
            cout << it->first << " " << it->second << endl;
        }
    }

    void static parseOneSideOfReaction(string &rxn, int &i, map<string, int> &freq){
        while(i < rxn.length()){
            if(rxn[i]=='-'){ // ->
                break; //change in sides of equation.
            } else if(rxn[i]=='+'){
                i+=2;
                continue;
            } else if(rxn[i]==' '){
                i++;
                continue;
            }
            int moleculeMultiplier = 0;
            //parse moleculeMultiplier if present
            while(i < rxn.length() && rxn[i]>='0' && rxn[i]<='9'){
                moleculeMultiplier = moleculeMultiplier*10 + (rxn[i]-'0');
                i++;
            }
            moleculeMultiplier = max(1, moleculeMultiplier);
            //i will either point to space or to start of first molecule.
            if(rxn[i]==' '){
                i++;
            }
            //i points to start of molecule
            int atomMultiplier = 0;
            string atom = "";
            while(i < rxn.length()){
                if((rxn[i]>='A' && rxn[i]<='Z') || rxn[i]==' '){
                    //start of new atom or end of molecule
                    if(atom!=""){
                        atomMultiplier = max(1, atomMultiplier);
                        freq[atom] += moleculeMultiplier*atomMultiplier;
                    }
                    if(rxn[i]==' ')
                        break;
                    atom = rxn[i]; //initialize with new atom's start
                    atomMultiplier = 0;
                } else if(rxn[i]>='a' && rxn[i]<='z'){
                    atom += rxn[i];
                } else if(rxn[i]>='0' && rxn[i]<='9'){
                    atomMultiplier = atomMultiplier*10 + (rxn[i]-'0');
                }
                i++;
            }
            //i either points to ' ' or i=rxn.length()
        }
    }

    bool static compareLhsAndRhs(map<string, int> &lhs, map<string, int> &rhs){
        if(lhs.size() != rhs.size())
            return false;
        for(map<string, int>::iterator it=lhs.begin(); it!=lhs.end(); it++){
            if(rhs.find(it->first)==rhs.end())
                return false;
            if(rhs[it->first]!=it->second)
                return false;
        }
        return true;
    }

    bool static isBalanced(string rxn){
        rxn += ' '; //adding 1 space at end to process last molecule 
        map<string, int> lhs; //keep count of different atoms
        map<string, int> rhs;
        int i=0;
        parseOneSideOfReaction(rxn, i, lhs);
        //i points to '-'
        i+=3;
        parseOneSideOfReaction(rxn, i, rhs);

        /*
        printMap(lhs);
        cout << endl;
        printMap(rhs);
        cout << endl;
        */

        //compare lhs and rhs
        return compareLhsAndRhs(lhs, rhs);
    }
};

int main(){
    cout << Solution::isBalanced("2 H2 + O2 -> 2 H2O") << endl; //true 
    cout << Solution::isBalanced("NaCl + AgNO3 -> NaNO3 + Ag") << endl; //false
    cout << Solution::isBalanced("O2 -> NaCl") << endl; //false
    cout << Solution::isBalanced("C6H12O6 + 6 O2 -> 6 CO2 + 6 H2O") << endl; //true
    cout << Solution::isBalanced("10 NH3 + 10 H2O -> 10 NH4 + OH") << endl; //false
}