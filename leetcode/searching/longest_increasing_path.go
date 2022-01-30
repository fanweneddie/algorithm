/*
Problem: https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/

Solution: top-down dynamic programming
For each position (x, y), the length of longest path from it as maxlen = max{maxlen(x+dx, y+dy)}.
At last, we get max{maxlen(x,y)} as the final result.

Complexity:
	Time: O(mn)
	Space: O(mn), where m and n is the row and column of the input matrix
*/

// four directions: up, left, down, right 
var dx = [4]int{-1, 0, 1, 0}
var dy = [4]int{0, -1, 0, 1}

func longestIncreasingPath(matrix [][]int) int {
    row := len(matrix)
    col := len(matrix[0])
    // the length of longest path that starts from the position
    path_lens := make([][] int, row)
    for i, _ := range path_lens {
        path_lens[i] = make([] int, col)
    }
    max_len := 0

    // top-down dynamic programming
    for i := 0; i < row; i++ {
        for j := 0; j < col; j++ {
            cur_len := searchLongestPath(i, j, matrix, path_lens)
            if cur_len > max_len {
                max_len = cur_len
            }
        }
    }
    return max_len
}

// Find the length of longest path that starts from (x, y)
// we make sure that (x, y) is a valid position
func searchLongestPath(x int, y int, matrix [][]int, path_lens [][]int) int {
    if path_lens[x][y] > 0 {
        return path_lens[x][y]
    }

    // mark this position as being searched
    path_lens[x][y] = 1
    // try to extend
    for i := 0; i < 4; i++ {
        new_x := x + dx[i]
        new_y := y + dy[i]
        valid := ValidToExtend(matrix[x][y], new_x, new_y, matrix)
        if valid {
            new_len := searchLongestPath(new_x, new_y, matrix, path_lens) + 1
            if new_len > path_lens[x][y] {
                path_lens[x][y] = new_len
            }
        }
    }

    return path_lens[x][y]
}

// Check whether position (x, y) is valid to be extended 
// from the original place with original value
func ValidToExtend(orig_val int, x int, y int, matrix [][] int) bool {
    row := len(matrix)
    col := len(matrix[0])
    // invalid position
    if x < 0 || x >= row || y < 0 || y >= col {
        return false
    }

    // return true only if it is rigidly ascending
    if matrix[x][y] > orig_val {
        return true
    } else {
        return false
    }
}
