#include <iostream>
#include <vector>
using namespace std;

/*
 * Problem: given a non-neg integer array, each element is the maximum step that you can jump
 * from that location. Output whether we can go to the last position.
 * e.g. nums = [2,3,1,1,4], we can go to the last position by 0 -> 1 -> 4
 *
 * Solution:
 * We set dp[i] as the longest position that can be reached from any position in [0...i],
 * then we have
 * dp[0] = nums[0],
 * dp[i] = max{dp[i-1], i + num[i]}, if dp[i-1] >= i
 *       otherwise, we cannot jump to the end
 * And if dp[n-1] >= n-1, return true; otherwise, return false. (where n is the size of nums)
 *
 * Complexity:
 * Time: O(n)
 * Space: O(1), where n is the size of nums
 */
int main() {
    // the input array
    vector<int> nums;
    // the size of nums
    int size;
    // dp[i] is the longest position that can be reached from any position in [0...i]
    // we just use a variable to save memory
    int dp;
    // whether the last position can be reached
    bool result = false;

    // input
    cin >> size;
    nums.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }

    // dynamic programming
    dp = nums[0];
    for (int i = 1; i < size; ++i) {
        if (dp >= i) {
            dp = max(dp, i + nums[i]);
        } else {
            result = false;
            break;
        }
    }

    if (dp >= size - 1) {
        result = true;
    }
    cout << result << endl;
    return 0;
}