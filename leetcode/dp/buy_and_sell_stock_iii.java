/*
Problem: https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/

Solution: DP

Complexity:
Time: O(n)
Space: O(1), where n is the size of prices

*/
class Solution {
    public static final int INF = 999999;
    // we make sure that prices is not empty
    public int maxProfit(int[] prices) {
        int size = prices.length;
        // the maximum money after ith day
        // when holding and not holding the stock
        // 0, 1 and 2 mean having done 0,1 and 2 transactions, respectively
        int dp_hold_0, dp_hold_1, dp_hold_2;
        int dp_nhold_0, dp_nhold_1, dp_nhold_2;

        // init for day 0
        dp_hold_0 = -prices[0];
        dp_hold_1 = -INF;
        dp_hold_2 = -INF;
        dp_nhold_0 = 0;
        dp_nhold_1 = -INF;
        dp_nhold_2 = -INF;


        // dynamic programming
        for (int i = 1; i < size; ++i) {
            int new_hold_0, new_hold_1, new_hold_2;
            int new_nhold_0, new_nhold_1, new_nhold_2;

            new_hold_0 = Math.max(dp_hold_0, dp_nhold_0 - prices[i]);
            new_hold_1 = Math.max(dp_hold_1, dp_nhold_1 - prices[i]);
            new_hold_2 = Math.max(dp_hold_2, dp_nhold_2 - prices[i]);
            new_nhold_0 = dp_nhold_0;
            new_nhold_1 = Math.max(dp_nhold_1, dp_hold_0 + prices[i]);
            new_nhold_2 = Math.max(dp_nhold_2, dp_hold_1 + prices[i]);
            
            dp_hold_0 = new_hold_0;
            dp_hold_1 = new_hold_1;
            dp_hold_2 = new_hold_2;
            dp_nhold_0 = new_nhold_0;
            dp_nhold_1 = new_nhold_1;
            dp_nhold_2 = new_nhold_2;
        }

        return Math.max(Math.max(dp_nhold_0, dp_nhold_1), dp_nhold_2);
    }
}
