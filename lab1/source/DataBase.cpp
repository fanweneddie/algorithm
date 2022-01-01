#include <iostream>
#include <vector>
#include <string>
using namespace std;
// FANWEN 2020.10.25
/* 
searching problem
INPUT: 
(1). insert several pairs of key-values to a database
(2). search several values i from the database
OUTPUT:
show the keys of those values.
if the value is absent in the database,print(-1).

e.g.
INPUT:
INSERT 1 7
INSERT 2 11
INSERT 3 2
INSERT 4 5
INSERT 5 3
FIND 2
FIND 4
FIND 7
EXIT
OUTPUT:
3
-1
1
*/



// an Item of data
// which record the key and value
class Item
{
    public:
    int key;
    int value;
    Item()
    {
        key = 0;
        value = 0;
    }
};

// declaration of some functions
void quick_sort_Item(int start,int end,vector<Item>& Item_vec);
int partition_Item(int start,int end,vector<Item>& Item_vec);
int binary_search(int start,int end,
        int search_value, vector<Item>& Item_vec);

// quick sort Item_vec[start,..., end](both inclusive)
// to make it ascending by item's value
// ----------------------------------------
// average T(n) = O(nlgn)
// worst T(n) = O(n^2) (which is really rare!)
void quick_sort_Item(int start,int end,vector<Item>& Item_vec)
{
    // the condition to do recursion
    if(start < end)
    {   
        // get the index of pivot element
        int pivot_index = partition_Item(start,end,Item_vec);
        // sort the subarray 
        // at the left and right of pivot element 
        quick_sort_Item(start,pivot_index - 1,Item_vec);
        quick_sort_Item(pivot_index + 1,end,Item_vec);
    }
}

// find the index of pivot element( = Item_vec[end])
// partition as left part, pivot element and right part
// s.t. left_part_element .value <= 
// pivot_element.value < right_part_element.value
int partition_Item(int start,int end,vector<Item>& Item_vec)
{
    Item pivot_ele = Item_vec[end];
    // i is the right most position of the left part
    int i = start - 1;
    for(int j = start; j < end;++j)
    {
        // exchange Item_vec[i+1] and Item_vec[j]
        if( Item_vec[j].value <= pivot_ele.value )
        {
            i++;
            Item temp_Item;
            temp_Item = Item_vec[i];
            Item_vec[i] = Item_vec[j];
            Item_vec[j] = temp_Item;
        }
    }
    // exchange arr[i+1] with arr[end]
    Item_vec[end] = Item_vec[i+1];
    Item_vec[i+1] = pivot_ele;
    // i+1 is the index of pivot element
    return i+1;
}

// binary_search the search_value in vec[start,end](inclusive)
// if the search_value can be searched, return its key
// else, return -1.
int binary_search(int start,int end,
        int search_value, vector<Item>& Item_vec)
{
    if(start == end)
    {
        if(Item_vec[start].value == search_value)
            return Item_vec[start].key;
        else
            return -1;
    }
    else
    {
        int mid = (start + end)/2;        
        if(Item_vec[mid].value >= search_value)
            return binary_search(start, mid, search_value,Item_vec);
        else
            return binary_search(mid + 1, end, search_value,Item_vec);
    }
}


/*
firstly, I quick_sort the database by value in O(nlgn)
then, I binary_search m times(where m is the number of find command)
so the total T(n) = O(nlgn) + mO(lgn) = O( (m+n)lgn )
*/
int main()
{
    // close cin's synchronization with stdin
    // to make it faster
    ios::sync_with_stdio(false);
    // cmd: INSERT,FIND and EXIT
    string cmd;
    // the value to search in FIND command
    int search_value;
    // the vector to store the keys and values in database
    vector<Item> data_base;
    // the vector to store the output result
    vector<int> result_vec;
    //-----------------------------------------------
    // stage of insertion
    cin >> cmd;
    while(cmd == "INSERT")
    {
        // input key and value
        // insert them to database
        Item temp_Item;
        cin >> temp_Item.key >> temp_Item.value;
        data_base.push_back(temp_Item);
        cin >> cmd;
    }
    // make database ascending according to value
    quick_sort_Item(0,data_base.size() - 1,data_base);
    //-----------------------------------------------
    // stage of searching
    while(cmd == "FIND")
    {
        // input the value to search
        cin >> search_value;
        // use binary search to search that value
        int result = binary_search(0,data_base.size()-1,search_value,data_base);
        // store the result
        result_vec.push_back(result);
        cin >> cmd;
    }
    //-----------------------------------------------
    // stage of output
    // output the search result and exit
    if(cmd == "EXIT")
    {   
        int result_len = result_vec.size();
        for(int i = 0; i < result_len;++i)
            cout << result_vec[i] << endl;
    }
    return 0;
}
