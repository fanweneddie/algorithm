#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
 * Problem:
 * Given k and an array, find the number of subarray whose sum = k
 *
 * Solution:
 * For each prefix subarray [0,...,i], calculate its sum as prefix[i].
 * Use a hashmap to get the number of subarray [0,...,j] (j < i) s.t. prefix[i] - prefix[j] = k
 * Note that numbers in the array can be negative, so sliding window doesn't help
 *
 * Complexity:
 * Time: O(n)
 * Space: O(n), where n is the size of input array
 */

int main() {
    // the input array
    vector<int> nums;
    // size of nums
    int size;
    // the given sum
    int k;
    // freq[i] means the frequency of prefix whose sum = i
    map<int, int> freq;
    // the prefix sum
    int prefix = 0;
    // the total number of subarray whose sum = k
    int total = 0;


    // input
    cin >> size;
    nums.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }
    cin >> k;

    // default
    freq[0] = 1;
    // get prefix sum, count total and record the frequency
    for (int i = 0; i < size; ++i) {
        prefix += nums[i];
        auto iter = freq.find(prefix - k);
        if (iter != freq.end()) {
            total += iter->second;
        }
        iter = freq.find(prefix);
        if (iter != freq.end()) {
            freq[prefix] += 1;
        } else {
            freq[prefix] = 1;
        }
    }

    cout << total << endl;
    return 0;
}