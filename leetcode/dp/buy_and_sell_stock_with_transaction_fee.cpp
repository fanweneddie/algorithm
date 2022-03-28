/*
Problem: https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

Solution: dynamic programming, which is similar to that 
of problem https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
*/

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        // the maximum money after ith day
        // when holding and not holding the stock
        int dp_hold, dp_nhold;

        // init for day 0
        dp_hold = -prices[0];
        dp_nhold = 0;

        // dynamic programming
        for (int i = 1; i < size; ++i) {
            int temp = dp_hold;
            dp_hold = max(dp_hold, dp_nhold - prices[i]);
            dp_nhold = max(dp_nhold, temp + prices[i] - fee);
        }

        return dp_nhold;
    }
};
