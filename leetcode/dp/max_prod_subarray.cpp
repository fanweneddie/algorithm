#include <iostream>
#include <vector>
using namespace std;

/*
 * Problem: https://leetcode-cn.com/problems/maximum-product-subarray/
 * Given an integer array nums[], return the maximum product in any subarray.
 *
 * Solution:
 * We set dp+[i] as the maximum positive product of any subarray that ends at i,
 * and dp-[i] as the minimum negative product of any subarray that ends at i.
 *
 * Then we have,
 * 1. if nums[0] >= 0, then dp+[0] = nums[0] and dp-[0] = 0;
 *    if nums[0] < 0, then dp+[0] = 0 and dp-[0] = nums[0].
 *
 * 2. for 1 <= i < size,
 *      if nums[i] >= 0,
 *          dp+[i] = max{dp+[i-1] * nums[i], nums[i]}
 *          dp-[i] = min{dp-[i-1] * nums[i], 0}
 *      if nums[i] < 0,
 *          dp+[i] = max{dp-[i-1] * nums[i], 0}
 *          dp-[i] = min{dp+[i-1] * nums[i], nums[i]}
 *
 * 3. if size = 0 and nums[0] < 0, then result = nums[0]
 *    else, the result must be non-negative, so result = max{dp+[i]}, 0 <= i < size
 *
 * Complexity:
 * Time: O(n)
 * Space: O(1), where n is the size of array
 */

const int INF = 999999;
int main() {
    // input array
    vector<int> nums;
    // size of input array
    int size;
    // the maximum positive product of any subarray that ends at an odd index
    int dp_pos_oddzz;
    // the maximum positive product of any subarray that ends at an even index
    int dp_pos_even;
    // the minimum negative product of any subarray that ends at an odd index
    int dp_neg_odd;
    // the minimum negative product of any subarray that ends at an even index
    int dp_neg_even;

    // input and init
    cin >> size;
    nums.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }

    // deal with special case
    if (size == 1 && nums[0] < 0) {
        cout << nums[0] << endl;
        return 0;
    }

    // dynamic programming
    if (nums[0] >= 0) {
        dp_pos_even = nums[0];
        dp_neg_even = 0;
    } else {
        dp_pos_even = 0;
        dp_neg_even = nums[0];
    };

    int max_prod = -INF;
    for (int i = 1; i < size; ++i) {
        if (nums[i] >= 0) {
            if (i % 2 == 1) {
                dp_pos_odd = max(dp_pos_even * nums[i], nums[i]);
                dp_neg_odd = min(dp_neg_even * nums[i], 0);
                max_prod = max(max_prod, dp_pos_odd);
            } else {
                dp_pos_even = max(dp_pos_odd * nums[i], nums[i]);
                dp_neg_even = min(dp_neg_odd * nums[i], 0);
                max_prod = max(max_prod, dp_pos_even);
            }
        } else {
            if (i % 2 == 1) {
                dp_pos_odd = max(dp_neg_even * nums[i], 0);
                dp_neg_odd = min(dp_pos_even * nums[i], nums[i]);
                max_prod = max(max_prod, dp_pos_odd);
            } else {
                dp_pos_even = max(dp_neg_odd * nums[i], 0);
                dp_neg_even = min(dp_pos_odd * nums[i], nums[i]);
                max_prod = max(max_prod, dp_pos_even);
            }
        }
    }

    cout << max_prod << endl;
    return 0;
}