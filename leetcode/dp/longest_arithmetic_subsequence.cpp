/*
Problem: https://leetcode-cn.com/problems/longest-arithmetic-subsequence/

Solution: dynamic programming
We set dp[i][d] stores the max length of arithmetic subsequence that ends at nums[i] with gap d.
1. We init dp[i][d] = 1
2. dp[i][d] = max{dp[i][d],dp[j][d]+1}, where d = nums[i] - nums[j]

Complexity:
Time: O(n^2)
Space: O(nd), where n is the length of nums and d is the max gap
*/
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        // dp[i][d] stores the max length of arithmetic subsequence
        // that ends at nums[i] with gap d
        vector<vector<int>> dp;
        // max length of arithmetic subsequence
        int result = 1;
        const int MAX_POS_GAP = 500; 

        // init
        int size = nums.size();
        dp.resize(size);
        for (int i = 0; i < size; ++i) {
            dp[i].resize(MAX_POS_GAP*2 + 1);
        }
        for (int i = 0; i < size; ++i) {
            for (int d = 0; d <= MAX_POS_GAP*2; ++d) {
                dp[i][d] = 1;
            }
        }

        // dynamic programming
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < i; ++j) {
                int d = nums[i] - nums[j];
                dp[i][d+MAX_POS_GAP] = max(dp[i][d+MAX_POS_GAP], dp[j][d+MAX_POS_GAP] + 1);
                result = max(result, dp[i][d+MAX_POS_GAP]);
            }
        }

        return result;
    }
};
