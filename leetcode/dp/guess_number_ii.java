/*
Problem: https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/

Solution: DP
We set dp[m][n] as the least money to guarantee a victory in [m,...,n].
Then we have dp[i][i] = 0, 1 <= i <= n.
dp[i][i+1] = i, 1 <= i < n.
dp[m][n] = min_{m < k < n}(max(dp[m][k-1], dp[k+1][n]) + k)
And finally we return dp[1][n].

Complexity:
	Time: O(n^3)
	Space: O(n^2) 
*/

class Solution {
    public int getMoneyAmount(int n) {
        // dp[m][n] means the least money to guarantee a victory
        // in [m,...,n]
        int[][] dp = new int[n + 1][n + 1];
        
        // boundary
        for (int i = 1; i < n; ++i) {
            dp[i][i] = 0;
            dp[i][i+1] = i;
        }
        dp[n][n] = 0;

        // dynamic programming by using a zigzag traverse
        for (int gap = 2; gap <= n - 1; ++gap) {
            for (int i = 1; i <= n - gap; ++i) {
                int j = i + gap;
                int temp = Integer.MAX_VALUE;
                for (int k = i + 1; k < j; ++k) {
                    temp = Math.min(temp, Math.max(dp[i][k-1], dp[k+1][j]) + k);
                }
                dp[i][j] = temp;
            }
        }
        return dp[1][n];
    }
}
