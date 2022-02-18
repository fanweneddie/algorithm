/*
Problem: https://leetcode-cn.com/problems/target-sum/

Solution: DP
dp[i][j] is the number of expression in [0,...i] that equals to j
and dp[i][sum] = dp[i-1][sum - num[i]] + dp[i-1][sum + num[i]]

Complexity:
	Time: O(nk)
	Space: O(nk), where n is the size of array and k is the range of elements.
*/

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int size = nums.size();
        // dp[i][j] is the number of expression in [0,...i] that equals to j
        vector<map<int, int>> dp;
        dp.resize(size);
        return calculate_dp(size - 1, target, nums, dp);
    }

    // Calculate dp[index][target]
    // we make sure that 0 <= index < size
    int calculate_dp(int index, int target, vector<int>& nums, vector<map<int, int>>& dp) {
        // return the value if it has been calculated
        if (dp[index].find(target) != dp[index].end()) {
            return dp[index][target];
        }

        int ele = nums[index];
        if (index == 0) {
            if (target == ele && target == -ele) {
                dp[index][target] = 2;
            } else if (target == ele || target == -ele) {
                dp[index][target] = 1;
            } else {
                dp[index][target] = 0;
            }
        } else {
            dp[index][target] = calculate_dp(index - 1, target - ele, nums, dp) 
                                + calculate_dp(index - 1, target + ele, nums, dp);
        }
        return dp[index][target];
    }
};
