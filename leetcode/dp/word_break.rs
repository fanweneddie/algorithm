/*
Problem: https://leetcode-cn.com/problems/word-break/

Solution: We set dp[i] to mark whether s[0...i-1] can be matched

Then, we have 
dp[0] = true,
dp[i] = dp[j] & s[j...i-1] is in dictionary, where 0 <= j <= i-1.
We can also leverage the max length of word to reduce unnecessary searching.
And we finally return dp[size]

Complexity:
Time: O(n^2 + k)
Space: O(n + k), where n is the size of input string and k is the size of dictionary
*/

use std::collections::HashSet;

impl Solution {
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        let size = s.len();
        // dp[i] means whether s[0...i-1] can be matched
        let mut dp = vec![false;size + 1];
        // the maximum length of a word in the dictionary
        let mut max_word_len = 0;
        // use a hashset to enable a fast search
        let mut words = HashSet::new();
	// build the dictionary in hashset
        for word in word_dict.iter() {
            if (word.len() > max_word_len) {
                max_word_len = word.len();
            }
            words.insert(word);
        }

        // dynamic programming
        dp[0] = true;
        for i in 1..size+1 {
            // getting the start position of searching
            let mut start = 0;
            if i > max_word_len {
                start = i - max_word_len;
            }
            for j in start..i {
            //for j in 0..i {
                if dp[j] == true && words.contains(&s[j..i].to_string()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[size];
    }
}
