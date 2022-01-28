/*
Problem: https://leetcode-cn.com/problems/house-robber/

Solution: DP
We set dp[i] to store the max sum in house[0,...,i]
Then we have
dp[0] = nums[0],
dp[i] = max{dp[i-2] + nums[i], dp[i-1]}

Complexity:
Time: O(n)
Space: O(1), where n is the size of input array
*/

impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let size = nums.len();
        // special case
        if size == 1 {
            return nums[0];
        }
        // dp i-2, i-1 and i
        // dp[i] means the max sum in house[0,...,i]
        let mut dp_llast = 0;
        let mut dp_last = 0;
        let mut dp_cur = 0;
        // dynamic programming
        dp_last = nums[0];
        for i in 1..size {
            dp_cur = std::cmp::max(dp_llast + nums[i], dp_last);
            dp_llast = dp_last;
            dp_last = dp_cur; 
        }

        return dp_cur;
    }
}
