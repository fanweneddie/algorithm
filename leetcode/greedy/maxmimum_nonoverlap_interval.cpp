#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * Problem: https://leetcode-cn.com/problems/non-overlapping-intervals/
 *
 * Solution: Greedy.
 * First sort the intervals based on their ending time,
 * then pick the intervals from left to right
 *
 * Complexity:
 * Time: O(nlgn)
 * Space: O(1), where n is the number of intervals
 */

// Sort ascendingly based on ending time
bool myComp(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

class Solution {
public:
    const int INF = 99999;

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // the number of intervals
        int size = intervals.size();
        // the maximum number of non-overlapping intervals
        int num = 0;
        // the current ending time
        int cur_end = -INF;

        // sort according to the ending time of each interval
        sort(intervals.begin(), intervals.end(), myComp);

        // pick proper time from left to right greedily
        for (int i = 0; i < size; ++i) {
            if (intervals[i][0] >= cur_end) {
                num++;
                cur_end = intervals[i][1];
            }
        }

        // get the number of intervals that should be removed
        return size - num;
    }
}