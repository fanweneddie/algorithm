#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
testcase
input:
7
1 2
2 5
3 3
4 4
5 1
6 7 
7 6
output:
4

input:
4
2 0
1 1
4 5
3 3
output:
3

input:
3
1 2
1 3
1 1
output:
3

input:
6
1 1
2 2
3 0
4 0
5 1
6 3
output:
4
*/


// longest increasing subsequence

class Point
{
    public:
    int x;
    int y;
};

// the standard of comparison
// make Points increasing by x
// if x are equal, make it increasing by y 
bool compare(Point p1,Point p2) 
{ 
    return p1.x < p2.x 
        || (p1.x == p2.x && p1.y <= p2.y);
}

int main()
{
    int point_num;
    Point temp_point;
    // a list to store points
    vector<Point> point_list;
    // LIS[i] stores the longest increasing subsequence
    // from 0 to i
    vector<int> LIS;
    // input
    cin >> point_num;    
    for(int i = 0;i < point_num;++i)
    {
        cin >> temp_point.x >> temp_point.y;
        point_list.push_back(temp_point);
    }

    // sort the points to make them 
    // increasing by x
    sort(point_list.begin(),point_list.end(),compare);
    
    // init LIS[i] as 1
    for(int i = 0;i < point_num;++i)
        LIS.push_back(1);
    for(int i = 1;i < point_num;++i)
    {
        for(int j = 0;j < i;++j)
        {
            if( point_list[i].y >= point_list[j].y 
                && LIS[j] + 1 > LIS[i] )
                LIS[i] = LIS[j] + 1;
        }
    }

    // max output the overall LIS
    int max = 1;
    for(int i = 0;i < point_num;++i)
        if(LIS[i] > max)
            max = LIS[i];
    cout << max << endl;
    return 0;
}

