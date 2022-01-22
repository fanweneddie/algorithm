/*
Problem: https://leetcode-cn.com/problems/longest-palindromic-subsequence/

Solution: DP

Complexity:
Time: O(n^2)
Space: O(n^2), where n is the length of input string
*/

class Solution1 {
public:
    int longestPalindromeSubseq(string s) {
        // dp[i][j] is the length of longest palindrome subsequence in s[i,...,j]
        vector<vector<int>> dp;
        int size = s.size();
        dp.resize(size);
        for (int i = 0; i < size; ++i) {
            dp[i].resize(size);
        }

        // dynamic programming
        // 1. init dp[i][i] and dp[i][i+1]
        for (int i = 0; i < size - 1; ++i) {
            dp[i][i] = 1;
            if (s[i] == s[i+1]) {
                dp[i][i+1] = 2;
            } else {
                dp[i][i+1] = 1;
            }
        }
        dp[size-1][size-1] = 1;

        // 3. k denotes the length of substring
        for (int k = 2; k < size; ++k) {
            for (int i = 0; i < size - k; ++i) {
                int j = i + k;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }

        return dp[0][size-1];
    }
};

// This is the optimized version. It reduces the cost of memory, but with a higher complexity
class Solution2 {
public:
    int longestPalindromeSubseq(string s) {
        // dp[i][j] is the length of longest palindrome subsequence in s[i,...,j]
        vector<vector<int>> dp;
        int size = s.size();
        dp.resize(size);
        for (int i = 0; i < size; ++i) {
            dp[i].resize(size - i);
        }

        // dynamic programming
        // 1. init dp[i][i] and dp[i][i+1]
        for (int i = 0; i < size - 1; ++i) {
            dp[i][0] = 1;
            if (s[i] == s[i+1]) {
                dp[i][1] = 2;
            } else {
                dp[i][1] = 1;
            }
        }
        dp[size-1][0] = 1;

        // 3. k denotes the length of substring
        for (int k = 2; k < size; ++k) {
            for (int i = 0; i < size - k; ++i) {
                if (s[i] == s[i+k]) {
                    dp[i][k] = dp[i+1][k-2] + 2;
                } else {
                    dp[i][k] = max(dp[i+1][k-1], dp[i][k-1]);
                }
            }
        }

        return dp[0][size-1];
    }
};

