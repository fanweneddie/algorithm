/*
Problem: https://leetcode-cn.com/problems/integer-break/

Solution: top-down dynamic programming
We set dp[i] as the max product of integer i after decomposition.
Obviously, dp[1] = 1.
For i > 0, we can decompose i into j and i - j, where 1 <= j < i.
Then, we fix j and we can choose to decompose i - j or not.
So the current max product is max{j*(i-j), j*dp[i-j]},
and dp[i] = max{max{j*(i-j), j*dp[i-j]}}, where 1 <= j < i.

Complexity:
	Time: O(n^2),
	Space: O(n), where n is the given integer.

*/

class Solution {
public:
    int integerBreak(int n) {
        // dp[i] is the max product of integer i (after decomposition)
        vector<int> dp;
        // flag[i] marks whether dp[i] has been calculated
        vector<bool> flag;
        dp.resize(n + 1);
        flag.resize(n + 1);
        // init
        dp[1] = 1;
        flag[1] = true;
        return getMaxProduct(n, dp, flag);
    }

    // Calculate dp[i]
    int getMaxProduct(int i, vector<int>& dp, vector<bool>& flag) {
        if (flag[i]) {
            return dp[i];
        }
        // top-down dynamic programming
        int cur_max = 0;
        for (int j = 1; j < i; ++j) {
            int temp = max(j*(i-j), j*getMaxProduct(i-j, dp, flag));
            cur_max = max(cur_max, temp);
        }
        // record dp[i]
        dp[i] = cur_max;
        flag[i] = true;
        return dp[i];
    }
};
