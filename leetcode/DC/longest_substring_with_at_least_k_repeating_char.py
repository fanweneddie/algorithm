'''
Problem: https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/

Solution: Divide and Conquer
For a string s and a length k,
if len(s) < k, then return 0.
else if s contains a character whose frequency < k,
	then split s with k and get some substrings;
	For each substring t, do longestSubstring(t, k) recursively
else, return len(s)

Complexity:
Time: O(n)
Space: O(1)
'''

class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        # terminating condition
        if len(s) < k:
            return 0

        # count the frequency of each character
        freq = {}
        for ch in s:
            if ch in freq:
                freq[ch] += 1
            else:
                freq[ch] = 1

        # get the character whose frequency < k
        pivot = '0'
        for key in freq:
            if freq[key] < k:
                pivot = key
                break
        
        # the frequency of all characters are >= k
        if pivot == '0':
            return len(s)

        # divide and conquer
        result = 0
        for t in s.split(pivot):
            result = max(result, self.longestSubstring(t, k))
        return result
