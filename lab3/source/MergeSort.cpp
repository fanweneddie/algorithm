#include <iostream>
#include <vector>
using namespace std;
#define SIZE 200
#define INF 100000
/*
testcase:
input:
5
68 34 41 55 71
output:
613
*/
int main()
{
    // the number of arrays to merge
    int num;
    // the original cost sum from i to j
    int orig_sum[SIZE][SIZE];
    // the minimal total merge cost sum from i to j
    int total_sum[SIZE][SIZE];
    // the list to store the cost of each array
    vector<int> list;

    // input data
    cin >> num;
    int cost;
    for(int i = 0;i < num;++i)
    {
        cin >> cost;
        list.push_back(cost);
    }
    
    // init total_sum and calculate orig_sum
    for(int i = 0;i < num;++i)
    {
        total_sum[i][i] = 0;
        orig_sum[i][i] = list[i];
        for(int j = i+1;j < num;++j)
        {
            total_sum[i][j] = INF;
            orig_sum[i][j] = orig_sum[i][j-1] + list[j];
        }
    }

    // DP in O(n^3)
    // l = gap of (i,j)
    // total_sum[i][j] 
    // = min{total_sum[i][k] + total_sum[k+1][j] + orig_sum[i][j]}
    // where i <= k < j
    for(int l = 2;l <= num;++l)
    {
        for(int i = 0;i <= num - l;++i)
        {
            int j = i + l - 1;
            int temp;
            for(int k = i;k < j;++k)
            {
                temp = total_sum[i][k] + total_sum[k+1][j] + orig_sum[i][j];
                if(temp < total_sum[i][j])
                    total_sum[i][j] = temp;
            }
        }
    }

    // output result
    cout << total_sum[0][num-1] << endl;
    return 0;
}
