#include <iostream>
#include <vector>
#include<algorithm>
#define SIZE 1000
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
1 1 1
output:
1

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
*/

class Group
{
    public:
    vector<int> members;
    int max_coe = 0;
};

// relation between two goods
class Relation
{
    public:
    int first;
    int second;
    int coe;
};

class Result
{
    public:
    int max_coe_1;
    int max_coe_2;
    int max_coe;
};

int coes[SIZE][SIZE];
// shows which group the goods is in
int group_num[SIZE];

// two groups
Group group_1;
Group group_2;

int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}

// the standard of comparison
bool compare_coe(Relation r1,Relation r2) 
{ 
    return r1.coe > r2.coe;
} 

// check the result of arranging to1 to group1
// and arranging to2 to group2
Result check_arrange_2(int to1,int to2)
{
    int max_coe_1 = coes[to1][to1];
    for(auto itr1 = group_1.members.begin();
        itr1 != group_1.members.end();++itr1)
    {
        if(coes[*itr1][to1] > max_coe_1)
            max_coe_1 = coes[*itr1][to1];
    }

    int max_coe_2 = coes[to2][to2];
    for(auto itr2 = group_2.members.begin();
        itr2 != group_2.members.end();++itr2)
    {
        if(coes[*itr2][to2] > max_coe_2)
            max_coe_2 = coes[*itr2][to2];
    }

    Result result;
    result.max_coe_1 = max(group_1.max_coe,max_coe_1);
    result.max_coe_2 = max(group_2.max_coe,max_coe_2);
    if(max_coe_1 > max_coe_2)
        result.max_coe = max_coe_1;
    else
        result.max_coe = max_coe_2;
    return result;
}


// check the result of arranging goods to group of group_num
int check_arrange_1(int goods,int group_num)
{
    int max_coe = coes[goods][goods];
    // arrange goods to group1
    if(group_num == 1)
    {
        for(auto itr1 = group_1.members.begin();
            itr1 != group_1.members.end();++itr1)
        {
            if(coes[*itr1][goods] > max_coe)
                max_coe = coes[*itr1][goods];
        }
    }
    // arrange goods to group2
    else if(group_num == 2)
    {
        for(auto itr2 = group_2.members.begin();
            itr2 != group_2.members.end();++itr2)
        {
            if(coes[*itr2][goods] > max_coe)
                max_coe = coes[*itr2][goods];
        }
    }
    return max_coe;
}

int main()
{
    int goods_num,relation_num;
    vector<Relation> relation_list;    
    cin >> goods_num >> relation_num;

    for(int i = 1; i <= goods_num;++i)
    {
        group_num[i] = 0;
        for(int j = 1; j <= goods_num;++j)
            coes[i][j] = 0; 
    }

    Relation rel_temp;
    for(int i = 0; i < relation_num;++i)
    {
        cin >> rel_temp.first 
            >> rel_temp.second >> rel_temp.coe;
        
        relation_list.push_back(rel_temp);
        coes[rel_temp.first][rel_temp.second] = rel_temp.coe;
        coes[rel_temp.second][rel_temp.first] = rel_temp.coe;   
    }

    // sort the input relationship according to coe
    sort(relation_list.begin(),relation_list.end(),compare_coe);

    // arrange the goods
    for(int i = 0;i < relation_num;++i)
    {
        // two goods in a relationship
        int goods_1 = relation_list[i].first;
        int goods_2 = relation_list[i].second; 
        
        // goods_1 and goods_2 are not arranged
        if( group_num[goods_1] == 0 && group_num[goods_2] == 0 )
        {
            // self-coe is not zero
            // print it out directly and return
            if(goods_1 == goods_2)
            {
                cout << coes[goods_1][goods_1] << endl;
                return 0;
            }
            // goods_1 and goods_2 are distinct
            else
            {
                Result overall_1 = check_arrange_2(goods_1,goods_2);
                Result overall_2 = check_arrange_2(goods_2,goods_1);
                // goods_1 to group_1, goods_2 to group_2
                // choose overall_1
                if(overall_1.max_coe < overall_2.max_coe)
                {
                    group_1.members.push_back(goods_1);
                    group_2.members.push_back(goods_2);
                    group_1.max_coe = overall_1.max_coe_1;
                    group_2.max_coe = overall_1.max_coe_2;
                    group_num[goods_1] = 1;
                    group_num[goods_2] = 2; 
                }
                // goods_1 to group_2 and goods_2 to group_1
                // choose overall_2
                else
                {
                    group_1.members.push_back(goods_2);
                    group_2.members.push_back(goods_1);
                    group_1.max_coe = overall_2.max_coe_1;
                    group_2.max_coe = overall_2.max_coe_2;
                    group_num[goods_1] = 2;
                    group_num[goods_2] = 1;
                }
            }
        }
        // goods_1 is not arranged and goods_2 is arranged
        // take goods_1 and goods_2 apart
        else if(group_num[goods_1] == 0 && group_num[goods_2] != 0)
        {
            // goods_1 to group_2
            if(group_num[goods_2] == 1)
            {
                int max_coe_2 = check_arrange_1(goods_1,2);
                group_2.members.push_back(goods_1);
                group_2.max_coe = max(group_2.max_coe,max_coe_2);
                group_num[goods_1] = 2;
            }
            // goods_1 to group_1
            else
            {
                int max_coe_1 = check_arrange_1(goods_1,1);
                group_1.members.push_back(goods_1);
                group_1.max_coe = max(group_1.max_coe,max_coe_1);
                group_num[goods_1] = 1;   
            }
        }

        // goods_2 is not arranged and goods_1 is arranged
        // take goods_1 and goods_2 apart
        else if(group_num[goods_1] != 0 && group_num[goods_2] == 0)
        {
            // goods_2 to group_2
            if(group_num[goods_1] == 1)
            {
                int max_coe_2 = check_arrange_1(goods_2,2);
                group_2.members.push_back(goods_2);
                group_2.max_coe = max(group_2.max_coe,max_coe_2);
                group_num[goods_2] = 2;
            }
            // goods_2 to group_1
            else
            {
                int max_coe_1 = check_arrange_1(goods_2,1);
                group_1.members.push_back(goods_2);
                group_1.max_coe = max(group_1.max_coe,max_coe_1);
                group_num[goods_2] = 1;   
            }
        }
        // else goods_1 and goods_2 are both arranged, do nothing
    }
    
    // print the result for debug
    /*
    cout << "----------------------------\n";
    cout << "group_1:\n";
    for(int i = 0; i < group_1.members.size();++i)
    {
        cout << group_1.members[i] << " ";
    }
    cout << "\ncoe_sum = " << group_1.max_coe << endl;

    cout << "----------------------------\n";
    cout << "group_2:\n";
    for(int i = 0; i < group_2.members.size();++i)
    {
        cout << group_2.members[i] << " ";
    }
    cout << "\ncoe_sum = " << group_2.max_coe << endl;
    cout << "-----------------------------\n";
    */
    // output the final result
    if(group_1.max_coe > group_2.max_coe)
        cout << group_1.max_coe << endl;
    else
        cout << group_2.max_coe << endl;
    
    return 0;
}
