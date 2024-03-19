#include <bits/stdc++.h>
using namespace std;

// **************** SEGMENT TREE SOLUTION (FENWICK TREE BELOW) ********************

/* The constraints say the numbers are between 1 to n */

class SegmentTree {
    private:
        int n;
        vector<int> segmentTree;

        void incrementIndexByOne(int treeIndex, int index, int left, int right){
            if(left == right){
                segmentTree[treeIndex]++;
                return;
            }
            int mid = (right + left)/2;
            if(index <= mid) incrementIndexByOne(2*treeIndex+1, index, left, mid);
            else incrementIndexByOne(2*treeIndex + 2, index, mid+1, right);
            segmentTree[treeIndex] = segmentTree[2*treeIndex+1] + segmentTree[2*treeIndex+2];
        }

        int querySegTree(int qLeft, int qRight, int treeIndex, int start, int end){
            if(qLeft <= start && qRight >= end)
                return segmentTree[treeIndex];
            if(qLeft > end || qRight < start) 
                return 0;
            int mid = (start+end)/2;
            return querySegTree(qLeft, qRight, 2*treeIndex + 1, start, mid) + querySegTree(qLeft, qRight, 2*treeIndex + 2, mid+1, end);
        }

    public:
        SegmentTree(int size){
            n = size;
            /*
            I wasted a lot of time as I thought the size of segment tree should be 2*n - 1 and not 4*n. But that gave me wrong answers, including heap buffer overflow errors. This is because segment tree's structure isn't that of a complete tree. 

            Check out this link: https://medium.com/nybles/understanding-range-queries-and-updates-segment-tree-lazy-propagation-and-mos-algorithm-d2cd2f6586d8
            Also, example: for a semgnet tree over array of size 6:
                       *
                      / \
                     *    \
                   /   \    \
                 *      *     *
                 /\     /\    /\ 
                *  *   *  *  *  *
                This won't be the structure, rather it would be like this:
                      *
                     / \
                   /     \
                  *        *
                  /\       /\
                 *  \     *  \
                 /\  \    /\  \
                *  *  *  *  *  *  

                It would be of this type.
            */
            segmentTree.resize(4*size, 0); 
        }

        void incrementByOne(int index){
            incrementIndexByOne(0, index, 0, n-1);
        }

        int query(int left, int right){
            return querySegTree(left, right, 0, 0, n-1);
        }
};

int solveBySegmentTrees(vector<int> arr, int k){
    // in segment tree, we are basically creating a segment tree that would store how many times a particular element has come. So we are creating a segment tree of size = max(arr[i]) and for every arr[i], we increment segment tree leaf associated with arr[i].
    int n = arr.size();
    // means max value of arr[i] can be n. We are building segment tree not on indices of array but considering elements of array as indices of a bigger array. As, we are rather considering an arr2[n+1], where arr2[i] will give how many times i is present in arr.
    SegmentTree* segTree = new SegmentTree(n+1); // as value of max element can be n. 
    vector<int> smallerOnLeft (n);
    for(int i=0; i<arr.size(); i++){ 
        if(arr[i]==0) 
            smallerOnLeft[i]=0;
        else
            smallerOnLeft[i] = segTree->query(0, arr[i]-1); // find sum of number of elements between 0 and arr[i]-1 that have been added till now
        // now add 1 to the element's count.
        segTree->incrementByOne(arr[i]); 
    }
    // now create a similar segment tree for smallerOnRight
    SegmentTree* segTree2 = new SegmentTree(n + 1);
    vector<int> smallerOnRight (n);
    for(int i=arr.size()-1; i>=0; i--){
        if(arr[i]==0)
            smallerOnRight[i] = 0;
        else
            smallerOnRight[i] = segTree2->query(0, arr[i]-1);
        segTree2->incrementByOne(arr[i]);
    }

    int ans = 0;
    for(int i=0; i<n; i++){
        if(smallerOnLeft[i] >= k && smallerOnRight[i] >= k) ans++;
    }
    return ans;
}

// ******************* FENWICK TREE / BINARY INDEX TREE ****************
// *********************************************************************

// applying the same logic in fenwick trees. Our range is not over index, but over the value of elements. As mentioned above, assume we created another array arr2 of length max(arr[i]) + 1.
// arr2[i] gives number of times i is there in arr. While constructing fenwick tree, we first do query on 0 to x-1 (when arr[i] = x) and check sum as that would give number of elements lesses than x, found till now. Then increment arr2[x] by 1.

class BinaryIndexTree {
    // FENWICK Trees are of length n+1 where n is the length of array. In our case, length of "assumed" array (arr2) is max(arr[i]) + 1. Eg: if we have numbers: 0,4,2, then we want arr2 = [1,0,1,0,1] of length 5 and arr2[i] gives how many times i is present in original arr.

    // Also in Fenwick tree, we assume 1 based indexing usually. 
    private:
        vector<int> fenwickTree;
        int n;

    public:
        BinaryIndexTree(int size){
            // say max element could be x, then we call BIT by doing new BIT(x+1) bcoz our arr2 will of length x+1. Now a normal BIT creates a n+1 size tree for an array of size n. So in this case it will end up creating a BIT tree of size x+2.
            n = size;
            fenwickTree.resize(n+1, 0); // n+1 is essentially = x+2 as "int size" is x+1.
        }

        void increment(int index){
            for(index; index < n + 1; index += index&(-index))
                fenwickTree[index]++;
        }

        int query(int index){
            int sum = 0;
            for(index; index > 0; index -= index&(-index))
                sum += fenwickTree[index];
            return sum;
        }

};

int solveByBinaryIndexedTrees(vector<int> nums, int k){
    int n = nums.size();
    BinaryIndexTree* bit = new BinaryIndexTree(n+1);
    vector<int> smallerOnLeft (n);
    for(int i=0; i<n; i++){
        smallerOnLeft[i] = bit->query(nums[i]);
        bit->increment(nums[i]+1);
        // now, important stuff here. The Fenwick tree is based on 1 based indexing. So consider original nums -> [3,4,0,2,3]. Ideally, our frquency array on which we would like to build and do queries upon would be like: [1,0,1,2,1,0]. where freq[i] gives how many times we saw i in nums.
        // But since fenwick tree is 1-indexed, this freq array would be: [0,1,0,1,2,1,0]. Since it is like this, when we want to query, in Segment tree we had to send nums[i]-1. Now, just sending nums[i] works as the fenwick tree is 1 indexed. Similarly, while updating, we need to update nums[i]+1 instead of nums[i] as it is 1 indexed. 
    }
    BinaryIndexTree* bit2 = new BinaryIndexTree(n+1);
    vector<int> smallerOnRight (n);
    for(int i=n-1; i>=0; i--){
        smallerOnRight[i] = bit2->query(nums[i]);
        bit2->increment(nums[i]+1);
    }
    int ans = 0;
    for(int i=0; i<n; i++)
        if(smallerOnLeft[i] >= k && smallerOnRight[i] >= k) ans++;
    return ans;
}

// *********************************************************************

int main(){
    // cout << solveBySegmentTrees({2,3,6,5,2,3}, 2) << endl; // 2
    // cout << solveByBinaryIndexedTrees({2,3,6,5,2,3}, 2) << endl; // 2
    // cout << solveBySegmentTrees({1,1,1}, 3) << endl; // 0
    // cout << solveByBinaryIndexedTrees({1,1,1}, 3) << endl; // 0
    // cout << solveBySegmentTrees({4,6,3,7,2,7,9,4,6,6}, 3) << endl; // 3
    // cout << solveByBinaryIndexedTrees({4,6,3,7,2,7,9,4,6,6}, 3) << endl; // 3
    // cout << solveBySegmentTrees({0,0,2,5,7,4,2,3,0,4}, 3) << endl; // 3
    cout << solveByBinaryIndexedTrees({0,0,2,5,7,4,2,3,0,4}, 3) << endl; // 3
}