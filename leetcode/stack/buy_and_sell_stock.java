/*
Problem: https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/

Solution:
We try to find the max gap in a timing order.
We use a monotonous stack, and maintain a max_gap.

Complexity:
Time: O(n)
Space: O(n), where n is the size of prices.
*/
class Solution {
    public int INF = 999999;
    // prices is not empty
    public int maxProfit(int[] prices) {
        int size = prices.length;
        // monotonous stack
        Stack<Integer> st = new Stack<Integer>();
        // max gap between two element (in a timing order)
        int max_gap = 0;
        int min_val = INF;

        // init stack
        st.push(new Integer(prices[0]));
        min_val = prices[0];
        // maintain the monotonous stack
        for (int i = 1; i < size; ++i) {
            if (prices[i] >= st.peek()) {
                st.push(new Integer(prices[i]));
            } else {
                Integer val = st.peek();
                max_gap = Math.max(max_gap, val - min_val);
                min_val = Math.min(min_val, prices[i]);
                while (!st.empty() && prices[i] < st.peek()) {
                    st.pop();
                }
                st.push(new Integer(prices[i]));
            }
        }
        
        Integer val = st.peek();
        max_gap = Math.max(max_gap, val - min_val);
        
        return max_gap;               
    }
}

