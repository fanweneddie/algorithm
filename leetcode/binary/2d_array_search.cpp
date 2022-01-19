#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int>> matrix;
    int row, col;
    int target;
    bool found = false;

    // input and init
    cin >> row;
    cin >> col;
    matrix.resize(row);
    for (int i = 0; i < row; ++i) {
        matrix[i].resize(col);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> matrix[i][j];
        }
    }
    cin >> target;

    int i = 0;
    int j = col - 1;
    while (i < row && j >= 0) {
        if (matrix[i][j] > target) {
            j--;
        } else if (matrix[i][j] < target) {
            i++;
        } else {
            found = true;
            break;
        }
    }

    cout << found << endl;
    return 0;

}