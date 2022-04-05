/*
Problem: https://leetcode-cn.com/problems/number-of-islands/

Solution: DFS

Complexity:
	Time: O(mn),
	Space: O(mn) in calling stack, where m and n are rows and columns of the grid.
*/

class Solution {
    // movement in 4 directions
    private int[] dx = {0, 0, 1, -1};
    private int[] dy = {1, -1, 0, 0};
    public int numIslands(char[][] grid) {
        // number of continents
        int count = 0;
        int row = grid.length;
        int col = grid[0].length;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] == '1') {
                    DFS(i, j, grid);
                    count++;
                }
            }
        }
        return count;
    }

    // Search from (x, y) and mark them as "2"
    private void DFS(int x, int y, char[][] grid) {
        grid[x][y] = '2';
        for (int i = 0; i < 4; ++i) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            if (isIsland(new_x, new_y, grid)) {
                DFS(new_x, new_y, grid);
            }
        }
    }

    // Check whether position (x, y) is an island in grid
    private boolean isIsland(int x, int y, char[][] grid) {
        int row = grid.length;
        int col = grid[0].length;
        if (x >= 0 && x < row && y >= 0 && y < col && grid[x][y] == '1') {
            return true;
        } else {
            return false;
        }
    }
}
