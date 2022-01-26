/*
Problem: https://leetcode-cn.com/problems/set-matrix-zeroes/

Solution: We use the elements at row 0 and column 0 to mark whether this col/row should be reset
Note that we should use another boolean variable to mark the boundary case.
Also pay attention to the sequence of resetting.

Complexity:
Time: O(mn)
Space: O(1), where m and n are the row and column of the input matrix.
*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
    	// whether row 0 should be reset
        bool clear_row0 = false;
        int row = matrix.size();
        int col = matrix[0].size();

        // special case for row 0
        for (int j = 0; j < col; ++j) {
            if (matrix[0][j] == 0) {
                clear_row0 = true;
                break;
            }
        }

        // mark 0 at row 0 and col 0
        for (int i = 1; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // reset by col
        for (int j = 1; j < col; ++j) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < row; ++i) {
                    matrix[i][j] = 0;
                }
            }
        }

        // reset by row
        for (int i = 1; i < row; ++i) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < col; ++j) {
                    matrix[i][j] = 0;
                }
            }
        }

        // reset col 0 and row 0
        if (matrix[0][0] == 0) {
            for (int i = 1; i < row; ++i) {
                matrix[i][0] = 0;
            }
        }
        if (clear_row0) {
            for (int j = 0; j < col; ++j) {
                matrix[0][j] = 0;
            }
        }
    }
};
