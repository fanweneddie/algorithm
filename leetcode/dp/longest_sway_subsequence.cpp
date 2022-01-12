#include <iostream>
#include <vector>
using namespace std;

/*
 * Problem:
 * Given an integer array arr, return the length of the longest subsequence
 * that satisfies swaying sequence.
 *
 * Solution:
 * We set up[i] to store the length of the longest swaying-up subsequence in arr[0...i],
 * and down[i] to store the length of the longest swaying-down subsequence in arr[0...i].
 * Here swaying-up subsequence is a swaying subsequence whose ending element >= starting element,
 * and swaying-down subsequence is a swaying subsequence whose ending element <= starting element.
 *
 * We use dynamic programming.
 *
 *
 * Complexity:
 * Time: O(n)
 * Space: O(1), where n is the size of input array
 */

int main() {
    // the input array
    vector<int> arr;
    // the size of arr
    int size;
    // stores the length of the longest swaying-up subsequence in arr[0...i],
    // where i is an odd number
    int up_odd;
    // stores the length of the longest swaying-up subsequence in arr[0...i],
    // where i is an even number
    int up_even;
    // stores the length of the longest swaying-down subsequence in arr[0...i],
    // where i is an odd number
    int down_odd;
    // stores the length of the longest swaying-down subsequence in arr[0...i],
    // where i is an even number
    int down_even;

    // input
    cin >> size;
    arr.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    // dynamic programming
    // 1. init up[0] = down[0] = 1
    up_even = 1;
    down_even = 1;

    // 2. cross update up[i] and down[i]
    for (int i = 1; i < size; ++i) {
        // 2.1 update up[i]
        // 2.1.1 up[i] = up[i-1]
        if (arr[i - 1] <= arr[i]) {
            if (i % 2 == 1) {
                up_odd = up_even;
            } else {
                up_even = up_odd;
            }
        }
        // 2.1.2 up[i] = max{up[i-1], down[i-1] + 1}
        else {
            if (i % 2 == 1) {
                up_odd = max(up_even, down_even + 1);
            } else {
                up_even = max(up_odd, down_odd + 1);
            }
        }

        // 2.2 update down[i], symmetrical to above
        // 2.2.1 down[i] = down[i-1]
        if (arr[i-1] >= arr[i]) {
            if (i % 2 == 1) {
                down_odd = down_even;
            } else {
                down_even = down_odd;
            }
        }
        // 2.2.2 down[i] = max{down[i-1], up[i-1] + 1}
        else {
            if (i % 2 == 1) {
                down_odd = max(down_even, up_even + 1);
            } else {
                down_even = max(down_odd, up_odd + 1);
            }
        }
    }

    // return result = max{up[size-1], down[size-1]}
    int result;
    if ((size - 1) % 2 == 1) {
        result = max(up_odd, down_odd);
    } else {
        result = max(up_even, down_even);
    }

    cout << result << endl;
    return 0;
}