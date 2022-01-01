#include <iostream>
using namespace std;
#define SIZE 2000

/*
testcase:
in:
5 5
1 0 0 0 0 
1 0 0 1 1 
0 1 0 0 0 
0 1 0 1 0 
1 0 0 0 0 
out:
18
*/
int min(int a,int b,int c)
{
    int temp = a < b ? a : b;
    temp = temp < c ? temp:c;
    return temp;
}

int main()
{
    int row,column;
    int square_num[SIZE][SIZE];
    cin >> row >> column;
    int temp;
    for(int i = 0; i < row;++i)
    {
        for(int j = 0;j < column;++j)
        {
            cin >> temp;
            square_num[i][j] = 1- temp;
        }
    }
    /*
    for(int i = 0; i < row;++i)
    {
        for(int j = 0; j < column;++j)
            cout << square_num[i][j] << " ";
        cout << endl;
    }
    */
    for(int i = 1; i < row;++i)
    {
        for(int j = 1; j < column;++j)
        {
            if(square_num[i][j] != 0)
            {
                square_num[i][j] += min( square_num[i][j-1], 
                    square_num[i-1][j],square_num[i-1][j-1] );
            }
        }
    }
     
    int sum = 0;
    for(int i = 0; i < row;++i)
    {
        for(int j = 0; j < column;++j)
            sum += square_num[i][j];
    }

    cout << sum << endl;
    return 0;
}
