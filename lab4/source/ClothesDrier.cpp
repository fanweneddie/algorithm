#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INFINITY 999999999

// to sort the clothes location
// in a ascending sequence(
bool compare(int loc_1,int loc_2) 
{ 
    return loc_1 < loc_2;
}

// check whether dis can be realized by fetching some clothes
bool check_distance(vector<int> &loc,int dis,int fetch_num)
{
    int len = loc.size();
    int base = 0;
    int fetch_count = 0;
    for(int i = 0;i < len;++i)
    {
        if( loc[i] - loc[base] >= dis )
        {
            fetch_count += i - base - 1;
            base = i;
            if(fetch_count > fetch_num)
                return false;
        }
    }
    return true;
}

int main()
{
    // total number of clothes
    // and nnumber of clothes to be fetched
    int total_num,fetch_num;
    // location of each clothe
    vector<int> loc;
    // INPUT data
    // temp location for input
    int temp_loc;

    cin >> total_num >> fetch_num;

    for(int i = 0; i < total_num;++i)
    {
        cin >> temp_loc;
        loc.push_back(temp_loc);
    }

    // sort the locations in an ascending sequence
    sort(loc.begin(),loc.end(),compare);
    loc.push_back(INFINITY);
    // flag of success for the distance
    bool success;
    // distance
    int dis;
    // for binary search
    int high = loc[total_num-1] - loc[0];
    int low = 1; 
    int mid = (high + low)/2;
    dis = 0;
    success = check_distance(loc,mid,fetch_num);

    // binary search the most proper distance
    while( high >= low )
    {
        // go towards high to search
        if(success)
        {
            // save current distance
            dis = mid;
            low = mid + 1;
            mid = (high + low)/2;
            success = check_distance(loc,mid,fetch_num);
        }
        // go towards low to search
        else
        {
            high = mid - 1;
            mid = (high + low)/2;
            success = check_distance(loc,mid,fetch_num);
        }
    }

    cout << dis << endl;
    return 0; 
}
