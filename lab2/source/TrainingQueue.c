#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHTABLE_SIZE 100000
typedef struct HashItem
{
    char name[6];
    int cnt;
}HashItem;
// hashtable for search
HashItem hash_table[HASHTABLE_SIZE];

int hash(char* name)
{
    int hash_index = 0;
    int coe = 1;
    int len = strlen(name);
    for(int i = 0; i < len ;++i)
    {
        // printf("%s[%d] = %d\n",name,i,name[i]);
        hash_index += name[i]*coe;
        coe *= 26; 
    }
    hash_index = hash_index % HASHTABLE_SIZE;
    // hash crash
    while( strcmp(hash_table[hash_index].name,name) != 0 
        && strcmp(hash_table[hash_index].name,"!!!") != 0 )
    {
        hash_index = (hash_index + 1) % HASHTABLE_SIZE;
    }

    if(strcmp(hash_table[hash_index].name,name) != 0 )
        strcpy(hash_table[hash_index].name,name);
    return hash_index;
}

int main()
{
    // total student number(n)
    int stu_num;
    // distinct name number in a subqueue(k)
    int name_num;
    // name for all of the students
    // this array is too large that it causes segmentation fault
    // in my PC, but it works in OJ
    char name_list[10000000][6];
    // input data
    scanf("%d%d",&stu_num,&name_num);
    for(int i = 1;i <= stu_num;++i)
    {
        scanf("%s",name_list[i]);
    }

    if(name_num == 1)
    {
        printf("%d\n",stu_num);
        return 0;
    }
    // left and right pointer of the interval
    // the name count in the interval
    // the number of cases 
    int left = 1,right = 1,name_cnt = 1,case_num = 0;
    // initialize hash_table
    for(int i = 0;i < HASHTABLE_SIZE;++i)
    {
        hash_table[i].cnt = 0;
        strcpy(hash_table[i].name,"!!!");
    }
    // count name_list[1] by default
    hash_table[ hash(name_list[1]) ].cnt++;
    // the main iteration
    // !(left == stu_num && right == stu_num)
    while(right <= stu_num)
    {
        // find the interval with name_num different names in it
        while(name_cnt < name_num && right < stu_num)
        {
            right++;
            int hash_index = hash(name_list[right]);
            hash_table[hash_index].cnt++;
            if( hash_table[hash_index].cnt == 1 )
                name_cnt++;
        }
        // can't slide right, the search is over, break
        if(name_cnt < name_num && right == stu_num)
            break;
        // slide right to find repetitious names
        while(1)
        {
            // count this case into total case_num
            case_num++;
            // name_list[right] is repetitious in the window
            if(right < stu_num && hash_table[hash
                    (name_list[right+1])].cnt != 0 )
            {
                right++;
                hash_table[hash(name_list[right])].cnt++;
            }
            // name_list[right] hasn't appear in the window
            else
                break;
        }
        // now, we can't slide right any more
        // delete the repetitious names from the left
        while(name_cnt == name_num)
        {
            left++;
            int hash_index = hash(name_list[left-1]);
            hash_table[hash_index].cnt--;
            // it means that the name is not in the window any more
            if(hash_table[hash_index].cnt == 0)
                name_cnt--;
            // it means that the name is still in the window any more
            // so count this case
            else
            {
                case_num++;
                // slide right ptr to left to count some other cases
                int temp_right = right;
                while( hash_table[hash(name_list[temp_right])].cnt > 1)
                {
                    case_num++;
                    hash_table[hash(name_list[temp_right])].cnt--;
                    temp_right--;
                }
                // now right ptr is on its leftmost place,just restore it
                // and restore the names in the half way
                temp_right++;
                while(temp_right <= right)
                {
                    hash_table[hash(name_list[temp_right])].cnt++;
                    temp_right++;
                }
            }
        }
    }// while
    // output the result
    printf("%d\n",case_num);
    return 0;
}
