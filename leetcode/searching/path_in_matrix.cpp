#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 4 directions
int di[4] = {1, 0, 0, -1};
int dj[4] = {0, 1, -1, 0};

// Location in the matrix
struct Loc {
    int i;
    int j;
    Loc(int i, int j) {
        this->i = i;
        this->j = j;
    }
};

bool dfs(int k, string word, Loc loc, vector<vector<char>>& board, vector<vector<bool>>& searched) {
    int row = board.size();
    int col = row > 0 ? board[0].size() : 0;
    int i = loc.i;
    int j = loc.j;

    if (board[i][j] == word[k]) {
        searched[i][j] = true;
        if (k == word.size() - 1) {
            return true;
        } else {
            k++;
            for (int d = 0; d < 4; ++d) {
                int new_i = i + di[d];
                int new_j = j + dj[d];
                Loc new_loc = Loc(new_i, new_j);
                if (new_i < 0 || new_i >= row || new_j < 0 || new_j >= col) {
                    continue;
                }
                if(!searched[new_i][new_j] && dfs(k, word, new_loc, board, searched)) {
                    return true;
                }
            }
        }
        searched[i][j] = false;
    }
    return false;
}

int main() {
    int row, col;
    vector<vector<char>> board;
    vector<vector<bool>> searched;
    string word;
    bool result = false;

    // input and init
    cin >> row >> col;
    board.resize(row);
    for (int i = 0; i < row; ++i) {
        board[i].resize(col);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> board[i][j];
        }
    }
    cin >> word;

    searched.resize(row);
    for (int i = 0; i < row; ++i) {
        searched[i].resize(col);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            searched[i][j] = false;
        }
    }

    // find the starting point
    for (int i = 0; i < row && !result; ++i) {
        for (int j = 0; j < col; ++j) {
            // start with location (i, j)
            if (board[i][j] == word[0]) {
                Loc loc = Loc(i, j);
                if (dfs(0, word, loc, board, searched)) {
                    result = true;
                    break;
                }
            }
        }
    }

    cout << result << endl;
    return 0;
}