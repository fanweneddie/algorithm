#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
 * Problem: longest common subsequence (LCS) of two texts: t1 and t2
 *
 * Solution:
 * We set dp[i][j] as the length of LCS of t1[0...i] and t2[0...j],
 * then we have
 * dp[0][0] = (t1[0] == t2[0])
 * dp[0][j] = dp[0][j-1] or (t1[0] == t2[j]), where 1 <= j < t2.size
 * dp[i][0] = dp[i-1][0] or (t1[i] == t2[0]), where i <= i < t1.size
 * dp[i][j] = max{dp[i][j-1], dp[i-1][j]}, if t1[i] != t2[j]
 *          = dp[i-1][j-1] + 1, if t1[i] == t2[j]
 *          (where i <= i < t1.size and 1 <= j < t2.size)
 * and the result is dp[t1.size-1][t2.size-1]
 *
 * Complexity:
 * time: O(n^2)
 * space: O(n^2), where n is the length of texts
 */

int main() {
    // two input strings
    string text1;
    string text2;
    // dp[i][j] stores the length of LCS of t1[0...i] and t2[0...j]
    vector<vector<int>> dp;

    // input
    cin >> text1;
    cin >> text2;

    // init dp
    int text1_size = text1.size();
    int text2_size = text2.size();
    // deal with special case
    if (text1_size * text2_size == 0) {
        cout << 0 << endl;
        return 0;
    } else {
        dp.resize(text1_size);
        for (int i = 0; i < text1_size; ++i) {
            dp[i].resize(text2_size);
        }
    }

    // dynamic programming
    // 1. dp[0][0]
    if (text1[0] == text2[0]) {
        dp[0][0] = 1;
    } else {
        dp[0][0] = 0;
    }
    // 2. dp[0][j]
    for (int j = 1; j < text2_size; ++j) {
        if (dp[0][j-1] || (text1[0] == text2[j])) {
            dp[0][j] = 1;
        } else {
            dp[0][j] = 0;
        }
    }
    // 3. dp[i][0]
    for (int i = 1; i < text1_size; ++i) {
        if (dp[i-1][0] || (text1[i] == text2[0])) {
            dp[i][0] = 1;
        } else {
            dp[i][0] = 0;
        }
    }
    // 4. dp[i][j]
    for (int i = 1; i < text1_size; ++i) {
        for (int j = 1; j < text2_size; ++j) {
            if (text1[i] == text2[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    // show result
    cout << dp[text1_size-1][text2_size-1] << endl;
    return 0;
}