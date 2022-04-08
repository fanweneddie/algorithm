/*
Problem: https://leetcode-cn.com/problems/maximum-length-of-pair-chain/

Solution: greedy, same as https://github.com/fanweneddie/algorithm_lab/blob/main/leetcode/greedy/maxmimum_nonoverlap_interval.cpp
*/

class Solution {
    private final int MY_INFINITY = 999999;
    public int findLongestChain(int[][] pairs) {
        // sort the pairs with ascending order of second number
        Arrays.sort(pairs, Comparator.comparingInt(pair -> pair[1]));
        // length of the chain
        int chain_len = 0;
        // number of pairs
        int pair_num = pairs.length;
        // the temporary pair in traversal
        int[] temp_pair = {-MY_INFINITY, -MY_INFINITY};
        // greedy
        for (int[] pair : pairs) {
            if (pair[0] > temp_pair[1]) {
                temp_pair = pair;
                chain_len++;
            }
        }
        return chain_len;
    }
}
