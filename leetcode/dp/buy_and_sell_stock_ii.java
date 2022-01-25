/*
Problem: https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/

Solution:
We set dp_hold[i] as the max number at hand after day i with holding the stock, 
and dp_nhold[i] as the max number at hand after day i without holding the stock.
Then, we have
dp_hold[0] = -prices[0]
dp_nhold[0] = 0
dp_hold[i] = max{dp_hold[i-1], dp_nhold[i-1] - prices[i]}
dp_nhold[i] = max{dp_nhold[i-1], dp_hold[i-1] + prices[i]}

At last, we return dp_nhold[size-1]

Complexity:
Time: O(n)
Space: O(1), where n is the size of prices.
*/

class Solution {
    // we make sure that prices is not empty
    public int maxProfit(int[] prices) {
        int size = prices.length;
        // the maximum money after ith day
        // when holding and not holding the stock
        int dp_hold, dp_nhold;

        // init for day 0
        dp_hold = -prices[0];
        dp_nhold = 0;

        // dynamic programming
        for (int i = 1; i < size; ++i) {
            int temp = dp_hold;
            dp_hold = Math.max(dp_hold, dp_nhold - prices[i]);
            dp_nhold = Math.max(dp_nhold, temp + prices[i]);
        }

        return dp_nhold;
    }
}
