/*
Problem: https://leetcode-cn.com/problems/longest-consecutive-sequence/

Solution: union set + hashmap

Complexity:
	Time: O(nlgn) on worst and O(n \alpha(n)) on average
	Space: O(n)
*/

class UnionSet {
    // The representative node of each node
    private:
    map<int, int> roots;
    
    public:
    UnionSet(const vector<int>& nums) {
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            int ele = nums[i];
            roots[ele] = ele;
        }
    }

    // Find the final root of node i
    int findRoot(int i) {
        if (roots[i] == i) {
            return i;
        } else {
            return findRoot(roots[i]);
        }
    }

    // Union node i and node j
    // Let j's representative node link to i's
    // Note that we should aggregate the length
    // Return the total length
    int doUnion(int i, int j, map<int, int>& lens) {
        int root_i = findRoot(i);
        int root_j = findRoot(j);
        int len_i = getLen(i, lens);
        int len_j = getLen(j, lens);
        int total_len = len_i + len_j;

        setLen(i, total_len, lens);
        roots[root_j] = root_i;
        return total_len;
    }

    // Check whether node i and node j are in the same connective component
    bool isConnective(int i, int j) {
        return findRoot(i) == findRoot(j);
    }

    // Get the length of consecutive numbers containing element i
    int getLen(int i, map<int, int>& lens) {
        int root = findRoot(i);
        if (lens.find(root) == lens.end()) {
            return 0;
        } else {
            return lens[root];
        }
    }

    // Set the length of consecutive numbers containing element i as new_len
    void setLen(int i, int new_len, map<int, int>& lens) {
        int root = findRoot(i);
        if (lens.find(root) != lens.end()) {
            lens[root] = new_len;
        }
    }
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int size = nums.size();
        // special case
        if (size == 0) {
            return 0;
        }
        
        int max_len = 1;
        // stores the length of consecutive numbers containing each element
        map<int, int> lens;
        UnionSet us = UnionSet(nums);
        
        // count the original frequency before merging
        for (int i = 0; i < size; ++i) {
            int ele = nums[i];
            lens[ele] = 1;
        }

        // union
        for (int i = 0; i < size; ++i) {
            int ele = nums[i];
            // ele - 1 is in present and it is not merged with ele
            if (lens.find(ele - 1) != lens.end() && !us.isConnective(ele, ele - 1)) {
                max_len = max(max_len, us.doUnion(ele, ele - 1, lens));
            }
            // ele - 1 is in present and it is not merged with ele
            if (lens.find(ele + 1) != lens.end() && !us.isConnective(ele, ele + 1)) {
                max_len = max(max_len, us.doUnion(ele, ele + 1, lens));
            }
        }
        return max_len;
    }
};
