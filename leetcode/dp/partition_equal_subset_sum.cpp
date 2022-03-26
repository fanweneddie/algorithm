/*
Problem: https://leetcode-cn.com/problems/partition-equal-subset-sum/

Solution: top-down dynamic programming
We set dp[i][j] as whether there exists subsequence of [0...i] whose sum is j.
If nums[i] == j, then dp[i][j] = true;
If nums[i] > j, then dp[i][j] = dp[i-1][j];
If nums[i] < j, then dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i]];

At last, we return dp[n-1][sum/2], where n is the size of nums and sum is the sum of nums.

Complexity:
	Time: O(n*sum)
	Space: O(n*sum)
*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int size = nums.size();
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        // the sum should be an even number
        if (sum % 2 == 1) {
            return false;
        }
        int target = sum / 2;
        // dp[i][j] shows whether there exists subsequence of [0...i] 
        // whose sum is j.
        // 1 means true, -1 means false and 0 means unsolved
        vector<vector<int>> dp;
        dp.resize(size);
        for (int i = 0; i < size; ++i) {
            dp[i].resize(target + 1);
            for (int j = 0; j <= target; ++j) {
                dp[i][j] = 0;
            }
        }

        // top-down dynamic programming
        int result = solve(size - 1, target, nums, dp);
        if (result == 1) {
            return true;
        } else {
            return false;
        }
    }

    // Solve dp[right][target] and return it
    int solve(int right, int target, 
                const vector<int>& nums,vector<vector<int>>& dp) {
        // out of bound
        if (right < 0) {
            return -1;
        }
        // calculated
        if (dp[right][target] != 0) {
            return dp[right][target];
        }
        // calculate and record
        if (nums[right] == target) {
            dp[right][target] = 1;
            return 1;
        } else if (nums[right] > target) {
            int result = solve(right - 1, target, nums, dp);
            dp[right][target] = result;
            return result;
        } else {
            int result1 = solve(right - 1, target - nums[right], nums, dp);
            int result2 = solve(right - 1, target, nums, dp);
            if (result1 == 1 || result2 == 1) {
                dp[right][target] = 1;
                return 1;
            } else {
                dp[right][target] = -1;
                return -1;
            }
        }
    }
};
