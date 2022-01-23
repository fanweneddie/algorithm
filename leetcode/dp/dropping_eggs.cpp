/*
Problem: https://leetcode-cn.com/problems/super-egg-drop/

Solution:
We set dp[i][k] as the minimum number of operations
(in the worst case) for floor i with at most k eggs.

Then obviously we have dp[i][1] = i for one coin and dp[1][m] = 1 for first floor
dp[i][m] = min_j{max(dp[j-1][m-1], dp[i-j][m])}, where 1 <= j < i.
And finally we return dp[n][k]

What's more, when getting min_j{max(dp[j-1][m-1], dp[i-j][m])},
we use binary search to accelerate.
Since dp[i][m] is ascending by i, 
so dp[j-1][m-1] is ascending by j and dp[i-j][m] is descending by j.
Therefore, we can get the last j0 s.t. dp[j0-1][m-1] <= dp[i-j0][m] and dp[j0+1 - 1][m-1] >= dp[i - j0-1][m],
and the proper j = min(dp[i-j0][m], dp[j0+1 - 1][m-1])

Complexity:
Time: O(knlgn)
Space: O(kn), where k is the number of eggs and n is the level of floors.
*/


class Solution {
public:
    // dp[i][k] stores the minimum number of operations 
    // (in the worst case) for floor i with at most k eggs.
    vector<vector<int>> dp;
    
    // Binary get min_j{max(dp[j-1][m-1], dp[i-j][m])}, where 1 <= j < i
    int binary_get_min(int i, int m) {
        int start = 0;
        int end = i - 1;
        int mid;
        while (start < end) {
            mid = (start + end + 1) / 2;
            if (dp[mid-1][m-1] < dp[i-mid][m]) {
                start = mid;
            } else if (dp[mid-1][m-1] > dp[i-mid][m]) {
                end = mid - 1;
            } else {
                break;
            }
        }
        // fix bug
        if (start == end) {
            mid = start;
        }
        return min(dp[i-mid][m], dp[mid][m-1]);
    }
    
    int superEggDrop(int k, int n) {
        // init
        dp.resize(n+1);
        for (int i = 0; i <= n; ++i) {
            dp[i].resize(k+1);
        }
        for (int m = 0; m <= k; ++m) {
            dp[0][m] = 0;
        }
    
        // dynamic programming
        // case 1: one coin
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = i;
        }
        // case 2： one floor
        for (int m = 1; m <= k; ++m) {
            dp[1][m] = 1;
        }
        // state transformation
        for (int i = 2; i <= n; ++i) {
            for (int m = 2; m <= k; ++m) {
                dp[i][m] = binary_get_min(i, m) + 1;
            }
        }

        return dp[n][k];
    }
};
