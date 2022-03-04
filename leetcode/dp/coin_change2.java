/*
Problem: https://leetcode-cn.com/problems/coin-change-2/

Solution: dynamic programming

Complexity:
	Time: O(mn)
	Space: O(m), where m is amount and n is the size of coins
*/

class Solution {
    public int change(int amount, int[] coins) {
        // dp[i] means the number of coin combinations for amount i
        int[] dp = new int[amount + 1];

        dp[0] = 1;
        // we consider the contribution of each coin, one by one
        for (int coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
}
