/*
Problem: https://leetcode-cn.com/problems/min-cost-climbing-stairs/submissions/
Solution: dp
Complexity:
	Time: O(n)
	Space: O(1), where n is the size of input array
*/

class Solution {
    public int minCostClimbingStairs(int[] cost) {
        // dp[i] means the min cost to reach position i
        // represents dp[i-2], dp[i-1] and dp[i]
        int dp_pre_2 = 0;
        int dp_pre_1 = 0;
        int dp = 0;

        // dynamic programming
        // dp[i] = min{dp[i-2] + cost[i-2], dp[i-1] + cost[i-1]}
        int size = cost.length;
        for (int i = 2; i <= size; ++i) {
            dp = Math.min(dp_pre_2 + cost[i-2], dp_pre_1 + cost[i-1]);
            dp_pre_2 = dp_pre_1;
            dp_pre_1 = dp;
        }

        return dp;
    }
}
