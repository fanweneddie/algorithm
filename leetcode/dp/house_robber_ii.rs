/*
Problem: https://leetcode-cn.com/problems/house-robber-ii/

Solution: dynamic programming twice
We get max{rob[0, size - 2], rob[1, size - 1]}.

Complexity:
Time: O(n)
Space: O(1),where n is the size of input nums.
*/

impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        let size = nums.len();
        // special case
        if size == 1 {
            return nums[0];
        }
        // the result of not robbing the last house
        let result1 = get_max_sum_in_range(&nums, 0, size - 2);
        // the result of not robbing the first house
        let result2 = get_max_sum_in_range(&nums, 1, size - 1);
        return std::cmp::max(result1, result2);        
    }
}

// get the maximum sum of robbery in house[start, end]
// we make sure that end >= start
fn get_max_sum_in_range(nums: &Vec<i32>, start: usize, end: usize) -> i32 {
    // dp[i] means the max sum in house[0,...,i]
    // dp i-2, i-1 and i
    let mut dp_llast = 0;
    let mut dp_last = 0;
    let mut dp_cur = nums[start];
    // dynamic programming
    dp_last = nums[start];
    for i in start+1..end+1 {
        dp_cur = std::cmp::max(dp_llast + nums[i], dp_last);
        dp_llast = dp_last;
        dp_last = dp_cur; 
    }

    return dp_cur;
}

