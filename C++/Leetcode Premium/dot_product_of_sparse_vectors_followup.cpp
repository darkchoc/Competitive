/*
Refer to other file, dot_product_sparse_vectors.cpp to see base question.
First follow up is simply that what if one vector is sparse and other is not.

The second followup is what if vectors are represented in compressed ranges. What that means is
[1,1,1,1,2,2,3,4,4,4] will be represented as: [(0:3,1),(4:5,2),(6:6,3),(7:9,4)]
For this we can modify our two pointer approach is length of both vectors after compression is nearly
similar.
*/

#include <bits/stdc++.h>
using namespace std;

class CompressedVector {
    private:
        vector<pair<pair<int, int>, int> > v;
    public:
        CompressedVector(vector<int> &nums){
            v.clear();
            int i = 0;
            while(i < nums.size()){
                int j = i;
                while(j < nums.size() && nums[i]==nums[j])
                    j++;
                v.emplace_back(make_pair(i, j-1), nums[i]);
                i=j;
            }
        }

        vector<pair<pair<int, int>, int> >& getVector(){
            return v;
        }

        int dotProduct(CompressedVector vec2){
            vector<pair<pair<int, int>, int> > &v2 = vec2.getVector();
            int i = 0, j = 0;
            int ans = 0;
            while(i < v.size() && j < v2.size()){
                // now both i and j are pointing to an interval. We see what's the overlap, and add that
                // to the answer. After that, we incremenet i, if that interval is ending first. 
                // Otherwise increment j.
                int overlap = min(v[i].first.second, v2[j].first.second) - max(v[i].first.first, v2[j].first.first) + 1; // +1 because if range of overlap is index p to q, then overlap = q-p+1
                ans += overlap*v[i].second*v2[j].second;
                if(v[i].first.second < v2[j].first.second)
                    i++;
                else if(v[i].first.second > v2[j].first.second)
                    j++;
                else { // if both intervals are ending
                    i++;
                    j++;
                }
            }
            return ans;
        }
};

void runTestCase(vector<int> nums1, vector<int> nums2){
    CompressedVector v1(nums1);
    CompressedVector v2(nums2);
    cout << v1.dotProduct(v2);
}

int main() {
    runTestCase({1,1,1,1,2,2,3,4,4,5}, {2,2,3,3,3,4,5,6,6,6}); // 117
}