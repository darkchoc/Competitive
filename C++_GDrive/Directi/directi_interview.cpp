N -> Positive integer
0 to N inclusive, number of set bits

000
001
010 -> 2
011
100
101
110
111


20


10100

n
if(n==0 )
	return 0;
dig = floor(log2(n));
//ans = 1*digC1 + 2*digC2 + … dig*digCdig -> (2^dig)-1
ans = dig * pow(2, dig-1)
ans += func(n-2^dig) + (n-2^dig) +1


int func2(int dig){
	return dig*pow(2, dig-1);
}

int func(int n){
	if(n<2)
		return n;
	int dig = floor(log2(n));
	int ans = 0;
	ans = func2(dig);
	ans += func(n - 

pow(2, dig)) + (n - pow(2, dig)) + 1;
	return ans;
}
A[N]

i<j<k
A[i]<A[j]<A[k]

A -> [8,5,11,10,15]

dp[n]
dp[0]=1;
for(int i=1; i<A.length(); i++){
	for(int j=i-1; j>=0; j--){
		if(A[i]>A[j])
			dp[i] = max(dp[i], dp[j]+1);
	}
}

for(int i=0; i<A.length()-2; i++){
	int j=i+1;
	int temp;
	while(j<A.length()-1 && A[j]<=A[i])
		j++;
	if(j==A.length()-1)
		continue;
	temp = A[j];
	for(int k=j+1; k<A.length(); k++){
		if(A[k]>temp)
			return true;
		if(A[k]>A[i])
			temp = min(temp, A[k]);
	}
}
return false;


func(vector<int>& arr){
	if(arr.size()<3)
		return false;
	vector<int> left_min (arr.size());
	vector<int> right_max(arr.size());
	
	//fill left_min
	stack<int> st;
	for(int i=0; i<arr.size(); i++){
		while(!st.empty() && arr[st.top()]>=arr[i])
			st.pop();
		if(st.empty()){
			left_min[i]=-1;
			st.push(i);
		}
		else{
			left_min[i]=st.top();

	}

	//right_max
	while(!st.empty())
		st.pop();
	for(int i=arr.size()-1; i>=0; i--){
		while(!st.empty() && arr[st.top()]<=arr[i])
			st.pop();
		if(st.empty()){
			right_max[i]=arr.size();
			st.push(i);
		}
		else
			right_max[i]=st.top();
	}
	
	for(int i=1; i<arr.size()-1; i++){
		if(left_min[i]!=-1 && right_max[i]!=arr.size())
			return true;
	}
	return false;
}


A -> [8,5,11,10,15]
left_min = -1, -1, 1, 1, 1
right_max =  4, 4, 4, 4, 5 
st = 4
