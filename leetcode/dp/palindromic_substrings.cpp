/*
Problem: https://leetcode-cn.com/problems/palindromic-substrings/

Solution: Manacher

Complexity:
	Time: O(n)
	Space: o(n), where n is the size of string
*/

class Solution {
public:
    // Manacher's algorithm
    int countSubstrings(string s) {
        string ss = preprocess(s);
        int size = ss.size();
        // dp[i] stores the max radius of palindromic string centering at i
        vector<int> dp;
        dp.resize(size);
        int center = 0;
        int right = 0;
        int cnt = 0;

        for (int i = 0; i < size; ++i) {
            // mirrored i on center
            int i_mr = 2*center - i;
            if (right > i) {
                dp[i] = min(right - i, dp[i_mr]);
            } else {
                dp[i] = 0;
            }

            // do out searching
            while (isEqual(i + dp[i] + 1, i - dp[i] - 1, ss)) {
                dp[i]++;
            }

            // update center and right
            if (i + dp[i] > right) {
                center = i;
                right = center + dp[center];
            }

            // count the number of palindromic substrings
            if (dp[i] > 0) {
                cnt += (dp[i] + 1)/2;
            }
        }

        return cnt;
    }

    string preprocess(string s) {
        string result;
        result.push_back('#');
        int size = s.size();
        for (int i = 0; i < size; ++i) {
            result.push_back(s[i]);
            result.push_back('#');
        }
        return result;
    }

    bool isEqual(int index1, int index2, const string& s) {
        int size = s.size();
        if (index1 < 0 || index1 > size || index2 < 0 || index2 > size) {
            return false;
        } else {
            return s[index1] == s[index2];
        }
    }
};
