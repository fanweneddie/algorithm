#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
 * Problem: find the minimum time difference
 * https://leetcode-cn.com/problems/minimum-time-difference/
 *
 * We just sort the array and find the neighboring gap one by one
 *
 * Time Complexity: O(nlgn), where n is the size of array
 *
 */

const int INF = 99999;

// get the minutes from 00:00 to time_point
int get_minutes(string time_point) {
    return ((time_point[0] - '0') * 10 + (time_point[1] - '0')) * 60
        + (time_point[3] - '0') * 10 + time_point[4] - '0';
}

// get the interval from start_minute to end_minute
// note that this interval <= 12 hours
inline int get_interval(int start_minute, int end_minute) {
    int interval = end_minute - start_minute;
    if (interval > 720) {
        interval = 1440 - interval;
    }
    return interval;
}

int main() {
    vector<string> time_points;
    int size;
    int min_interval = INF;

    // input and init
    cin >> size;
    time_points.resize(size);
    for (int i = 0; i < size; ++i) {
        cin >> time_points[i];
    }

    // sort the time points
    sort(time_points.begin(), time_points.end());

    // get min interval by iterating over the neighboring gap
    int last_minute = get_minutes(time_points[0]);
    int curr_minute;
    for (int i = 1; i < size; ++i) {
        curr_minute = get_minutes(time_points[i]);
        min_interval = min(min_interval, get_interval(last_minute, curr_minute));
        last_minute = curr_minute;
    }

    // check for the first and the last
    last_minute = get_minutes(time_points[0]);
    curr_minute = get_minutes(time_points[size-1]);
    min_interval = min(min_interval, get_interval(last_minute, curr_minute));

    cout << min_interval << endl;
    return 0;
}

