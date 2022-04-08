/*
Problem: https://leetcode-cn.com/problems/maximum-length-of-pair-chain/

Solution: dynamic programming

We first sort pairs with ascending order of first number.
We set dp[i] as the max length of chain that ends at pairs[i].
Then, dp[0] = 1,
and dp[i] = max(1, max{dp[j] + 1}), where 0 < j < i and pairs[j][1] < pairs[i][0].
At last, we get max{dp[i]} where 0 <= i < n as the result.

Complexity:
	Time: O(n^2)
	Space: O(n), where n is the size of pairs.
*/

class Solution {
    public int findLongestChain(int[][] pairs) {
        int length = pairs.length;
        // sort the pairs with ascending order of first number
        Arrays.sort(pairs, Comparator.comparingInt(pair -> pair[0]));
        // dp[i] marks the max length of chain that ends at pairs[i]
        int[] dp = new int[length];
        // dynamic programming
        dp[0] = 1;
        for (int i = 1; i < length; ++i) {
            int temp = 1;
            for (int j = 0; j < i; ++j) {
                if (pairs[j][1] < pairs[i][0]) {
                    temp = Math.max(temp, dp[j] + 1);
                }
            }
            dp[i] = temp;
        }

        // get max{dp[i]}
        int max_len = 0;
        for (int i = 0; i < length; ++i) {
            max_len = Math.max(max_len, dp[i]);
        }
        return max_len;
    }
}
