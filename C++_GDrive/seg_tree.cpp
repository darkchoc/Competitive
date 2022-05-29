/*Two types of queries. 
	update -> update value at index i with value v
	query(l,r) -> get min(l,r)*sum(l,r)
*/
#include <bits/stdc++.h>

using namespace std;

class SegTree{
	private:
		vector<int> seg_tree_min;
		vector<int> seg_tree_sum;
		int total_nums;

	public:
		SegTree(vector<int> &nums){
			//build segtree here
			total_nums = nums.size();
			int n = total_nums;
			//find power of two which is >= n;
			double x = ceil(log2(n));
			int reqd_size = 2*pow(2, x) - 1;
			seg_tree_sum.resize(reqd_size, 0);
			seg_tree_min.resize(reqd_size, INT_MAX);
			buildSegTree(nums, 0, n-1, 0, "sum");
			buildSegTree(nums, 0, n-1, 0, "min"); 
			cout << "required size: " << reqd_size << endl;
			cout << "seg_tree_sum: " << endl;
			for(int i=0; i<reqd_size; i++)
				cout << seg_tree_sum[i] << " ";
			cout << endl << "seg_tree_min: " << endl;
			for(int i=0; i<reqd_size; i++)
				cout << seg_tree_min[i] << " ";
			cout << endl;
			return;
		}

		void merge(int ind, string operation){
			if(operation=="sum")
				seg_tree_sum[ind] = seg_tree_sum[2*ind+1] + seg_tree_sum[2*ind+2];
			else if(operation=="min")
				seg_tree_min[ind] = min(seg_tree_min[2*ind+1], seg_tree_min[2*ind+2]);
			return;
		}

		int merge(int left_ans, int right_ans, string operation){
			if(operation=="sum")
				return left_ans+right_ans;
			else if(operation=="min")
				return min(left_ans, right_ans);
		}

		void buildSegTree(vector<int> &nums, int lo, int hi, int tree_idx, string operation){
			if(lo==hi){
				if(operation=="min")
					seg_tree_min[tree_idx] = nums[lo];
				else if(operation=="sum")
					seg_tree_sum[tree_idx] = nums[hi];
				return;
			}
			int mid = (lo+hi)/2;
			buildSegTree(nums, lo, mid, 2*tree_idx+1, operation);
			buildSegTree(nums, mid+1, hi, 2*tree_idx+2, operation);

			merge(tree_idx, operation);
			return;
		}

		void updateSegTree(int num_ind, int val, string operation, int lo, int hi, int tree_ind){
			if(lo==hi){
				if(operation=="sum")
					seg_tree_sum[tree_ind] = val;
				else if(operation=="min")
					seg_tree_min[tree_ind] = val;
				return;
			}
			int mid = (lo+hi)/2;
			if(num_ind<=mid)
				updateSegTree(num_ind, val, operation, lo, mid, 2*tree_ind+1);
			else 
				updateSegTree(num_ind, val, operation, mid+1, hi, 2*tree_ind+2);

			merge(tree_ind, operation);
			return;
		}

		void update(int ind, int val, vector<int> &nums){
			nums[ind] = val;
			updateSegTree(ind, val, "sum", 0, total_nums-1, 0);
			updateSegTree(ind, val, "min", 0, total_nums-1, 0);
			return;
		}

		int querySegTree(int nums_ind_left, int nums_ind_right, int tree_ind_left, int tree_ind_right, int curr_tree_ind, string operation){
			if(tree_ind_left>=nums_ind_left && tree_ind_right<=nums_ind_right){
				if(operation=="sum")
					return seg_tree_sum[curr_tree_ind];
				else if(operation=="min")
					return seg_tree_min[curr_tree_ind];
			}
			if(tree_ind_left>nums_ind_right || tree_ind_right<nums_ind_left){
				if(operation=="sum")
					return 0;
				else if(operation=="min")
					return INT_MAX;
			}
			int mid = (tree_ind_right+tree_ind_left)/2;
			int left_ans = querySegTree(nums_ind_left, nums_ind_right, tree_ind_left, mid, 2*curr_tree_ind+1, operation);
			int right_ans = querySegTree(nums_ind_left, nums_ind_right, mid+1, tree_ind_right, 2*curr_tree_ind+2, operation);

			return merge(left_ans, right_ans, operation);
		}

		int query(int left, int right){
			int min_ = querySegTree(left, right, 0, total_nums-1, 0, "min");
			int sum_ = querySegTree(left, right, 0, total_nums-1, 0, "sum");
			return min_*sum_;
		}

		int query(int left, int right, string operation){
			return querySegTree(left, right, 0, total_nums-1, 0, operation);
		}
};

void print_(vector<int> &nums){
	for(int i=0; i<nums.size(); i++)
		cout << nums[i] << " " ;
	cout << endl;
	return;
}

int main(){
	vector<int> nums;
	nums.push_back(1); nums.push_back(4); nums.push_back(2); nums.push_back(6); nums.push_back(-3);
	nums.push_back(8), nums.push_back(9); nums.push_back(4); nums.push_back(0); nums.push_back(2); //size = 10
	
	SegTree* segtree = new SegTree(nums);

	print_(nums);
	cout << "min 0-9: " << segtree->query(0, 9, "min") << endl;
	cout << "min 3-8: " << segtree->query(3, 8, "min") << endl;
	cout << "sum 0-9: " << segtree->query(0, 9, "sum") << endl;
	cout << "sum 3-8: " << segtree->query(3, 8, "sum") << endl;
	cout << "min*sum 0-9: " << segtree->query(0, 9) << endl;
	cout << "min*sum 3-8: " << segtree->query(3, 8) << endl;

	segtree->update(3, -4, nums);
	print_(nums);
	cout << "min 2-7: " << segtree->query(2, 7, "min") << endl;
	cout << "sum 2-7: " << segtree->query(2, 7, "sum") << endl;
	cout << "min*sum 2-7: " << segtree->query(2, 7) << endl;

	segtree->update(3, 0, nums);
	segtree->update(4, 3, nums);
	print_(nums);
	cout << "min 1-6: " << segtree->query(1, 6, "min") << endl;
	cout << "sum 1-6: " << segtree->query(1, 6, "sum") << endl;
	cout << "min*sum 1-6: " << segtree->query(1, 6) << endl;
	cout << "min 0-9: " << segtree->query(0, 9, "min") << endl;
	cout << "sum 0-9: " << segtree->query(0, 9, "sum") << endl;
	cout << "min*sum 0-9: " << segtree->query(0, 9) << endl;

	return 0;
}