#include <iostream>
using namespace std;

/*
 * Problem:
 * Given n as the size of a Binary Sorting Tree,
 * Output the number of types of BSTs
 *
 * Solution:
 * set dp[i] as the number of BST types containing i nodes.
 * dp[0] = 1
 * dp[i] = sum_{j=0}^{i} dp[j]*dp[i-j]
 *
 * Complexity:
 *  time: O(n^2)
 *  space: O(n)
 */

int main() {
    // number of nodes
    int n;
    cin >> n;
    // dp[i] as the number of BST types containing i nodes.
    int* dp = new int[n + 1];
    // dynamic programming
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        dp[i + 1] = 0;
        for (int j = 0; j <= i; ++j) {
            dp[i + 1] += dp[j] * dp[i - j];
        }
    }
    // output
    cout << dp[n] << endl;
    delete [] dp;
}