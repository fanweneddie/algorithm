#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
 * Problem:
 * Given an int array nums[], return top k frequent elements.
 *
 * Solution:
 * 1. Count the frequency of each element in nums
 * 2. For each element, push <frequency, element> into bucket
 * 3. Iterate over bucket reversely and get top-k results
 *
 * Complexity:
 * Time: O(n)
 * Space: O(n), where n is the size of nums
 *
 * But actually, the real execution is not ideal,
 * since we have to iterate over nums for many times.
 */

int main() {
    // input array
    vector<int> nums;
    // size of nums
    int size;
    // k of top-k frequent elements
    int k;
    // freq[i] means the frequency of element i
    map<int, int> freq;
    // bucket[i] is a list of elements whose frequency is i
    vector<vector<int>> bucket;
    // stores top-k frequent elements
    vector<int> results;

    // input and init
    cin >> size;
    nums.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
    }
    cin >> k;
    bucket.resize(size + 1);

    // count the frequency of each element
    for (int i = 0; i < size; ++i) {
        if (freq.find(nums[i]) == freq.end()) {
            freq[nums[i]] = 1;
        } else {
            freq[nums[i]]++;
        }
    }

    // push <frequency, element> into bucket
    for (auto it = freq.begin(); it != freq.end(); ++it) {
        bucket[it->second].push_back(it->first);
    }

    // iterate over bucket reversely and get top-k results
    for (int i = size; i > 0 && k > 0; --i) {
        if (bucket[i].size() > 0) {
            int bucket_size = bucket[i].size();
            for (int j = 0; j < bucket_size && k > 0; ++j) {
                results.push_back(bucket[i][j]);
                k--;
            }
        }
    }

    // show results
    for (int i = 0; i < results.size(); ++i) {
        cout << results[i] << " ";
    }
    cout << endl;
    return 0;
}