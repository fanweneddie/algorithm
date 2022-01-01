#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// to sort the original village_pos in a ascending sequence
bool compare(int ele_1,int ele_2) 
{ 
    return ele_1 < ele_2;
} 

int main()
{
    // number of villages, coverage radius and number of station
    int village_num,radius,station_num = 0;
    // the linear list to store the villages
    vector<int> village_pos;

    // data input
    cin >> village_num >> radius;
    int temp_pos;
    for(int i = 0; i < village_num;++i)
    {
        cin >> temp_pos;
        village_pos.push_back(temp_pos);
    }

    sort(village_pos.begin(),village_pos.end(),compare);

    // index to traverse the village_pos
    int i = 0,j;
    // temp place to place a station
    int place;
    while(i < village_num)
    {
        // get the place to place a station
        place = village_pos[i];
        j = i;
        while(j < village_num && 
            village_pos[j] <= village_pos[i] + radius)
        {
            j++;
        }
        place = village_pos[j-1];

        // eliminate the villages in station's coverage
        while(j < village_num && 
            village_pos[j] <= place + radius)
        {
            j++;
        }

        // add new station and update the current village
        station_num++;
        i = j;
    }
    cout << station_num << endl;
    return 0;

}

