/*
Problem: https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

Solution: dp
we set dp[i][j] to store the min operation for s[i,j].
dp[i][i] = 0 and 
If s[i] = s[i+1], dp[i][i+1] = 0; else dp[i][i+1] = 1.
If s[i] = s[j], then dp[i][j] = dp[i+1][j-1];
else, dp[i][j] = min{dp[i+1][j], dp[i][j-1]} + 1.

Complexity:
	Time: O(n^2)
	Space: O(n^2), where n is the size of string.
*/

class Solution {
public:
    int minInsertions(string s) {
        int size = s.size();
        // dp[i][j] stores the min operation for s[i,j]
        vector<vector<int>> dp;
        dp.resize(size);
        for (int i = 0; i < size; ++i) {
            dp[i].resize(size);
        }
        
        // boundary cases
        for (int i = 0; i < size - 1; ++i) {
            dp[i][i] = 0;
            if (s[i] == s[i+1]) {
                dp[i][i+1] = 0;
            } else {
                dp[i][i+1] = 1;
            }
        }
        dp[size-1][size-1] = 0;

        // dynamic programming
        for (int j = 2; j < size; ++j) {
            for (int i = j - 2; i >= 0; --i) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1];
                } else {
                    dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
                }
            }
        }

        return dp[0][size - 1];
    }
};


