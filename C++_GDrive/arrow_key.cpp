#include <bits/stdc++.h>

using namespace std;

int main(){
	int c=0;
	while(1){
		c = std::cin.get();
		if(c==72){
		//up
			cout << "Up" << endl;
		}
		else if(c==80){
		//down
			cout << "Down" << endl;
		}
		else if(c==75){
		//left
			cout << "Left" << endl;
		}
		else if(c==77){
		//right
			cout << "Right" << endl;
		}
		else
			break;
	}
	return 0;
}
