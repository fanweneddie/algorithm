#include <iostream>
#include <vector>
using namespace std;

/*
 * Problem:
 * Binary Search in a rotated-sorted-array (partially-sorted)
 * https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
 *
 * Time Complexity: O(lgn), where n is the size of array
 */

// binary search whether ele is in nums[start,end]
// If in, return its index; Else, return -1.
int binary_search(int start, int end, vector<int> &nums, int ele) {
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (nums[mid] < ele) {
            start = mid + 1;
        } else if (nums[mid] > ele) {
            end = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int main() {
    vector<int> nums;
    int size;
    int target;

    // input and init
    cin >> size;
    nums.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }
    cin >> target;

    // find the index of last element in the first ascending segment
    int left = 0;
    int right = size - 1;
    int mid = (left + right) / 2;

    while (mid != left && mid != right) {
        if (nums[mid] > nums[right]) {
            left = mid;
        } else if (nums[mid] < nums[left]) {
            right = mid;
        } else {
            mid = right;
            break;
        }
        mid = (left + right) / 2;
    }

    int ans1 = binary_search(0, mid, nums, target);
    int ans2 = binary_search(mid + 1, size - 1, nums, target);
    int ans = -1;
    if (ans1 != -1) {
        ans = ans1;
    }
    if (ans2 != -1) {
        ans = ans2;
    }

    cout << ans << endl;
    return 0;
}