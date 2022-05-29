#include <bits/stdc++.h>

using namespace std;

namespace abc{
	extern int x;
}

namespace pqr{
	void func(){
		abc::x = 5;
		return;
	}
}
