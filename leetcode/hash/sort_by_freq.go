/*
Problem: https://leetcode-cn.com/problems/sort-characters-by-frequency/

Solution:
Firstly, we use a hashmap to store the frequency of each char.
Secondly, we use a bucket to store the chars of each frequency.
At last, we traverse the bucket reversely to get the result string

Complexity:
	Time: O(n+k)
	Space: O(n+k), where n is the length of s and k is the number of distinctive chars  
*/

func frequencySort(s string) string {
    // stores the frequency of each char
    freq_map := make(map[byte] int)
    // the max frequency (to save memory for bucket)
    max_freq := 0
    
    // count the frequency of each char
    for i := range s {
        c := s[i]
        freq_map[c]++
        if (freq_map[c] > max_freq) {
            max_freq = freq_map[c]
        }
    }

    // stores the chars of each frequency
    buckets := make([][] byte, max_freq + 1)

    // fill the buckets
    for c, freq := range freq_map {
        buckets[freq] = append(buckets[freq], c)
    }

    // new string for output
    new_str := make([] byte, 0)

    // iterate over the buckets
    for i := max_freq; i > 0; i-- {
        for _, c := range buckets[i] {
            new_str = append(new_str, bytes.Repeat([]byte{c}, i)...)
        }
    }

    return string(new_str)
}
