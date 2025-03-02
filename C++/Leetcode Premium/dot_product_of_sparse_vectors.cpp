/*

AMAZING BLOG: https://leetcode.com/discuss/interview-question/6282240/1570.-Dot-Product-of-Two-Sparse-Vectors-(All-Follow-Ups)/



Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) Initializes the object with the vector nums
dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
A sparse vector is a vector that has mostly zero values, you should store the sparse vector efficiently and compute the dot product between two SparseVector.

Follow up: What if only one of the vectors is sparse?

Example 1:

Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
Output: 8
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
Example 2:

Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
Output: 0
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
Example 3:

Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
Output: 6
 

Constraints:

n == nums1.length == nums2.length
1 <= n <= 10^5
0 <= nums1[i], nums2[i] <= 100
*/

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1 = new SparseVector(nums1);
// SparseVector v2 = new SparseVector(nums2);
// int ans = v1.dotProduct(v2);

#include <bits/stdc++.h>
using namespace std;

class SparseVectorInefficient {
    private:
        map<int, int> mp;
    public:
        SparseVectorInefficient(vector<int> &nums) {
            mp.clear();
            for(int i=0; i<nums.size(); i++)
                if(nums[i]!=0)
                    mp[i]=nums[i];
        }

        map<int, int>& getMap(){
            return mp;
        }

        int dotProduct(SparseVectorInefficient v2){
            map<int, int> &mp2 = v2.getMap(); //getting map by reference
            int ans = 0;
            // FOLLOW UP: If only one vector is sparse, then we can choose the map which has less
            // elements and traverse on that only.
            map<int,int> &smaller = (mp.size() > mp2.size())?mp2:mp;
            map<int,int> &larger = (mp.size() > mp2.size())?mp:mp2;
            for(map<int, int>::iterator it=smaller.begin(); it!=smaller.end(); it++){
                if(larger.find(it->first)!=larger.end())
                    ans += larger[it->first] * it->second;
            }
            return ans;
        }
};

void runTestCaseInefficient(vector<int> nums1, vector<int> nums2){
    SparseVectorInefficient v1(nums1);
    SparseVectorInefficient v2(nums2);
    cout << v1.dotProduct(v2) << endl;
}

class SparseVectorEfficient {
    private:
        vector<pair<int,int> > v;
    public:
        SparseVectorEfficient(vector<int> &nums){
            v.clear();
            for(int i=0; i<nums.size(); i++)
                if(nums[i]!=0)
                    v.emplace_back(i, nums[i]);
        }

        vector<pair<int, int> >& getVector(){
            return v;
        }

        int dotProduct(SparseVectorEfficient v2){
            vector<pair<int, int> > &vec2 = v2.getVector();
            int ans = 0;
            // if both are sparse, we can normally iterate (TWO POINTER APPROACH)
            int i = 0, j = 0;
            while(i < v.size() && j < vec2.size()) {
                if(v[i].first < vec2[j].first)
                    i++;
                else if(v[i].first > vec2[j].first)
                    j++;
                else {
                    // v[i].first==vec2[j].first
                    ans += v[i].second*vec2[j].second;
                    i++;
                    j++;
                }
            }
            return ans;
        }
};

void runTestCaseEfficient(vector<int> nums1, vector<int> nums2) {
    /*
    *** HashMap Solution Often Rejected ***
    Although a HashMap-based solution might seem efficient at first, interviewers often reject it for large sparse vectors due to inefficiencies in hash computation.
    The preferred solution is a two-pointer approach using sparse representation ((index, value) pairs).
    */
   SparseVectorEfficient v1(nums1);
   SparseVectorEfficient v2(nums2);
   cout << v1.dotProduct(v2) << endl;
}

class SparseVectorDiffLength {
    private:
        vector<pair<int,int> > v;
    public:
        SparseVectorDiffLength(vector<int> &nums){
            v.clear();
            for(int i=0; i<nums.size(); i++)
                if(nums[i]!=0)
                    v.emplace_back(i,nums[i]);
        }

        vector<pair<int, int> >& getVector(){
            return v;
        }

        int dotProduct(SparseVectorDiffLength vec2){
            vector<pair<int, int> > &v2 = vec2.getVector();
            vector<pair<int, int> > &smaller = (v.size() > v2.size())?v2:v;
            vector<pair<int, int> > &larger  = (v.size() > v2.size())?v:v2;
            // now iterate on smaller and apply binary search on larger
            int ans = 0;
            for(int i=0; i<smaller.size(); i++){
                int index = smaller[i].first;
                int l = 0, r = larger.size()-1;
                // find if index exists in larger
                while(l <= r){ // equal condition ensures that we process the equality case too. in case 
                // at the very end, when l==r, then larger[l].first = index. 
                    int mid = (l+r)/2;
                    if(larger[mid].first > index)
                        r = mid-1;
                    else if(larger[mid].first < index)
                        l = mid+1;
                    else {
                        // equal
                        ans += smaller[i].second * larger[mid].second;
                        break;
                    }
                }
            }
            return ans;
        }
};

void runTestCaseSparseVectorDiffLength(vector<int> nums1, vector<int> nums2){
    SparseVectorDiffLength v1(nums1);
    SparseVectorDiffLength v2(nums2);
    cout << v1.dotProduct(v2) << endl;
}

// small example to see how if we simply return map, it is returned by value and not reference.
class A {
    private:
        map<int,int> mp;
    public:
        map<int, int> getMap(){
            return mp;
        }
};

int main() {
    // Small example to see how if maps are not passed by reference, then all values are copied
    // and a new map is created.
    A a;
    map<int, int> mp = a.getMap();
    mp[1]=2;
    mp = a.getMap();
    cout << mp[1] << endl; // 0
    // Hash map approach: Slightly inefficient as we waste time in calculating hash of the keys.
    // Also iteration over map is probably not as good as iteration over vector.
    runTestCaseInefficient({1,0,0,2,3},{0,3,0,4,0}); // 8
    runTestCaseInefficient({0,1,0,0,0},{0,0,0,0,2}); // 0
    runTestCaseInefficient({0,1,0,0,2,0,0},{1,0,0,0,3,0,4}); // 6

    // Better approach. Instead of using hash map, store non-zero (index, value) pair in vector.
    // Iterate over these vectors (two pointer). 
    runTestCaseEfficient({0,1,0,0,2,0,0},{1,0,0,0,3,0,4}); // 6

    // Follow up: What happens when one vector is sparse and other is not? 
    /*
    In this case, after processing the vectors, one would be small and other would be much longer.
    For example, ifthe two vectors were: [0,3,0,0,0,0,9] and [1,2,3,4,0,0,7]. After processing, they 
    would become: [(1,3),(6,9)] and [(0,1),(1,2),(2,3),(3,4),(6,7)]. In this case, we iterate over
    smaller vector and apply binary search on larger vector to find first element >= required.
    If that is equal to required element, good, otherwise, move forward in smaller element.

    For both sparse, time complexity of dotProduct was O(K) where K=#elements in sparse vector
    But if we use previous method for one sparse and one dense vector, time complexity will be
    O(K + N), where N = #elements in dense vector.
    But by using binary search, it will be O(KlogN)
    So when K << N, O(KlogN) might be smaller than O(N+K).
    But if K~N, then O(KlogN) = O(NlogN)
    */
   runTestCaseSparseVectorDiffLength({0,1,0,0,2,0,0},{1,0,0,0,3,0,4}); // 6
}