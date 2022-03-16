/*
Problem: https://leetcode-cn.com/problems/maximum-sum-circular-subarray/

Solution:
If the circular subarray of max sum does not cross the bound, then the result is maxSubArraySum();
Else, the result is sum - minSubArraySum() when at least an element is positive.
Therefore, maxSubarraySumCircular = max{maxSubarraySum(), sum - minSubArraySum}.

Complexity:
	Time: O(n),
	Space: O(1), where n is the size of input array.

Since we can use dp to solve maxSubarraySum with O(n) in time and O(1) in space;
Also, getting the sum of an array requires O(n) in time and O(1) in space.
*/

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        // the max sum of subarray in nums
        int max_sum_in = getMaxSubarraySum(nums);
        int min_sum = getMinSubarraySum(nums);
        int total_sum = getTotalSum(nums);
        // the max sum of subarray across the boundary of nums
        int max_sum_cross = max_sum_in;
        if (total_sum != min_sum) {
            max_sum_cross = total_sum - min_sum;
        }
        return max(max_sum_in, max_sum_cross);
    }

    int getMaxSubarraySum(vector<int>& nums) {
        int size = nums.size();
        // dp[i] stores the biggest sum of subarray that ends at nums[i]
        int dp = nums[0];
        int cur_max = dp;
        // dynamic programming
        for (int i = 1; i < size; ++i) {
            dp = max(dp + nums[i], nums[i]);
            cur_max = max(cur_max, dp);
        }
        return cur_max;
    }

    int getMinSubarraySum(vector<int>& nums) {
        int size = nums.size();
        // dp[i] stores the smallest sum of subarray that ends at nums[i]
        int dp = nums[0];
        int cur_min = dp;
        // dynamic programming
        for (int i = 1; i < size; ++i) {
            dp = min(dp + nums[i], nums[i]);
            cur_min = min(cur_min, dp);
        }
        return cur_min;
    }

    int getTotalSum(vector<int>& nums) {
        int size = nums.size();
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += nums[i];
        }
        return sum;
    }
};
