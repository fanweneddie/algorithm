#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

/*
 * Problem:
 * given an array, find the top-k max element
 *
 * Solution:
 * Continue to do partition in this array.
 * If the position of pivot element is size - k, then return that pivot element
 *
 * Complexity:
 * Time: if we pick a random pivot during partition, then the expected T(n) = O(n),
 *          (where n is the size of the array)
 * Space: O(1)
 */

// partition nums[low, high] and return the position i of pivot element s.t.
// all elements in nums[low, i-1] <= pivot element and
// all elements in nums[i+1, high] >= pivot element
int partition(int low, int high, vector<int>& nums);

// swap nums[i] and nums[j]
// it is guaranteed that index i and j are valid for nums
inline void swap(int i, int j, vector<int>& nums);

int main() {
    // the input array
    vector<int> nums;
    // size of nums
    int size;
    // k for top-k
    int k;
    // the position of current pivot
    int cur_pos;
    // the final position
    int final_pos;

    // input and init
    cin >> size;
    nums.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }
    cin >> k;
    final_pos = size - k;

    // two bounds for pruning
    int low = 0;
    int high = size - 1;
    // continue to do partition until the current pivot is at the right position
    cur_pos = partition(low, high, nums);
    while (cur_pos != final_pos) {
        if (cur_pos < final_pos) {
            low = cur_pos + 1;
            cur_pos = partition(low, high, nums);
        } else {
            high = cur_pos - 1;
            cur_pos = partition(low, high, nums);
        }
    }

    cout << nums[cur_pos] << endl;
    return 0;
}

inline void swap(int i, int j, vector<int>& nums) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

int partition(int low, int high, vector<int>& nums) {
    // pick a random pivot element
    int pivot_pos = rand() % (high - low + 1) + low;
    swap(pivot_pos, high, nums);
    int pivot = nums[high];

    // do partition by swapping
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (nums[j] < pivot) {
            i++;
            swap(i, j, nums);
        }
    }

    // return the right position of pivot element
    swap(i + 1, high, nums);
    return i + 1;
}