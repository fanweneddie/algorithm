#include <iostream>
#include <vector>
using namespace std;

/*
 * Problem: Given a triangle, a point at (i,j) can only move to (i+1,j) or (i+1,j+1),
 * and we need to find the distance of the shortest path from top to bottom.
 * e.g. the triangle is
 * 2
 * 3 4
 * 6 5 7
 * 4 1 8 3
 * And the shortest path is 2->3->5->1
 *
 * Solution:
 * set value[i][j] is the value of each point
 * set dp[i][j] is the distance of the shortest path from top (0,0) to (i,j)
 * then
 * dp[0][0] = value[0][0]
 * dp[i][0] = dp[i-1][0] + value[i][0], where i > 0
 * dp[i][j] = min{dp[i-1][j], dp[i-1][j-1]} + value[i][j], where i > 0 and 0 < j < i
 * dp[i][i] = dp[i-1][i-1] + value[i][i], where i > 0
 * And return min{dp[height-1][j]}
 *
 * Complexity:
 *  Time: O(n^2)
 *  Space: O(n^2), where n is the height of triangle
 */
const int INF = 99999999;
int min_value(int a, int b);

int main() {
    // the value of each point in the triangle
    vector<vector<int>> value = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    // the distance of the shortest path from top (0,0) to (i,j)
    vector<vector<int>> dp;
    // the height of the triangle
    int height = value.size();

    // init dp
    dp.resize(height);
    for (int i = 0; i < height; ++i) {
        dp[i].resize(i + 1);
    }

    // dynamic programming
    dp[0][0] = value[0][0];
    for (int i = 1; i < height; ++i) {
        dp[i][0] = dp[i - 1][0] + value[i][0];
        for (int j = 1; j < i; ++j) {
            dp[i][j] = min_value(dp[i - 1][j], dp[i - 1][j - 1]) + value[i][j];
        }
        dp[i][i] = dp[i - 1][i - 1] + value[i][i];
    }

    // find the minimum value in dp[height-1]
    int min = INF;
    for (int j = 0; j < height; ++j) {
        if (dp[height - 1][j] < min) {
            min = dp[height - 1][j];
        }
    }

    cout << min << endl;
}

int min_value(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}