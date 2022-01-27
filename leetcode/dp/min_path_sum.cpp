/*
Problem: https://leetcode-cn.com/problems/minimum-path-sum/

Solution: Dynamic Programming
Note that we use in-place memory to store states

Complexity:
Time: O(mn)
Space: O(1), where m and n are the row and column of the input grid.
*/

class Solution {
    public int minPathSum(int[][] grid) {
        int row = grid.length;
        int col = grid[0].length;
        
        // row 0
        for (int j = 1; j < col; ++j) {
            grid[0][j] += grid[0][j-1];
        }

        // col 0
        for (int i = 1; i < row; ++i) {
            grid[i][0] += grid[i-1][0];
        }

        // others
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                grid[i][j] += Math.min(grid[i][j-1], grid[i-1][j]);
            }
        }

        return grid[row-1][col-1];
    }
}
