#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/*
 * Problem:
 * Given an array arr, find the length of the shortest consecutive subarray a s.t.
 * if a is sorted, then arr is sorted.
 * e.g. arr = [2, 6, 4, 8, 10, 9, 15], then a = [6, 4, 8, 10, 9] and len = 5
 *
 * Solution:
 * Use a stack to record the starting index of the last element that doesn't
 * need to be sorted. If the elements after it is not sorted, then those elements should be sorted
 *
 * Complexity:
 * time: O(n)
 * space: O(n)
 */

const int INF = 999999;

int main() {
    // the input array of integers
    vector<int> arr;
    // the size of input array
    int size;
    // the stack to store the sorted elements
    stack<int> s;
    // the max unsorted element
    int unsorted_max = -INF;
    // the number of unsorted elements
    int unsorted_num = 0;
    // whether the subarray of arr needs to be sorted
    bool need_sort = false;
    // the stack position of the last element that does not need to be sorted
    int last_unsort_index = -1;

    // input
    cin >> size;
    arr.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    // use stack to solve
    unsorted_max = arr[0];
    for (int i = 0; i < size; ++i) {
        // 1. arr[i] can make the current subarray sorted, just add it
        if (arr[i] >= unsorted_max) {
            s.push(arr[i]);
            unsorted_max = arr[i];
        }
        // 2. first time to sort, record the position of the last unsorted element
        else if (!need_sort) {
            need_sort = true;
            unsorted_num++;
            while (!s.empty() && s.top() > arr[i]) {
                s.pop();
                unsorted_num++;
            }
            last_unsort_index = s.size();
        }
        // 2. have sorted, so just sort the elements after last_unsort_index
        else {
            unsorted_num++;
            while (s.size() > last_unsort_index) {
                s.pop();
                unsorted_num++;
            }
            while (!s.empty() && s.top() > arr[i]) {
                s.pop();
                unsorted_num++;
            }
        }
    }

    cout << unsorted_num << endl;
}