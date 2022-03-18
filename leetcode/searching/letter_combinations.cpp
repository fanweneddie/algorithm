/*
Problem: https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/

Solution: using hashmap to record the set of letters of a digit, do searching and backtracking

Complexity: 
	Time: O(3^m * 4^n), where m is the number of digits having 3 letters and n is the number of digits having 4 letters.
	Space: O(m+n), meaning the total number of distinctive digits.
*/


class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // dict maps a number to its corresponding letters
        map<int, string> dict;
        init_dict(dict);
        // appear_digits stores the digits that appear
        vector<int> appear_digits;
        // the answer to be returned
        vector<string> answer;
        // record appearing digits
        int size = digits.size();
        for (int i = 0; i < size; ++i) {
            char c = digits[i];
            appear_digits.push_back(c - '0');
        }
        // search and backtrack
        string cur_string;
        search(0, cur_string, dict, appear_digits, answer);
        return answer;
    }

private:
    void search(int i, string& cur_string, map<int, string>& dict, 
            vector<int>& appear_digits, vector<string>& answer) {
        int digit_num = appear_digits.size();
        // record current string into answer
        if (i == digit_num) {
            // we don't need to add an empty string
            if (i != 0) {
                answer.push_back(cur_string);
            }
            return;
        }

        int cur_digit = appear_digits[i];
        string chars = dict[cur_digit];
        int chars_size = chars.size();
        // searching and backtracking
        for (int j = 0; j < chars_size; ++j) {
            char cur_char = chars[j];
            cur_string.push_back(cur_char);
            search(i + 1, cur_string, dict, appear_digits, answer);
            cur_string.pop_back();
        }
    }

    void init_dict(map<int, string>& dict) {
        dict.insert({2, "abc"});
        dict.insert({3, "def"});
        dict.insert({4, "ghi"});
        dict.insert({5, "jkl"});
        dict.insert({6, "mno"});
        dict.insert({7, "pqrs"});
        dict.insert({8, "tuv"});
        dict.insert({9, "wxyz"});
    }
};
