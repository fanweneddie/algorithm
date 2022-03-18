/*
Problem: https://leetcode-cn.com/problems/2-keys-keyboard/

Solution: DP
we set dp[i] as the minimum number of operations to get i number of As.
for all j as a factor of i, we have dp[i] = min{dp[j], i/j}.
Also, dp[1] is initialized as 0.

We only need to calculate dp[i] where i is the factor of n.
Also, when calculating dp[i], we don't need to traverse from 1 to i to get i's factors;
Instead, we can traverse from 1 to sqrt(i) to get all PAIRS of factors.

Complexity:
	Time: O(nsqrt(n))
	Space: O(n)
*/


class Solution {
public:
    int minSteps(int n) {
        const int INFI = 99999;
        // dp[i] means the minimum number of operations to get i As
        vector<int> dp;
        dp.resize(n + 1);

        // dynamic programming
        dp[1] = 0;
        for (int i = 2; i <= n; ++i) {
            if (n % i != 0) {
                continue;
            }
            dp[i] = INFI;
            int top = (int) sqrt(i);
            for (int j = 1; j <= top; ++j) {
                if (i % j == 0) {
                    dp[i] = min(dp[i], dp[j] + i / j);
                    dp[i] = min(dp[i], dp[i/j] + j);
                }
            }
        }
        return dp[n];
    }
};
