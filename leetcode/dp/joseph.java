/*
Problem:
https://leetcode-cn.com/problems/find-the-winner-of-the-circular-game/

Solution:
We set the winner as f(n, k).
Obviously, f(1, k) = 1,
Due to the offset, we have f(i, k) = (f(i-1, k) + k - 1) % i + 1
And we just need to return f(n, k).

Complexity:
Time: O(n)
Space: O(1), where n is the number of players.
*/

class Solution {
    public int findTheWinner(int n, int k) {
        // f(i,k)
        int winner = 1;
        // dynamic programming
        for (int i = 2; i <= n; ++i) {
            winner = (winner + k - 1) % i + 1;
        }
    
        return winner;
    }
}
