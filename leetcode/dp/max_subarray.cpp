#include <iostream>
#include <vector>
using namespace std;

/*
 * Problem: given an array of integer, return the maximum sum of a consecutive subarray
 * e.g. nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4], then the max sum is 6 for [4, -1, 2, 1]
 *
 * Solution:
 * We set dp[i] as the maximum sum of consecutive subarray in nums[0...i]
 * and that subarray must end with nums[i].
 * Then we have
 *      dp[0] = nums[0]
 *      dp[i] = max{dp[i-1] + nums[i], nums[i]}, where i > 0
 * Finally, answer = max{dp[i]}
 *
 * Complexity:
 * time: O(n)
 * space: O(n) where n is the size of input array
 */

const int INF = 99999;

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    // the size of input array
    int size;
    // the input array of integers
    vector<int> nums;
    // dp[i] stores the maximum sum of consecutive subarray in nums[0...i]
    // and that subarray must end with nums[i].
    vector<int> dp;
    int result = -INF;

    // init
    cin >> size;
    nums.resize(size);
    dp.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }

    // dynamic programming
    dp[0] = nums[0];
    for (int i = 1; i < size; ++i) {
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
    }

    for (int i = 0; i < size; ++i) {
        if (dp[i] > result) {
            result = dp[i];
        }
    }

    cout << result << endl;
}