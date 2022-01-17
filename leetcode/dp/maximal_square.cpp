#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

/*
 * Problem:
 * Given a 0/1 matrix, find the area of the largest square that only contains 1s
 *
 * Solution:
 * We set dp[i][j] to store the largest length of 1-square that contains matrix[i][j]
 * Then we have
 * dp[i][0] = matrix[i][0], where 0 <= i < row;
 * dp[0][j] = matrix[0][j], where 0 <= j < col;
 * dp[i][j] = min{dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1,
 *          where 0 < i < row and 0 < j < col.
 * Finally, we return dp[row-1][col-1] as the result.
 *
 * Complexity:
 * Time: O(mn)
 * Space: O(n), where m is row and n is column of the matrix
 */

int get_min(int a, int b, int c) {
    return min(min(a, b),c);
}

int main() {
    // the row and column of the input 0/1 matrix
    int row, col;
    vector<vector<char>> matrix;
    // dp[j] stores the largest length of 1-square that contains matrix[i][j]
    vector<int> dp;
    int max_len = 0;

    // input and init
    cin >> row >> col;
    matrix.resize(row);
    dp.resize(col);
    for (int i = 0; i < row; ++i) {
        matrix[i].resize(col);
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> matrix[i][j];
        }
    }

    // dynamic programming
    for (int j = 0; j < col; ++j) {
        if (matrix[0][j] == '1') {
            dp[j] = 1;
            max_len = max(max_len, dp[j]);
        } else {
            dp[j] = 0;
        }
    }

    // temp value for dp[i-1][j-1]
    int temp1, temp2;
    for (int i = 1; i < row; ++i) {
        // j = 0
        temp1 = dp[0];
        if (matrix[i][0] == '1') {
            dp[0] = 1;
            max_len = max(max_len, dp[0]);
        } else {
            dp[0] = 0;
        }
        // j > 0, temp = dp[i-1][j-1]
        for (int j = 1; j < col; ++j) {
            temp2 = dp[j];
            if (matrix[i][j] == '1') {
                dp[j] = get_min(temp1, dp[j-1], dp[j]) + 1;
                max_len = max(max_len, dp[j]);
            } else {
                dp[j] = 0;
            }
            temp1 = temp2;
        }
    }

    // show result
    cout << max_len * max_len << endl;
    return 0;
}