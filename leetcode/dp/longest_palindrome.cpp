#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * Problem:
 * Given a string, find the longest palindrome substring.
 * e.g. str = "babad", return "aba"
 *
 * Solution:
 * We set dp[i][j] to show whether substring str[i...j] is a palindrome.
 * Then, we have
 * dp[i][i] = true
 * dp[i][i+1] = (str[i] == str[i+1])
 * dp[i][j] = dp[i+1][j-1] and (str[i] == str[j])
 *
 * Complexity:
 * time: O(n^2)
 * space: O(n^2), where n is the size of input string
 * (dp makes it more complex than Manacher's method
 */

int main() {
    // the input string
    string str;
    // the size of input string
    int size;
    // dp[i][j] shows whether substring str[i...j] is a palindrome.
    vector<vector<bool>> dp;
    // the length of the longest palindrome substring
    int max_len = -1;
    // starting index of the longest palindrome substring
    int max_start = -1;

    // init
    cin >> str;
    size = str.size();
    dp.resize(size);
    for (int i = 0; i < size; ++i) {
        dp[i].resize(size);
    }

    // dynamic programming
    for (int i = 0; i < size; ++i) {
        dp[i][i] = true;
    }

    for (int i = 0; i < size - 1; ++i) {
        dp[i][i + 1] = str[i] == str[i + 1];
    }

    for (int j = 2; j < size; ++j) {
        for (int i = 0; i < size - j; ++i) {
            dp[i][i + j] = dp[i + 1][i + j - 1] & (str[i] == str[i + j]);
        }
    }

    // get result
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (dp[i][j] && j - i + 1 > max_len) {
                max_start = i;
                max_len = j - i + 1;
            }
        }
    }

    cout << str.substr(max_start, max_len) << endl;
}