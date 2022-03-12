/*
Problem: https://leetcode-cn.com/problems/minimum-cost-for-tickets/

Solution: Top-down dynamic programming
We can't do dp in a bottom-up way, since the choice of ticket for ith day can affect that of the jth day,
where j < i.

Complexity:
	Time: O(n)
	Space: O(n), where n is the biggest day 
*/

class Solution {
    public int mincostTickets(int[] days, int[] costs) {
        int day_num = days.length;
        int last_day = days[day_num - 1];
        // dp[i] is the min cost for day[i];
        int[] dp = new int[last_day + 35];
        // we use hashset for an O(1) search
        Set<Integer> day_set = new HashSet<Integer>();
        for (int day : days) {
            day_set.add(day);
        }
        // dynamic programming
        // if i > last day, then dp[i] = 0.
        for (int i = last_day; i >= 1; --i) {
            if (day_set.contains(i)) {
                dp[i] = get_min(dp[i+1] + costs[0], dp[i+7] + costs[1], dp[i+30] + costs[2]);
            } else {
                dp[i] = dp[i+1];
            }
        }
        return dp[1];
    }

    // get minimum element from a, b and c
    private int get_min(int a, int b, int c) {
        int temp = Math.min(a, b);
        return Math.min(temp, c);
    }
}
