/*
Problem: https://leetcode-cn.com/problems/egg-drop-with-2-eggs-and-n-floors/

Solution 1:
Suppose we first drop the egg at k-th floor. Now the worst times is k
For next drop, to make the worst times is also k, we should make the gap as k-1,
and so on (until the gap is 1).
So we have 1 + 2 + ... + k >= n => k >= sqrt(2n + 1/4) - 1/2

Complexity 1:
Time: O(1)
Space O(1)

Solution 2: dynamic programming
We set dp[i] as the minimum number of operations (in the worst case) for floor i
To solve dp[i], if we first drop the egg on floor j (1 <= j < i),
then we have dp[i] = max{j, dp[i-j]}.
Of course, considering all j, we have dp[i] = min_j{max{j, dp[i-j]}}, 1 <= j < i.
At last, we return dp[n]

Complexity 2:
Time: O(n^2)
Space: O(n), where n is the floor.
*/

class Solution1 {
public:
    int twoEggDrop(int n) {
        return ceil(sqrt(2*n + 0.25) - 0.5);
    }
};

class Solution2 {
public:
    const int INF = 9999;
    int twoEggDrop(int n) {
        // dp[i] stores the min number of operations (in the worst case) for floor i
        vector<int> dp;
        // init
        dp.resize(n+1);
        for (int i = 1; i <= n; ++i) {
            dp[i] = INF;
        }
        // dynamic programming
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = i - 1; j >= 1; --j) {
                dp[i] = min(dp[i], max(j, dp[i-j] + 1));
            }
        }

        return dp[n];
    }
};
