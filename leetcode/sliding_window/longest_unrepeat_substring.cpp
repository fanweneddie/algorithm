#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
 * Problem:
 * given a string, return the longest substring that does not
 * contain a repeated character.
 *
 * Solution:
 * Sliding window. If the new char is not in current window, expand the window to right;
 * Else, let it starts next to the position of char found.
 * We record the max length of window during this process
 *
 * Complexity:
 * Time: O(n)
 * Space: O(n)
 */

int main() {
    // the input string
    string str;
    // left and right boundary of the sliding window
    int left = 0;
    int right = 0;
    // the maximum length of the window
    int max_len = 0;
    // maps char to its location in the current window
    map<char, int> hashmap;

    // input
    cin >> str;

    // sliding window
    int size = str.size();
    // if size = 0, then max_len = 0
    for (int i = 0; i < size; ++i) {
        char c = str[i];
        auto iter = hashmap.find(c);
        // not found, expand this window to right
        if (iter == hashmap.end() || iter->second < left) {
            right = i;
            hashmap[c] = i;
            if (right - left + 1 > max_len) {
                max_len = right - left + 1;
            }
        }
        // found, let the new window start at next position of that char in the window
        // we use [] to overwrite
        else {
            left = iter->second + 1;
            right = i;
            hashmap[c] = i;
        }
    }

    // output result
    cout << max_len << endl;
}