#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
testcase 1:
input:
4 7
2 4 5
1 3 4
1 4 3
2 3 3
3 4 2
1 2 1
4 4 1
output:
2

testcase 2:
input:
5 7
1 3 3 
1 4 3
1 5 3
2 3 3
2 4 3
2 5 3
1 1 10
output:
10

testcase 3;
input:
5 7
1 2 1
1 4 4
1 5 3
2 3 2
2 4 3
3 4 1
4 5 5
output:
3

testcase4:
input:
4 4
1 2 5
3 4 4
1 3 3
2 4 2
output:
0
*/

// relation between two goods
class Relation
{
    public:
    int first;
    int second;
    int coe;
};

// the temp groups
vector<vector<int>> groups;

// shows which group the goods is in
vector<int> group_num;

vector<Relation> relation_list;  

int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}

int another_group(int group_num)
{
    if(group_num % 2 == 0)
        return group_num+1;
    else
        return group_num-1;
}

// the standard of comparison
// make them decreasing by coe
bool compare_coe(Relation r1,Relation r2) 
{ 
    return r1.coe > r2.coe;
}

// merge groups[src_num] to groups[dst_num]
void merge(int src_num,int dst_num)
{
    int src_size = groups[src_num].size();
    for(int i = 0;i < src_size;++i)
    {
        group_num[ groups[src_num][i] ] = dst_num;
    }

    //merge(groups[dst_num].begin(), groups[dst_num].end(), 
    //groups[src_num].begin(), groups[src_num].end(), groups[dst_num].begin());
    
    groups[dst_num].insert(groups[dst_num].end(),
       groups[src_num].begin(),groups[src_num].end());
}

int main()
{
    int goods_num,relation_num;  
    cin >> goods_num >> relation_num;
    for(int i = 0;i <= goods_num;++i)
        group_num.push_back(0);

    Relation rel_temp;
    for(int i = 0; i < relation_num;++i)
    {
        cin >> rel_temp.first 
            >> rel_temp.second >> rel_temp.coe;
        relation_list.push_back(rel_temp);  
    }

    // sort the input relationship according to coe
    sort(relation_list.begin(),relation_list.end(),compare_coe);

    int g_ptr = 2;
    int groups_size = 8;
    groups.resize(groups_size);
    
    // arrange the goods
    for(int i = 0;i < relation_num;++i)
    {
        // two goods in a relationship
        int goods_1 = relation_list[i].first;
        int goods_2 = relation_list[i].second; 
        // output the self-coe
        if(goods_1 == goods_2)
        {
            cout << relation_list[i].coe << endl;
            return 0;
        }
        // both are not arranged yet
        else if(group_num[goods_1] == 0 && group_num[goods_2] == 0)
        {
            groups[g_ptr].push_back(goods_1);
            group_num[goods_1] = g_ptr;
            g_ptr++;
            groups[g_ptr].push_back(goods_2);
            group_num[goods_2] = g_ptr;
            g_ptr++;
            if(g_ptr >= groups_size/2)
            {
                groups_size *= 2;
                groups.resize(groups_size);
            }
        }
        // goods_1 is arranged
        // push goods_2 to another group
        else if(group_num[goods_1] != 0 && group_num[goods_2] == 0)
        {
            int group_num_1 = group_num[goods_1];
            // the group_num that group_2 should be arranged to
            int group_num_2 = another_group(group_num_1);
            groups[group_num_2].push_back(goods_2);
            group_num[goods_2] = group_num_2;
        }
        // goods_2 is arranged
        // push goods_1 to another group
        else if(group_num[goods_1] == 0 && group_num[goods_2] != 0)
        {
            int group_num_2 = group_num[goods_2];
            // the group_num that group_1 should be arranged to
            int group_num_1 = another_group(group_num_2);
            groups[group_num_1].push_back(goods_1);
            group_num[goods_1] = group_num_1;
        }
        // else goods_1 and goods_2 are both arranged,
        // merge their groups
        else if(group_num[goods_1] != 0 && group_num[goods_2] != 0)
        {
            // if they are in the same group, just output it!
            if(group_num[goods_1] == group_num[goods_2])
            {
                cout << relation_list[i].coe << endl;
                return 0;
            }
            // the group_num that goods_1 is in
            int group_num_1 = group_num[goods_1];
            // the group_num that goods_2 is in
            int group_num_2 = group_num[goods_2];
            // the another group num that goods_1 
            // and goods_2's group should be merge with
            int group_num_1_another = another_group(group_num_2);
            int group_num_2_another = another_group(group_num_1);
            // merge
            merge(group_num_1,group_num_1_another);
            merge(group_num_2_another,group_num_2);
        }
    }
    cout << 0 << endl;    
    return 0;
}
