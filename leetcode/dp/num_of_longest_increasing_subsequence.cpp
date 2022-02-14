/*
Problem: https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/

Solution: DP
we set dp[i] as the max length of subsequence ending at nums[i],
and cnt[i] as the number of longest subsequence ending at nums[i].

Then we have
dp[0] = 1, cnt[1] = 1.
dp[i] = max{dp[j]} + 1, 0 <= j < i
cnt[i] = sum of cnt[j] where dp[i] = dp[j] + 1, 0 <= j < i.

At last, we get the max length of dp[0...size - 1] = max_len
and return sum{cnt[k]} where dp[k] = max_len.

Complexity:
	Time: O(n^2)
	Space: O(n), where n is the size of input array
*/

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        // dp[i] stores the max length of subsequence ending at nums[i]
        vector<int> dp;
        // cnt[i] stores the number of longest subsequence ending at nums[i]
        vector<int> cnt;
        // the global longest length and its count
        int max_dp = -1;
        int max_cnt = 0;

        // init
        int size = nums.size();
        dp.resize(size);
        cnt.resize(size);
        for (int i = 0; i < size; ++i) {
            dp[i] = 1;
            cnt[i] = 1;
        }

        // dynamic programming
        for (int i = 1; i < size; ++i) {
            int cur_max_len = 1;
            int cur_cnt = 1;
            for (int j = i - 1; j >= 0; --j) {
                if (nums[j] < nums[i]) {
                    if (dp[j] + 1 > cur_max_len) {
                        cur_max_len = dp[j] + 1;
                        cur_cnt = cnt[j];
                    } else if (dp[j] + 1 == cur_max_len) {
                        cur_cnt += cnt[j];
                    }
                }
            }
            // update
            dp[i] = cur_max_len;
            cnt[i] = cur_cnt;
        }

        // count max
        for (int i = 0; i < size; ++i) {
            if (dp[i] > max_dp) {
                max_dp = dp[i];
                max_cnt = cnt[i];
            } else if (dp[i] == max_dp) {
                max_cnt += cnt[i];
            }
        }
        return max_cnt;
    }
};
