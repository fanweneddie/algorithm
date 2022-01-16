#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * Problem:
 * Given 3 strings s1, s2 and s3, check whether s3 is an interleaving string
 * of s1 and s2.
 *
 * Solution:
 * We set dp[i][j] as whether s3[0,i+j-1] is an interleaving string of
 * s1[0...i-1] and s2[0...j-1], then we have
 *
 * dp[0][0] = true
 * dp[i][0] = s1[i-1] == s3[i-1] && dp[i-1][0], for 1 <= i <= size1
 * dp[0][j] = s2[j-1] == s3[j-1] && dp[0][j-1], for 1 <= j <= size2
 * dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j]) || (s2[j-1] == s3[i+j-1] && dp[i][j-1]),
 *              for 1 <= i <= size1 and 1 <= j <= size2
 * At last, return dp[size1][size2]
 *
 * Complexity:
 * Time: O(mn)
 * Space: O(mn), where m and n are the size of s1 and s2, respectively.
 */

int main() {
    // three input strings
    string s1, s2, s3;
    // size of those strings
    int size1, size2, size3;
    // dp[i][j] shows whether s3[0,i+j-1] is an interleaving string of
    // s1[0...i-1] and s2[0...j-1],
    vector<vector<bool>> dp;

    // input
    cin >> s1;
    cin >> s2;
    cin >> s3;
    size1 = s1.size();
    size2 = s2.size();
    size3 = s3.size();

    // deal with special case
    if (size3 != size1 + size2) {
        cout << false << endl;
        return 0;
    } else if (size3 == 0) {
        cout << true << endl;
        return 0;
    }

    // init
    dp.resize(size1 + 1);
    for (int i = 0; i <= size1; ++i) {
        dp[i].resize(size2 + 1);
    }

    // dynamic programming
    dp[0][0] = true;
    for (int i = 1; i <= size1; ++i) {
        dp[i][0] = s1[i-1] == s3[i-1] && dp[i-1][0];
    }
    for (int j = 1; j <= size2; ++j) {
        dp[0][j] = s2[j-1] == s3[j-1] && dp[0][j-1];
    }

    for (int i = 1; i <= size1; ++i) {
        for (int j = 1; j <= size2; ++j) {
            dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j]) ||
                        (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
        }
    }

    cout << dp[size1][size2] << endl;
    return 0;
}