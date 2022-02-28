/*
Problem: https://leetcode-cn.com/problems/01-matrix/

Solution: BFS
At first, we push the location of 0s into queue and set their distance as 0.
Then, we keep doing BFS to calculate the distance.

Complexity:
	Time: O(mn)
	Space: O(mn), where m is row and n is column of the input matrix
*/


// The location (i, j) in a matrix
class Loc {
    public int i;
    public int j;
    public Loc(int i, int j) {
        this.i = i;
        this.j = j;
    }
}

class Solution {
    public int[] di = {1, 0, -1, 0};
    public int[] dj = {0, 1, 0, -1};
    public int[][] updateMatrix(int[][] mat) {
        int row = mat.length;
        int col = mat[0].length;
        int[][] result = new int[row][col];
        // queue storing location for BFS
        Queue<Loc> q = new LinkedList<Loc>();
        // first, we push the location of 0s into q
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (mat[i][j] == 0) {
                    result[i][j] = 0;
                    Loc loc = new Loc(i, j);
                    q.offer(loc);
                }
            }
        }
        // BFS
        while (!q.isEmpty()) {
            Loc loc = q.poll();
            // search the neighboring locations
            for (int k = 0; k < 4; ++k) {
                int new_i = loc.i + di[k];
                int new_j = loc.j + dj[k];
                if (is_valid_loc(row, col, new_i, new_j) && 
                    mat[new_i][new_j] != 0 && result[new_i][new_j] == 0 ) {
                    result[new_i][new_j] = result[loc.i][loc.j] + 1;
                    Loc new_loc = new Loc(new_i, new_j);
                    q.offer(new_loc);
                }
            }
        }

        return result;
    }

    // Check whether location (i, j) is valid
    boolean is_valid_loc(int row, int col, int i, int j) {
        if (i >= 0 && i < row && j >= 0 && j < col) {
            return true;
        } else {
            return false;
        }
    }
}
