#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// right-shift the left pointer in nums
inline int right_shift(int left, int right, const vector<int> & nums) {
    int current = nums[left];
    while (left <= right && nums[left] == current) {
        left++;
    }
    return left;
}

// left-shift the right pointer in nums
inline int left_shift(int right, int left, const vector<int> & nums) {
    int current = nums[right];
    while (left <= right && nums[right] == current) {
        right--;
    }
    return right;
}

int main() {
    // the input array
    vector<int> nums;
    // size of the array
    int size;
    // stores the sub-triple whose sum = 0
    vector<vector<int>> results;
    // left and right pointers
    int left;
    int right;

    // input
    cin >> size;
    nums.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }

    if (size < 3) {
        cout << "[]" << endl;
        return 0;
    }

    sort(nums.begin(), nums.end());

    // do double pointer
    int i = 0;
    while (i < size) {
        if (nums[i] > 0) {
            break;
        }

        left = i + 1;
        right = size - 1;
        while (left < right) {
            int temp = nums[i] + nums[left] + nums[right];
            // right-shift the left pointer
            if (temp < 0) {
               left = right_shift(left, right, nums);
            }
            // left-shift the right pointer
            else if (temp > 0) {
                right = left_shift(right, left, nums);
            }
            // record the result, right-shift left pointer and
            // left-shift right pointer
            else {
                results.push_back({nums[i], nums[left], nums[right]});
                left = right_shift(left, right, nums);
                right = left_shift(right, left, nums);
            }
        }

        i = right_shift(i, size - 1, nums);
    }

    // show results
    int results_size = results.size();
    for (int i = 0; i < results_size; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << results[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}